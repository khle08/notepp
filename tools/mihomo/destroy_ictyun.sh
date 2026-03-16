#!/bin/bash
#
# ictyun 自毁脚本 — 彻底清除所有代理相关痕迹
#
# 用法（在服务器上执行）：
#   bash destroy_ictyun.sh
#
# 或从本地远程执行：
#   sshpass -p "密码" ssh root@服务器IP 'bash -s' < destroy_ictyun.sh
#
# 清除内容：
#   - systemd 服务（ictyun / mihomo）
#   - 安装目录（/opt/ictyun / /opt/mihomo）
#   - 快捷命令（/usr/local/bin/mh、mhd）
#   - 系统日志中的相关记录
#   - bash 历史中的相关记录
#   - /tmp 中的残留文件
#

set -e

R='\033[0;31m'; G='\033[0;32m'; Y='\033[1;33m'; D='\033[0;90m'; NC='\033[0m'

# 自动检测是否需要 sudo
S=""
if [ "$(id -u)" -ne 0 ]; then
    if sudo -n true 2>/dev/null; then
        S="sudo"
    elif [ -n "$1" ] && echo "$1" | sudo -S true 2>/dev/null; then
        S="sudo"
    else
        echo -e "${R}需要 root 或 sudo 权限${NC}"
        echo "用法: bash destroy_ictyun.sh [sudo密码]"
        exit 1
    fi
fi

echo ""
echo -e "${R}╔══════════════════════════════════════════╗${NC}"
echo -e "${R}║          自毁脚本 — 清除所有痕迹          ║${NC}"
echo -e "${R}╚══════════════════════════════════════════╝${NC}"
echo ""
echo -e "即将清除以下内容："
echo -e "  ${R}●${NC} systemd 服务 (ictyun / mihomo)"
echo -e "  ${R}●${NC} 安装目录 (/opt/ictyun /opt/mihomo)"
echo -e "  ${R}●${NC} 快捷命令 (mh / mhd)"
echo -e "  ${R}●${NC} 系统日志中的相关记录"
echo -e "  ${R}●${NC} bash 历史中的相关记录"
echo -e "  ${R}●${NC} /tmp 中的残留文件"
echo ""
echo -e "${Y}此操作不可逆！${NC}"
echo ""
read -rp "输入 YES 确认执行: " confirm
if [ "$confirm" != "YES" ]; then
    echo "已取消"
    exit 0
fi

echo ""

# ── 1. 停止并删除 systemd 服务 ──
for svc in ictyun mihomo; do
    if systemctl list-unit-files "${svc}.service" &>/dev/null; then
        echo -e "${D}[1/6]${NC} 停止服务 ${svc}..."
        $S systemctl stop "$svc" 2>/dev/null || true
        $S systemctl disable "$svc" 2>/dev/null || true
        $S rm -f "/etc/systemd/system/${svc}.service"
    fi
done
$S systemctl daemon-reload 2>/dev/null || true
echo -e "${G}[1/6]${NC} systemd 服务已清除"

# ── 2. 删除安装目录 ──
echo -e "${D}[2/6]${NC} 删除安装目录..."
$S rm -rf /opt/ictyun /opt/mihomo
echo -e "${G}[2/6]${NC} 安装目录已清除"

# ── 3. 删除快捷命令 ──
echo -e "${D}[3/6]${NC} 删除快捷命令..."
$S rm -f /usr/local/bin/mh /usr/local/bin/mhd
echo -e "${G}[3/6]${NC} 快捷命令已清除"

# ── 4. 清除系统日志 ──
echo -e "${D}[4/6]${NC} 清除系统日志..."
for svc in ictyun mihomo; do
    $S journalctl --rotate 2>/dev/null || true
    $S journalctl --vacuum-time=1s -u "$svc" 2>/dev/null || true
done
$S rm -rf /run/log/journal/* 2>/dev/null || true
$S journalctl --flush 2>/dev/null || true
echo -e "${G}[4/6]${NC} 系统日志已清除"

# ── 5. 清除 /tmp 残留 ──
echo -e "${D}[5/6]${NC} 清除临时文件..."
rm -f /tmp/mh_* /tmp/mhd_* /tmp/ictyun* /tmp/mihomo* /tmp/kernel* /tmp/country.mmdb /tmp/geoip.dat /tmp/geosite.dat /tmp/_deploy_*
echo -e "${G}[5/6]${NC} 临时文件已清除"

# ── 6. 清除 bash 历史中的相关记录 ──
echo -e "${D}[6/6]${NC} 清除历史记录..."
for histfile in /root/.bash_history /home/*/.bash_history; do
    if [ -f "$histfile" ]; then
        $S sed -i '/ictyun\|mihomo\|mh \|mhd\|clash\|proxy.*7897\|127\.0\.0\.1:9097\|destroy_ictyun/d' "$histfile" 2>/dev/null || true
    fi
done
# 清除当前 session 的历史
history -c 2>/dev/null || true
history -w 2>/dev/null || true
echo -e "${G}[6/6]${NC} 历史记录已清除"

# ── 清理部署留下的临时 sudoers 规则 ──
$S rm -f /etc/sudoers.d/_deploy_tmp 2>/dev/null || true

# ── 最终验证 ──
echo ""
echo -e "${G}══════ 验证 ══════${NC}"

CLEAN=true
for check in "/opt/ictyun" "/opt/mihomo" "/usr/local/bin/mh" "/usr/local/bin/mhd" "/etc/systemd/system/ictyun.service" "/etc/systemd/system/mihomo.service"; do
    if [ -e "$check" ]; then
        echo -e "  ${R}残留:${NC} $check"
        CLEAN=false
    fi
done

for svc in ictyun mihomo; do
    if systemctl is-active "$svc" &>/dev/null; then
        echo -e "  ${R}残留:${NC} 服务 $svc 仍在运行"
        CLEAN=false
    fi
done

if ss -tlnp 2>/dev/null | grep -q ':7897\|:9097'; then
    echo -e "  ${R}残留:${NC} 端口 7897/9097 仍被占用"
    CLEAN=false
fi

if $CLEAN; then
    echo -e "  ${G}全部清除完毕，无任何残留${NC}"
else
    echo -e "  ${Y}存在残留项，请手动检查${NC}"
fi

echo ""
