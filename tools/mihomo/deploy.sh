#!/bin/bash
#
# ictyun 一键部署脚本（代理服务）
#
# 说明：本脚本部署的代理内核实际为 mihomo (Clash Meta)，但为避免在国内服务器上
#       因敏感词导致问题，所有安装路径、服务名、二进制文件名统一使用 "ictyun" 代替。
#
# 功能：在本地机器上执行，自动完成以下流程：
#   1. 下载代理内核 + Geodata 文件到本地
#   2. 通过 SCP 传输到目标服务器（二进制重命名为 ictyun）
#   3. 在服务器上安装、配置订阅、创建 systemd 服务
#   4. 安装 mh 快捷操作工具
#   5. 启动并验证代理是否工作
#
# 用法：
#   chmod +x deploy.sh
#   ./deploy.sh
#
# 非交互式（CI/批量部署）：
#   ./deploy.sh --ip 1.2.3.4 --user root --pass mypass --sub "https://..."
#
# 前提条件：
#   - 本地可访问 GitHub（下载内核和 geodata）
#   - 目标服务器为 Linux (amd64/arm64)，可通过 SSH 访问
#   - 本地已安装 ssh / scp / curl / gzip
#   - 密码登录需要 sshpass（SSH 密钥登录不需要）
#
# ============================================================================

set -e

# ---- 伪装名称（避免敏感词） ----
APP_NAME="ictyun"
INSTALL_DIR="/opt/$APP_NAME"

# 颜色
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m'

# 默认值
DEFAULT_KERNEL_VERSION="v1.19.8"
DEFAULT_PROXY_PORT="7897"
DEFAULT_API_PORT="9097"
DEFAULT_SSH_PORT="22"
USE_SUDO=""    # 非 root 用户时自动设为 "sudo"
S=""           # sudo 前缀，在 setup_sudo() 中设置

TMPDIR=$(mktemp -d)
trap 'rm -rf "$TMPDIR"' EXIT

# ============================================================================
# 工具函数
# ============================================================================

log_info()    { echo -e "${BLUE}[INFO]${NC} $1"; }
log_success() { echo -e "${GREEN}[ OK ]${NC} $1"; }
log_warn()    { echo -e "${YELLOW}[WARN]${NC} $1"; }
log_error()   { echo -e "${RED}[FAIL]${NC} $1"; }
log_step()    { echo -e "\n${CYAN}══════ $1 ══════${NC}\n"; }

