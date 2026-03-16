#!/bin/bash
# mhd - 代理交互式控制面板
# 一条命令查看状态 + 切换模式/组/节点

APP_NAME="ictyun"
CONFIG="/opt/$APP_NAME/config.yaml"

# 非 root 时自动加 sudo
S=""; [ "$(id -u)" -ne 0 ] && S="sudo"

# 确保 Python 在 locale 不完整的系统上也能正常输出 UTF-8
export PYTHONIOENCODING=utf-8

PROXY_PORT=$(grep -oP 'mixed-port:\s*\K[0-9]+' "$CONFIG" 2>/dev/null || echo "7897")
API_PORT=$(grep -oP 'external-controller.*:\K[0-9]+' "$CONFIG" 2>/dev/null || echo "9097")
API="http://127.0.0.1:$API_PORT"

# 颜色
R='\033[0;31m'; G='\033[0;32m'; Y='\033[1;33m'; B='\033[0;34m'; C='\033[0;36m'; W='\033[1;37m'; D='\033[0;90m'; NC='\033[0m'

# ────────────────────────────────────────────
# 显示当前状态总览
# ────────────────────────────────────────────
show_status() {
    echo ""
    echo -e "${C}═══════════════════════════════════════════${NC}"
    echo -e "${C}  代理控制面板${NC}"
    echo -e "${C}═══════════════════════════════════════════${NC}"

    # 服务状态
    STATUS=$($S systemctl is-active "$APP_NAME" 2>/dev/null)
    if [ "$STATUS" = "active" ]; then
        echo -e "  服务状态:  ${G}●${NC} 运行中"
    else
        echo -e "  服务状态:  ${R}●${NC} 已停止"
        echo -e "${C}═══════════════════════════════════════════${NC}"
        return
    fi

    # 模式
    MODE=$(curl -s "$API/configs" 2>/dev/null | python3 -c "import json,sys; print(json.load(sys.stdin).get('mode','?'))" 2>/dev/null || echo "?")
    case "$MODE" in
        global) MODE_DISPLAY="${G}Global${NC} (全局代理)" ;;
        rule)   MODE_DISPLAY="${Y}Rule${NC} (规则分流)" ;;
        direct) MODE_DISPLAY="${D}Direct${NC} (直连)" ;;
        *)      MODE_DISPLAY="$MODE" ;;
    esac
    echo -e "  当前模式:  $MODE_DISPLAY"

    # 代理组和当前节点
    GROUPS_JSON=$(curl -s "$API/proxies" 2>/dev/null)
    if [ -n "$GROUPS_JSON" ]; then
        echo ""
        echo -e "  ${W}代理组:${NC}"
        echo "$GROUPS_JSON" | python3 -c "
import json, sys
data = json.load(sys.stdin).get('proxies', {})
for name in sorted(data):
    info = data[name]
    t = info.get('type', '')
    if t in ('Selector', 'URLTest', 'Fallback'):
        now = info.get('now', '?')
        count = len(info.get('all', []))
        tmap = {'Selector': '\u624b\u52a8', 'URLTest': '\u81ea\u52a8', 'Fallback': '\u6545\u969c\u8f6c\u79fb'}
        tname = tmap.get(t, t)
        print(f'    {tname:6} {name} \u2192 {now}  ({count}\u8282\u70b9)')
" 2>/dev/null
    fi

    # 出口 IP（后台获取，超时跳过）
    echo ""
    echo -ne "  出口 IP:   "
    IP_INFO=$(curl -x "http://127.0.0.1:$PROXY_PORT" -sS --connect-timeout 5 https://ipinfo.io/json 2>/dev/null | python3 -c "
import json, sys
d = json.load(sys.stdin)
print(f\"{d.get('ip')} ({d.get('city')}, {d.get('country')})\")" 2>/dev/null)
    if [ -n "$IP_INFO" ]; then
        echo -e "${G}$IP_INFO${NC}"
    else
        echo -e "${D}获取中超时${NC}"
    fi

    echo -e "${C}═══════════════════════════════════════════${NC}"
}

# ────────────────────────────────────────────
# 交互菜单
# ────────────────────────────────────────────
show_menu() {
    echo ""
    echo -e "  ${W}操作:${NC}"
    echo -e "    ${G}1${NC}) 切换模式 (Global/Rule/Direct)"
    echo -e "    ${G}2${NC}) 切换节点"
    echo -e "    ${G}3${NC}) 测速选节点"
    echo -e "    ${G}4${NC}) 测试连通性"
    echo -e "    ${G}5${NC}) 刷新状态"
    echo -e "    ${G}q${NC}) 退出"
    echo ""
}

# ────────────────────────────────────────────
# 切换模式
# ────────────────────────────────────────────
switch_mode() {
    echo ""
    echo -e "  选择模式:"
    echo -e "    ${G}1${NC}) Global  - 所有流量走代理"
    echo -e "    ${G}2${NC}) Rule    - 按规则分流（国内直连）"
    echo -e "    ${G}3${NC}) Direct  - 全部直连（临时关闭代理）"
    echo ""
    read -rp "  选择 [1-3]: " choice
    case "$choice" in
        1) MODE="global" ;;
        2) MODE="rule" ;;
        3) MODE="direct" ;;
        *) echo "  取消"; return ;;
    esac
    curl -s -X PATCH "$API/configs" -H "Content-Type: application/json" -d "{\"mode\":\"$MODE\"}" >/dev/null
    echo -e "  ${G}已切换到 $MODE 模式${NC}"
}