check_local_deps() {
    local missing=()
    for cmd in ssh scp curl gzip; do
        command -v "$cmd" &>/dev/null || missing+=("$cmd")
    done
    if [ ${#missing[@]} -gt 0 ]; then
        log_error "缺少必要工具: ${missing[*]}"
        exit 1
    fi
}

remote_exec() {
    if [ -n "$SSH_KEY" ]; then
        ssh -o StrictHostKeyChecking=no -o ConnectTimeout=10 \
            -i "$SSH_KEY" -p "$SSH_PORT" "$SSH_USER@$SERVER_IP" "$1"
    else
        sshpass -p "$SSH_PASS" \
            ssh -o StrictHostKeyChecking=no -o ConnectTimeout=10 \
            -p "$SSH_PORT" "$SSH_USER@$SERVER_IP" "$1"
    fi
}

remote_upload() {
    if [ -n "$SSH_KEY" ]; then
        scp -o StrictHostKeyChecking=no -P "$SSH_PORT" \
            -i "$SSH_KEY" "$1" "$SSH_USER@$SERVER_IP:$2"
    else
        sshpass -p "$SSH_PASS" \
            scp -o StrictHostKeyChecking=no -P "$SSH_PORT" \
            "$1" "$SSH_USER@$SERVER_IP:$2"
    fi
}

# 上传文件到需要权限的目录（非 root 时先传 /tmp 再 sudo mv）
remote_upload_to() {
    local src="$1" dest="$2"
    if [ -n "$S" ]; then
        local tmp_name="/tmp/_deploy_$(basename "$dest")"
        remote_upload "$src" "$tmp_name"
        remote_exec "$S mv '$tmp_name' '$dest'"
    else
        remote_upload "$src" "$dest"
    fi
}

# 检测是否需要 sudo 并设置前缀
setup_sudo() {
    if [ "$SSH_USER" = "root" ] && [ -z "$USE_SUDO" ]; then
        S=""
        log_info "以 root 身份部署"
        return
    fi

    # 非 root 或手动指定 --sudo
    log_info "以 $SSH_USER + sudo 模式部署"

    # 验证 sudo 可用
    if remote_exec "sudo -n true" &>/dev/null; then
        S="sudo"
        log_success "sudo 权限验证通过 (NOPASSWD)"
    elif [ -n "$SSH_PASS" ] && remote_exec "echo '$SSH_PASS' | sudo -S true" &>/dev/null; then
        # sudo 需要密码 — 临时添加 NOPASSWD 规则，部署结束后自动清理
        remote_exec "echo '$SSH_PASS' | sudo -S sh -c 'echo \"${SSH_USER} ALL=(ALL) NOPASSWD: ALL\" > /etc/sudoers.d/_deploy_tmp && chmod 440 /etc/sudoers.d/_deploy_tmp'"
        S="sudo"
        # 注册清理（追加到已有的 trap）
        trap 'remote_exec "sudo rm -f /etc/sudoers.d/_deploy_tmp" 2>/dev/null; rm -rf "$TMPDIR"' EXIT
        log_success "sudo 权限验证通过"
    else
        log_error "$SSH_USER 无 sudo 权限，请使用 root 账号或配置 sudo"
        exit 1
    fi
}

# ============================================================================
# 命令行参数
# ============================================================================

parse_args() {
    while [ $# -gt 0 ]; do
        case "$1" in
            --ip)       SERVER_IP="$2"; shift 2 ;;
            --user)     SSH_USER="$2"; shift 2 ;;
            --pass)     SSH_PASS="$2"; shift 2 ;;
            --key)      SSH_KEY="$2"; shift 2 ;;
            --port)     SSH_PORT="$2"; shift 2 ;;
            --sub)      SUB_URL="$2"; shift 2 ;;
            --version)  KERNEL_VERSION="$2"; shift 2 ;;
            --sudo)        USE_SUDO="yes"; shift ;;
            --proxy-port)  PROXY_PORT="$2"; shift 2 ;;
            --api-port)    API_PORT="$2"; shift 2 ;;
            --help|-h)
                echo "用法: $0 [选项]"
                echo ""
                echo "选项:"
                echo "  --ip IP           服务器 IP"
                echo "  --user USER       SSH 用户名 (默认: root)"
                echo "  --pass PASS       SSH 密码"
                echo "  --key PATH        SSH 密钥路径"
                echo "  --port PORT       SSH 端口 (默认: 22)"
                echo "  --sub URL         订阅链接"
                echo "  --version VER     内核版本 (默认: $DEFAULT_KERNEL_VERSION)"
                echo "  --sudo            强制使用 sudo（非 root 用户自动启用）"
                echo "  --proxy-port PORT 代理端口 (默认: $DEFAULT_PROXY_PORT)"
                echo "  --api-port PORT   API 端口 (默认: $DEFAULT_API_PORT)"
                echo ""
                echo "交互式: 直接运行 $0 不加参数"
                exit 0
                ;;
            *) log_error "未知参数: $1"; exit 1 ;;
        esac
    done
}

# ============================================================================
# 第一步：收集用户输入
# ============================================================================

collect_input() {
    log_step "配置信息"

    if [ -n "$SERVER_IP" ] && [ -n "$SUB_URL" ] && { [ -n "$SSH_PASS" ] || [ -n "$SSH_KEY" ]; }; then
        SSH_PORT="${SSH_PORT:-$DEFAULT_SSH_PORT}"
        SSH_USER="${SSH_USER:-root}"
        KERNEL_VERSION="${KERNEL_VERSION:-$DEFAULT_KERNEL_VERSION}"
        PROXY_PORT="${PROXY_PORT:-$DEFAULT_PROXY_PORT}"
        API_PORT="${API_PORT:-$DEFAULT_API_PORT}"
        log_info "使用命令行参数（非交互模式）"
        return
    fi

    [ -z "$SERVER_IP" ] && read -rp "服务器 IP: " SERVER_IP
    [ -z "$SSH_PORT" ] && { read -rp "SSH 端口 [${DEFAULT_SSH_PORT}]: " SSH_PORT; SSH_PORT="${SSH_PORT:-$DEFAULT_SSH_PORT}"; }
    [ -z "$SSH_USER" ] && { read -rp "SSH 用户名 [root]: " SSH_USER; SSH_USER="${SSH_USER:-root}"; }

    if [ -z "$SSH_PASS" ] && [ -z "$SSH_KEY" ]; then
        echo "认证方式:"
        echo "  1) 密码"
        echo "  2) SSH 密钥"
        read -rp "选择 [1]: " AUTH_METHOD
        AUTH_METHOD="${AUTH_METHOD:-1}"

        if [ "$AUTH_METHOD" = "2" ]; then
            read -rp "SSH 密钥路径 [~/.ssh/id_rsa]: " SSH_KEY
            SSH_KEY="${SSH_KEY:-$HOME/.ssh/id_rsa}"
            [ ! -f "$SSH_KEY" ] && { log_error "密钥文件不存在: $SSH_KEY"; exit 1; }
        else
            if ! command -v sshpass &>/dev/null; then
                log_warn "密码认证需要 sshpass 工具"
                echo "  macOS:  brew install hudochenkov/sshpass/sshpass"
                echo "  Ubuntu: sudo apt install sshpass"
                read -rp "已安装？[y/N]: " confirm
                [ "$confirm" != "y" ] && [ "$confirm" != "Y" ] && exit 1
            fi
            read -rsp "SSH 密码: " SSH_PASS
            echo ""
        fi
    fi

    [ -z "$SUB_URL" ] && read -rp "订阅链接: " SUB_URL
    [ -z "$SUB_URL" ] && { log_error "订阅链接不能为空"; exit 1; }

    echo ""
    echo "可选配置（回车使用默认值）："
    [ -z "$KERNEL_VERSION" ] && { read -rp "内核版本 [${DEFAULT_KERNEL_VERSION}]: " KERNEL_VERSION; }
    KERNEL_VERSION="${KERNEL_VERSION:-$DEFAULT_KERNEL_VERSION}"
    [ -z "$PROXY_PORT" ] && { read -rp "代理端口 [${DEFAULT_PROXY_PORT}]: " PROXY_PORT; }
    PROXY_PORT="${PROXY_PORT:-$DEFAULT_PROXY_PORT}"
    [ -z "$API_PORT" ] && { read -rp "API 端口 [${DEFAULT_API_PORT}]: " API_PORT; }
    API_PORT="${API_PORT:-$DEFAULT_API_PORT}"

    echo ""
    log_info "部署配置："
    echo "  服务器:       $SSH_USER@$SERVER_IP:$SSH_PORT"
    echo "  内核版本:     $KERNEL_VERSION"
    echo "  安装目录:     $INSTALL_DIR"
    echo "  代理端口:     $PROXY_PORT"
    echo "  API 端口:     $API_PORT"
    echo "  订阅链接:     ${SUB_URL:0:60}..."
    echo ""
    read -rp "确认开始部署？[Y/n]: " confirm
    [ "$confirm" = "n" ] || [ "$confirm" = "N" ] && { log_warn "已取消"; exit 0; }
}

# ============================================================================
# 第二步：检测服务器架构
# ============================================================================

detect_arch() {
    log_step "检测服务器"

    log_info "连接 $SSH_USER@$SERVER_IP:$SSH_PORT ..."
    REMOTE_ARCH=$(remote_exec "uname -m") || { log_error "SSH 连接失败"; exit 1; }
    REMOTE_OS=$(remote_exec "uname -s")

    [ "$REMOTE_OS" != "Linux" ] && { log_error "仅支持 Linux，当前: $REMOTE_OS"; exit 1; }

    case "$REMOTE_ARCH" in
        x86_64|amd64) ARCH="amd64" ;;
        aarch64|arm64) ARCH="arm64" ;;
        *) log_error "不支持的架构: $REMOTE_ARCH"; exit 1 ;;
    esac

    log_success "系统: $REMOTE_OS $REMOTE_ARCH → $ARCH"
}

# ============================================================================
# 第三步：本地下载
# ============================================================================