# ────────────────────────────────────────────
# 切换节点（交互式）
# ────────────────────────────────────────────
switch_node() {
    # 先选择代理组
    echo ""
    echo -e "  ${W}选择代理组:${NC}"
    GROUPS=$(curl -s "$API/proxies" 2>/dev/null | python3 -c "
import json, sys
data = json.load(sys.stdin).get('proxies', {})
groups = []
for name in sorted(data):
    info = data[name]
    if info.get('type') == 'Selector':
        groups.append(name)
for i, g in enumerate(groups, 1):
    print(f'{i}:{g}')
" 2>/dev/null)

    if [ -z "$GROUPS" ]; then
        echo "  无可用代理组"
        return
    fi

    # 显示组列表
    IDX=1
    while IFS=: read -r num name; do
        echo -e "    ${G}$num${NC}) $name"
        IDX=$((IDX + 1))
    done <<< "$GROUPS"

    echo ""
    read -rp "  选择组 [序号]: " group_choice
    SELECTED_GROUP=$(echo "$GROUPS" | sed -n "${group_choice}p" | cut -d: -f2)
    if [ -z "$SELECTED_GROUP" ]; then
        echo "  取消"
        return
    fi

    # 获取该组的节点列表并测速
    echo ""
    ENCODED=$(python3 -c "import urllib.parse; print(urllib.parse.quote('$SELECTED_GROUP'))")

    echo -e "  ${Y}测速中...${NC}"
    curl -s "$API/group/$ENCODED/delay?url=http://www.gstatic.com/generate_204&timeout=5000" >/dev/null 2>&1

    echo -e "  ${W}$SELECTED_GROUP 的节点:${NC}"

    # 获取节点列表和延迟
    NODE_LIST=$(curl -s "$API/proxies/$ENCODED" 2>/dev/null | API_PORT_VAL="$API_PORT" python3 -c '
import json, sys, urllib.parse, urllib.request, os
api_port = os.environ.get("API_PORT_VAL", "9097")
d = json.load(sys.stdin)
now = d.get("now", "")
nodes = d.get("all", [])
for i, n in enumerate(nodes, 1):
    marker = " \u2190" if n == now else ""
    encoded = urllib.parse.quote(n)
    try:
        resp = urllib.request.urlopen(f"http://127.0.0.1:{api_port}/proxies/{encoded}", timeout=2)
        info = json.loads(resp.read())
        history = info.get("history", [])
        delay = history[-1].get("delay", 0) if history else 0
    except:
        delay = 0
    print(f"{i}:{n}:{delay}:{marker}")
' 2>/dev/null)

    CURRENT_NODE=$(curl -s "$API/proxies/$ENCODED" 2>/dev/null | python3 -c "import json,sys; print(json.load(sys.stdin).get('now',''))" 2>/dev/null)

    # 显示节点（带延迟和颜色）
    echo "$NODE_LIST" | while IFS=: read -r num name delay marker; do
        if [ "$delay" -gt 0 ] 2>/dev/null; then
            if [ "$delay" -lt 200 ]; then
                delay_str="${G}${delay}ms${NC}"
            elif [ "$delay" -lt 500 ]; then
                delay_str="${Y}${delay}ms${NC}"
            else
                delay_str="${R}${delay}ms${NC}"
            fi
        else
            delay_str="${D}超时${NC}"
        fi

        if [ -n "$marker" ]; then
            echo -e "    ${G}${num}${NC}) $delay_str  ${W}${name}${NC}  ${G}←当前${NC}"
        else
            echo -e "    ${D}${num}${NC}) $delay_str  ${name}"
        fi
    done

    TOTAL=$(echo "$NODE_LIST" | wc -l)
    echo ""
    echo -e "  共 $TOTAL 个节点, 当前: ${G}$CURRENT_NODE${NC}"

    # 支持输入序号或关键词过滤
    echo ""
    read -rp "  输入序号（或关键词过滤，如 '美国'）: " node_input

    # 判断是否为数字
    if [[ "$node_input" =~ ^[0-9]+$ ]]; then
        TARGET_NODE=$(echo "$NODE_LIST" | sed -n "${node_input}p" | cut -d: -f2)
    else
        # 关键词过滤
        echo ""
        echo -e "  ${W}匹配 '$node_input' 的节点:${NC}"
        FILTERED=$(echo "$NODE_LIST" | grep -i "$node_input")
        if [ -z "$FILTERED" ]; then
            echo "  未找到匹配节点"
            return
        fi
        FIDX=1
        echo "$FILTERED" | while IFS=: read -r num name delay marker; do
            if [ "$delay" -gt 0 ] 2>/dev/null; then
                if [ "$delay" -lt 200 ]; then delay_str="${G}${delay}ms${NC}"
                elif [ "$delay" -lt 500 ]; then delay_str="${Y}${delay}ms${NC}"
                else delay_str="${R}${delay}ms${NC}"; fi
            else delay_str="${D}超时${NC}"; fi

            if [ -n "$marker" ]; then
                echo -e "    ${G}${FIDX}${NC}) $delay_str  ${W}${name}${NC}  ${G}←当前${NC}"
            else
                echo -e "    ${D}${FIDX}${NC}) $delay_str  ${name}"
            fi
            FIDX=$((FIDX + 1))
        done

        echo ""
        read -rp "  选择序号: " filter_choice
        TARGET_NODE=$(echo "$FILTERED" | sed -n "${filter_choice}p" | cut -d: -f2)
    fi

    if [ -z "$TARGET_NODE" ]; then
        echo "  取消"
        return
    fi

    # 执行切换
    RESULT=$(curl -s -X PUT "$API/proxies/$ENCODED" \
        -H "Content-Type: application/json" \
        -d "{\"name\":\"$TARGET_NODE\"}")

    if [ -z "$RESULT" ]; then
        echo -e "  ${G}已切换: $SELECTED_GROUP → $TARGET_NODE${NC}"
    else
        echo -e "  ${R}切换失败: $RESULT${NC}"
    fi
}

# ────────────────────────────────────────────
# 测速并切换
# ────────────────────────────────────────────
speedtest_switch() {
    echo ""
    read -rp "  输入关键词过滤（如 '美国', 回车测全部）: " keyword

    echo -e "  ${Y}测速中...${NC}"
    RESULTS=$(curl -s "$API/proxies" 2>/dev/null | python3 -c "
import json, sys, urllib.request, urllib.parse
data = json.load(sys.stdin).get('proxies', {})
skip = {'Selector','URLTest','Fallback','Direct','Reject','Compatible','Pass',''}
nodes = [(n, i) for n, i in data.items() if i.get('type','') not in skip]
filt = '$keyword'
if filt:
    nodes = [(n, i) for n, i in nodes if filt in n]
results = []
for name, _ in nodes:
    encoded = urllib.parse.quote(name)
    try:
        resp = urllib.request.urlopen(f'http://127.0.0.1:$API_PORT/proxies/{encoded}/delay?timeout=5000&url=http://www.gstatic.com/generate_204', timeout=6)
        delay = json.loads(resp.read()).get('delay', 0)
        if delay > 0:
            results.append((delay, name))
    except:
        pass
results.sort()
for i, (delay, name) in enumerate(results, 1):
    print(f'{i}:{delay}:{name}')
" 2>/dev/null)

    if [ -z "$RESULTS" ]; then
        echo "  无可用节点"
        return
    fi

    echo ""
    echo -e "  ${W}测速结果（延迟低→高）:${NC}"
    echo "$RESULTS" | while IFS=: read -r idx delay name; do
        if [ "$idx" -le 3 ]; then
            echo -e "    ${G}${idx}${NC}) ${G}${delay}ms${NC}  ${name}"
        else
            echo -e "    ${D}${idx}${NC}) ${delay}ms  ${name}"
        fi
    done

    echo ""
    read -rp "  选择序号切换到该节点（回车跳过）: " choice
    if [ -z "$choice" ]; then return; fi

    TARGET=$(echo "$RESULTS" | sed -n "${choice}p" | cut -d: -f3)
    if [ -z "$TARGET" ]; then
        echo "  无效选择"
        return
    fi

    # 切换 GLOBAL 组
    RESULT=$(curl -s -X PUT "$API/proxies/GLOBAL" \
        -H "Content-Type: application/json" \
        -d "{\"name\":\"$TARGET\"}")
    if [ -z "$RESULT" ]; then
        echo -e "  ${G}已切换 GLOBAL → $TARGET${NC}"
    else
        echo -e "  ${R}切换失败: $RESULT${NC}"
    fi
}

# ────────────────────────────────────────────
# 测试连通性
# ────────────────────────────────────────────
test_connectivity() {
    echo ""
    echo -e "  ${W}连通性测试:${NC}"
    for target in "Google:https://www.google.com" "Claude API:https://api.anthropic.com" "OpenAI API:https://api.openai.com"; do
        NAME="${target%%:*}"
        URL="${target#*:}"
        printf "    %-14s " "$NAME:"
        CODE=$(curl -x "http://127.0.0.1:$PROXY_PORT" -o /dev/null -w "%{http_code}" -sS --connect-timeout 10 "$URL" 2>/dev/null || echo "000")
        if [ "$CODE" != "000" ]; then
            echo -e "${G}OK${NC} (HTTP $CODE)"
        else
            echo -e "${R}FAIL${NC}"
        fi
    done
}

# ────────────────────────────────────────────
# 主循环
# ────────────────────────────────────────────
main() {
    # 非交互模式：mhd status
    if [ "$1" = "status" ] || [ "$1" = "s" ]; then
        show_status
        exit 0
    fi

    # 交互模式
    while true; do
        show_status
        show_menu
        read -rp "  选择操作: " action
        case "$action" in
            1) switch_mode ;;
            2) switch_node ;;
            3) speedtest_switch ;;
            4) test_connectivity ;;
            5) continue ;;  # 刷新
            q|Q|exit) echo ""; break ;;
            *) echo -e "  ${R}无效选择${NC}" ;;
        esac
        echo ""
        read -rp "  按回车继续..." _
    done
}

main "$@"