download_files() {
    log_step "下载文件（本地）"

    # 内核（从 GitHub 下载原始文件）
    KERNEL_URL="https://github.com/MetaCubeX/mihomo/releases/download/${KERNEL_VERSION}/mihomo-linux-${ARCH}-${KERNEL_VERSION}.gz"
    log_info "下载代理内核 ${KERNEL_VERSION} (${ARCH})..."

    if ! curl -L --fail --progress-bar -o "$TMPDIR/kernel.gz" "$KERNEL_URL"; then
        log_error "下载失败，检查版本: https://github.com/MetaCubeX/mihomo/releases"
        exit 1
    fi
    gzip -d "$TMPDIR/kernel.gz"
    # 重命名为伪装名称
    mv "$TMPDIR/kernel" "$TMPDIR/$APP_NAME"
    chmod +x "$TMPDIR/$APP_NAME"
    log_success "$APP_NAME $(du -h "$TMPDIR/$APP_NAME" | cut -f1)"

    # Geodata
    GEO_BASE="https://github.com/MetaCubeX/meta-rules-dat/releases/download/latest"
    for f in country.mmdb geoip.dat geosite.dat; do
        log_info "下载 $f..."
        curl -sL --fail -o "$TMPDIR/$f" "${GEO_BASE}/$f" || { log_error "下载 $f 失败"; exit 1; }
        log_success "$f $(du -h "$TMPDIR/$f" | cut -f1)"
    done
}

# ============================================================================
# 第四步：传输到服务器
# ============================================================================

upload_files() {
    log_step "传输文件到服务器"

    remote_exec "$S mkdir -p $INSTALL_DIR"

    for f in "$APP_NAME" country.mmdb geoip.dat geosite.dat; do
        log_info "上传 $f ..."
        remote_upload_to "$TMPDIR/$f" "$INSTALL_DIR/$f"
    done

    remote_exec "$S chmod +x $INSTALL_DIR/$APP_NAME"

    REMOTE_VERSION=$(remote_exec "$INSTALL_DIR/$APP_NAME -v" 2>/dev/null || echo "FAIL")
    if echo "$REMOTE_VERSION" | grep -qi "mihomo\|meta"; then
        log_success "内核已安装: $REMOTE_VERSION"
    else
        log_error "安装验证失败"; exit 1
    fi
}

# ============================================================================
# 第五步：配置订阅
# ============================================================================

setup_subscription() {
    log_step "配置订阅"

    log_info "尝试服务器直接下载订阅..."
    RESULT=$(remote_exec "$S curl -sS -o $INSTALL_DIR/config.yaml -w '%{http_code}' -H 'User-Agent: clash.meta' '$SUB_URL'" 2>/dev/null || echo "000")

    if [ "$RESULT" = "200" ]; then
        log_success "订阅下载成功（服务器直连）"
    else
        log_warn "服务器下载失败 (HTTP $RESULT)，改为本地下载后传输"
        curl -sS -o "$TMPDIR/config.yaml" -H "User-Agent: clash.meta" "$SUB_URL"
        [ ! -s "$TMPDIR/config.yaml" ] && { log_error "订阅下载失败"; exit 1; }
        remote_upload_to "$TMPDIR/config.yaml" "$INSTALL_DIR/config.yaml"
        log_success "订阅已传输"
    fi

    log_info "调整配置..."
    local cfg="$INSTALL_DIR/config.yaml"
    # 确保 mixed-port 存在
    remote_exec "grep -q 'mixed-port' $cfg || $S sed -i '1i mixed-port: $PROXY_PORT' $cfg"
    # 设置 external-controller
    if remote_exec "grep -q 'external-controller' $cfg" 2>/dev/null; then
        remote_exec "$S sed -i \"s|external-controller:.*|external-controller: '127.0.0.1:$API_PORT'|\" $cfg"
    else
        remote_exec "$S sed -i \"1a external-controller: '127.0.0.1:$API_PORT'\" $cfg"
    fi
    # 禁用 TUN
    remote_exec "$S sed -i '/tun:/,/enable:/{s/enable: true/enable: false/}' $cfg 2>/dev/null; true"
    # 强制 global 模式（订阅默认 rule）
    remote_exec "$S sed -i 's/^mode: .*/mode: global/' $cfg"

    ACTUAL_PROXY_PORT=$(remote_exec "grep -oP 'mixed-port:\s*\K[0-9]+' $INSTALL_DIR/config.yaml" 2>/dev/null || echo "$PROXY_PORT")
    ACTUAL_API_PORT=$(remote_exec "grep -oP 'external-controller.*:\K[0-9]+' $INSTALL_DIR/config.yaml" 2>/dev/null || echo "$API_PORT")

    log_success "代理端口: $ACTUAL_PROXY_PORT  API 端口: $ACTUAL_API_PORT"
}

# ============================================================================
# 第六步：创建 systemd 服务
# ============================================================================

setup_service() {
    log_step "配置 systemd 服务"

    # 停止旧服务（兼容旧名称和新名称）
    remote_exec "$S systemctl stop mihomo 2>/dev/null; $S systemctl disable mihomo 2>/dev/null; $S systemctl stop $APP_NAME 2>/dev/null; true"

    # 清理旧服务文件
    remote_exec "$S rm -f /etc/systemd/system/mihomo.service 2>/dev/null; true"

    # 写 service 文件（sudo 时用 tee）
    remote_exec "$S tee /etc/systemd/system/${APP_NAME}.service > /dev/null << 'EOF'
[Unit]
Description=ICTyun Network Service
After=network.target

[Service]
Type=simple
ExecStart=$INSTALL_DIR/$APP_NAME -d $INSTALL_DIR
Restart=on-failure
RestartSec=5
LimitNOFILE=65535

[Install]
WantedBy=multi-user.target
EOF"

    remote_exec "$S systemctl daemon-reload && $S systemctl start $APP_NAME && $S systemctl enable $APP_NAME 2>/dev/null"
    sleep 2

    STATUS=$(remote_exec "$S systemctl is-active $APP_NAME" 2>/dev/null || echo "unknown")
    if [ "$STATUS" = "active" ]; then
        log_success "$APP_NAME 已启动并设为开机自启"
    else
        log_error "启动失败，日志："
        remote_exec "$S journalctl -u $APP_NAME -n 20 --no-pager" 2>/dev/null || true
        exit 1
    fi
}

# ============================================================================
# 第七步：安装 mh + mhd 工具
# ============================================================================

install_tools() {
    log_step "安装管理工具 (mh + mhd + mh-auto)"

    # deploy.sh 所在目录
    SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

    # 查找 mh_ictyun.sh
    MH_SRC=""
    for candidate in "$SCRIPT_DIR/mh_ictyun.sh" "$SCRIPT_DIR/mh.sh" "./mh_ictyun.sh"; do
        if [ -f "$candidate" ]; then MH_SRC="$candidate"; break; fi
    done

    # 查找 mhd_ictyun.sh
    MHD_SRC=""
    for candidate in "$SCRIPT_DIR/mhd_ictyun.sh" "$SCRIPT_DIR/mhd.sh" "./mhd_ictyun.sh"; do
        if [ -f "$candidate" ]; then MHD_SRC="$candidate"; break; fi
    done

    # 查找 mh-auto_ictyun.sh
    MHAUTO_SRC=""
    for candidate in "$SCRIPT_DIR/mh-auto_ictyun.sh" "$SCRIPT_DIR/mh-auto.sh" "./mh-auto_ictyun.sh"; do
        if [ -f "$candidate" ]; then MHAUTO_SRC="$candidate"; break; fi
    done

    # 上传 mh
    if [ -n "$MH_SRC" ]; then
        log_info "上传 mh ($(basename "$MH_SRC"))..."
        remote_upload_to "$MH_SRC" "$INSTALL_DIR/mh"
        remote_exec "$S chmod +x $INSTALL_DIR/mh && $S ln -sf $INSTALL_DIR/mh /usr/local/bin/mh"
        log_success "mh 命令行工具已安装"
    else
        log_warn "未找到 mh_ictyun.sh，跳过 mh 安装"
        log_warn "请将 mh_ictyun.sh 放在 deploy.sh 同目录下"
    fi

    # 上传 mhd
    if [ -n "$MHD_SRC" ]; then
        log_info "上传 mhd ($(basename "$MHD_SRC"))..."
        remote_upload_to "$MHD_SRC" "$INSTALL_DIR/mhd"
        remote_exec "$S chmod +x $INSTALL_DIR/mhd && $S ln -sf $INSTALL_DIR/mhd /usr/local/bin/mhd"
        log_success "mhd 交互式控制面板已安装"
    else
        log_warn "未找到 mhd_ictyun.sh，跳过 mhd 安装"
        log_warn "请将 mhd_ictyun.sh 放在 deploy.sh 同目录下"
    fi

    # 上传 mh-auto
    if [ -n "$MHAUTO_SRC" ]; then
        log_info "上传 mh-auto ($(basename "$MHAUTO_SRC"))..."
        remote_upload_to "$MHAUTO_SRC" "$INSTALL_DIR/mh-auto"
        remote_exec "$S chmod +x $INSTALL_DIR/mh-auto && $S ln -sf $INSTALL_DIR/mh-auto /usr/local/bin/mh-auto"
        log_success "mh-auto 自动切换工具已安装"
    else
        log_warn "未找到 mh-auto_ictyun.sh，跳过 mh-auto 安装"
        log_warn "请将 mh-auto_ictyun.sh 放在 deploy.sh 同目录下"
    fi
}

# ============================================================================
# 第八步：Global 模式 + 自动选节点
# ============================================================================

setup_global_mode() {
    log_step "切换到 Global 模式"

    # 写入配置文件，确保重启后仍为 global
    remote_exec "$S sed -i 's/^mode: .*/mode: global/' $INSTALL_DIR/config.yaml"
    # API 运行时也切换
    remote_exec "curl -s -X PATCH http://127.0.0.1:$ACTUAL_API_PORT/configs -H 'Content-Type: application/json' -d '{\"mode\":\"global\"}'" >/dev/null

    log_info "自动选择最优节点..."
    # 先下载到临时文件，避免 pipe+heredoc stdin 冲突
    remote_exec "curl -s http://127.0.0.1:$ACTUAL_API_PORT/proxies/GLOBAL > /tmp/_deploy_proxies.json"
    SELECTED_NODE=$(remote_exec "PYTHONIOENCODING=utf-8 python3 << 'PY'
import json, sys
with open('/tmp/_deploy_proxies.json') as f:
    d = json.load(f)
skip = {'DIRECT', 'REJECT', 'COMPATIBLE', 'PASS'}
nodes = [n for n in d.get('all', []) if n not in skip]
for n in nodes:
    if any(k in n for k in ('美国', 'US', '🇺🇸')):
        print(n); sys.exit(0)
for n in nodes:
    if any(k in n for k in ('日本', 'JP', '🇯🇵')):
        print(n); sys.exit(0)
if nodes:
    print(nodes[0])
PY" 2>/dev/null)
    remote_exec "rm -f /tmp/_deploy_proxies.json" 2>/dev/null

    if [ -n "$SELECTED_NODE" ]; then
        remote_exec "PYTHONIOENCODING=utf-8 python3 << PY
import urllib.request, urllib.parse, json
node = '''$SELECTED_NODE'''
url = 'http://127.0.0.1:$ACTUAL_API_PORT/proxies/GLOBAL'
data = json.dumps({'name': node}).encode()
req = urllib.request.Request(url, data=data, method='PUT', headers={'Content-Type': 'application/json'})
urllib.request.urlopen(req)
PY" 2>/dev/null
        log_success "已选择节点: $SELECTED_NODE"
    else
        log_warn "未能自动选择，请手动: mh nodes GLOBAL"
    fi
}

# ============================================================================
# 第九步：验证
# ============================================================================

verify() {
    log_step "验证代理"

    local pass_count=0

    for target in "Google:https://www.google.com" "Anthropic API:https://api.anthropic.com" "OpenAI API:https://api.openai.com"; do
        NAME="${target%%:*}"
        URL="${target#*:}"
        printf "  %-16s " "$NAME:"
        CODE=$(remote_exec "curl -x http://127.0.0.1:$ACTUAL_PROXY_PORT -o /dev/null -w '%{http_code}' -sS --connect-timeout 15 '$URL'" 2>/dev/null || echo "000")
        if [ "$CODE" != "000" ]; then
            echo -e "${GREEN}OK${NC} (HTTP $CODE)"
            pass_count=$((pass_count + 1))
        else
            echo -e "${RED}FAIL${NC}"
        fi
    done

    printf "  %-16s " "出口 IP:"
    EXIT_INFO=$(remote_exec "curl -x http://127.0.0.1:$ACTUAL_PROXY_PORT -sS https://ipinfo.io/json 2>/dev/null | python3 -c \"
import json, sys
d = json.load(sys.stdin)
print(f\\\"{d.get('ip')} ({d.get('city')}, {d.get('region')}, {d.get('country')})\\\")
\"" 2>/dev/null || echo "无法获取")
    echo "$EXIT_INFO"

    echo ""
    if [ "$pass_count" -eq 3 ]; then
        log_success "全部验证通过！"
    elif [ "$pass_count" -gt 0 ]; then
        log_warn "部分通过 ($pass_count/3)，可尝试切换节点: mh nodes GLOBAL"
    else
        log_error "验证失败，请检查节点: mh log / mh test"
    fi
}

# ============================================================================
# 第十步：清理旧安装（如果存在 /opt/mihomo）
# ============================================================================

cleanup_old_install() {
    # 检测是否存在旧的 /opt/mihomo 安装
    OLD_EXISTS=$(remote_exec "test -d /opt/mihomo && echo 'yes' || echo 'no'" 2>/dev/null)
    if [ "$OLD_EXISTS" = "yes" ] && [ "$INSTALL_DIR" != "/opt/mihomo" ]; then
        log_info "检测到旧安装 /opt/mihomo，正在清理..."
        remote_exec "$S systemctl stop mihomo 2>/dev/null; $S systemctl disable mihomo 2>/dev/null; true"
        remote_exec "$S rm -f /etc/systemd/system/mihomo.service 2>/dev/null; true"
        remote_exec "$S rm -f /usr/local/bin/mh 2>/dev/null; true"
        remote_exec "$S rm -rf /opt/mihomo 2>/dev/null; true"
        remote_exec "$S systemctl daemon-reload 2>/dev/null; true"
        log_success "旧安装已清理"
    fi
}

# ============================================================================
# 最终输出
# ============================================================================

print_summary() {
    echo ""
    echo -e "${GREEN}════════════════════════════════════════════${NC}"
    echo -e "${GREEN}  代理服务部署完成！${NC}"
    echo -e "${GREEN}════════════════════════════════════════════${NC}"
    echo ""
    echo "  服务器:     $SERVER_IP"
    echo "  代理地址:   http://127.0.0.1:$ACTUAL_PROXY_PORT"
    echo "  SOCKS5:     socks5://127.0.0.1:$ACTUAL_PROXY_PORT"
    echo "  API:        http://127.0.0.1:$ACTUAL_API_PORT"
    echo "  安装目录:   $INSTALL_DIR"
    echo "  服务名:     $APP_NAME"
    echo ""
    echo "  常用命令（SSH 后使用）:"
    echo "    mhd                 交互式控制面板（推荐）"
    echo "    mhd status          快速查看状态"
    echo "    mh test             测试连通性"
    echo "    mh ip               查看出口 IP"
    echo "    mh mode global      全局模式"
    echo "    mh nodes GLOBAL     查看节点"
    echo "    mh select GLOBAL x  切换节点"
    echo "    mh speedtest 美国   测速"
    echo ""
    echo "  Sub2API 账号代理填写:"
    echo "    http://127.0.0.1:$ACTUAL_PROXY_PORT"
    echo ""
}

# ============================================================================
# 主流程
# ============================================================================

main() {
    echo ""
    echo -e "${CYAN}╔══════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║  代理服务一键部署脚本                  ║${NC}"
    echo -e "${CYAN}║  本地下载 → 传输 → 安装 → 验证        ║${NC}"
    echo -e "${CYAN}╚══════════════════════════════════════╝${NC}"
    echo ""

    check_local_deps
    parse_args "$@"
    collect_input
    detect_arch
    setup_sudo
    download_files
    upload_files
    setup_subscription
    cleanup_old_install
    setup_service
    install_tools
    setup_global_mode
    verify
    print_summary
}

main "$@"
