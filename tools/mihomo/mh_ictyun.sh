#!/bin/bash
APP_NAME="ictyun"
INSTALL_DIR="/opt/$APP_NAME"
CONFIG="$INSTALL_DIR/config.yaml"

# 非 root 时自动加 sudo
S=""; [ "$(id -u)" -ne 0 ] && S="sudo"

# 确保 Python 在 locale 不完整的系统上也能正常输出 UTF-8
export PYTHONIOENCODING=utf-8

PROXY_PORT=$(grep -oP 'mixed-port:\s*\K[0-9]+' "$CONFIG" 2>/dev/null || echo "7897")
API_PORT=$(grep -oP 'external-controller.*:\K[0-9]+' "$CONFIG" 2>/dev/null || echo "9097")
API="http://127.0.0.1:$API_PORT"

case "$1" in
  start)    $S systemctl start "$APP_NAME" && echo "已启动" ;;
  stop)     $S systemctl stop "$APP_NAME" && echo "已停止" ;;
  restart)  $S systemctl restart "$APP_NAME" && echo "已重启" ;;
  status)   $S systemctl status "$APP_NAME" --no-pager ;;
  log)      $S journalctl -u "$APP_NAME" -f ;;

  mode)
    if [ -z "$2" ]; then
      MODE=$(curl -s "$API/configs" | python3 -c "import json,sys; print(json.load(sys.stdin).get('mode','unknown'))" 2>/dev/null)
      echo "当前模式: $MODE"
    else
      curl -s -X PATCH "$API/configs" -H "Content-Type: application/json" -d "{\"mode\":\"$2\"}" >/dev/null
      echo "已切换到 $2 模式"
    fi
    ;;

  groups)
    curl -s "$API/proxies" | python3 -c '
import json, sys
data = json.load(sys.stdin).get("proxies", {})
for name in sorted(data):
    info = data[name]
    t = info.get("type", "")
    if t in ("Selector", "URLTest", "Fallback"):
        now = info.get("now", "?")
        count = len(info.get("all", []))
        print(f"  [{t:10}] {name} -> {now}  ({count}\u4e2a\u8282\u70b9)")
'
    ;;

  nodes)
    GROUP="${2:-GLOBAL}"
    ENCODED=$(python3 -c "import urllib.parse; print(urllib.parse.quote('$GROUP'))")
    # 先触发组内测速
    echo "测速中..."
    curl -s "$API/group/$ENCODED/delay?url=http://www.gstatic.com/generate_204&timeout=5000" >/dev/null 2>&1
    sleep 1
    # 重新拉取带延迟的数据并显示
    API_PORT_VAL="$API_PORT" GROUP_NAME="$GROUP" curl -s --retry 2 --retry-delay 1 "$API/proxies/$ENCODED" | API_PORT_VAL="$API_PORT" GROUP_NAME="$GROUP" python3 -c '
import json, sys, urllib.parse, urllib.request, os

api_port = os.environ.get("API_PORT_VAL", "9097")
group = os.environ.get("GROUP_NAME", "GLOBAL")
d = json.load(sys.stdin)
now = d.get("now", "")
all_names = d.get("all", [])
print(f"\u7ec4: {group}  \u5f53\u524d: {now}  \u5171 {len(all_names)} \u4e2a\u8282\u70b9")
print()
for i, name in enumerate(all_names, 1):
    encoded = urllib.parse.quote(name)
    try:
        resp = urllib.request.urlopen(f"http://127.0.0.1:{api_port}/proxies/{encoded}", timeout=2)
        info = json.loads(resp.read())
        history = info.get("history", [])
        delay = history[-1].get("delay", 0) if history else 0
    except:
        delay = 0

    is_current = name == now
    G = "\033[0;32m"; Y = "\033[1;33m"; R = "\033[0;31m"; D = "\033[0;90m"; W = "\033[1;37m"; NC = "\033[0m"

    if delay > 0:
        if delay < 200:   dc = G
        elif delay < 500: dc = Y
        else:             dc = R
        delay_str = f"{dc}{delay:>5}ms{NC}"
    else:
        delay_str = f"{D}  \u8d85\u65f6{NC}"

    marker = f"  {G}\u2190\u5f53\u524d{NC}" if is_current else ""
    name_str = f"{W}{name}{NC}" if is_current else name
    print(f"  {i:3}. {delay_str}  {name_str}{marker}")
'
    ;;

  select)
    if [ -z "$2" ] || [ -z "$3" ]; then
      echo "用法: mh select <组名> <节点名>"
      exit 1
    fi
    ENCODED=$(python3 -c "import urllib.parse; print(urllib.parse.quote('$2'))")
    RESULT=$(curl -s -X PUT "$API/proxies/$ENCODED" -H "Content-Type: application/json" -d "{\"name\":\"$3\"}")
    if [ -z "$RESULT" ]; then echo "OK: $2 -> $3"; else echo "失败: $RESULT"; fi
    ;;

  delay)
    if [ -z "$2" ]; then echo "用法: mh delay <节点名>"; exit 1; fi
    ENCODED=$(python3 -c "import urllib.parse; print(urllib.parse.quote('$2'))")
    RESULT=$(curl -s "$API/proxies/$ENCODED/delay?timeout=5000&url=http://www.gstatic.com/generate_204")
    echo "$2: $RESULT"
    ;;

  ip)
    curl -x "http://127.0.0.1:$PROXY_PORT" -sS https://ipinfo.io/json 2>/dev/null | python3 -c "
import json, sys
try:
    d = json.load(sys.stdin)
    print(f\"IP: {d.get('ip')}  \u5730\u533a: {d.get('city')}, {d.get('region')}, {d.get('country')}  ISP: {d.get('org')}\")
except:
    print('\u65e0\u6cd5\u83b7\u53d6 IP \u4fe1\u606f')
"
    ;;

  conns)
    curl -s "$API/connections" | python3 -c '
import json, sys
d = json.load(sys.stdin)
conns = d.get("connections") or []
up = d.get("uploadTotal", 0) / 1024 / 1024
down = d.get("downloadTotal", 0) / 1024 / 1024
print(f"\u8fde\u63a5\u6570: {len(conns)}  \u4e0a\u4f20: {up:.1f}MB  \u4e0b\u8f7d: {down:.1f}MB")
for c in conns[:15]:
    m = c.get("metadata", {})
    host = m.get("host", "") or m.get("destinationIP", "")
    port = m.get("destinationPort", "")
    rule = c.get("rule", "")
    chains = " -> ".join(c.get("chains", []))
    print(f"  {host}:{port}  {rule}  {chains}")
'
    ;;

  flush)
    curl -s -X DELETE "$API/connections" >/dev/null
    echo "已关闭所有连接"
    ;;

  reload)
    curl -s -X PUT "$API/configs?force=true" -H "Content-Type: application/json" -d "{\"path\":\"$INSTALL_DIR/config.yaml\"}" >/dev/null
    echo "配置已热重载"
    ;;

  test)
    echo "测试代理连通性..."
    for target in "Google:https://www.google.com" "Anthropic:https://api.anthropic.com" "OpenAI:https://api.openai.com"; do
      NAME="${target%%:*}"; URL="${target#*:}"
      printf "  %-14s " "$NAME:"
      CODE=$(curl -x "http://127.0.0.1:$PROXY_PORT" -o /dev/null -w "%{http_code}" -sS --connect-timeout 10 "$URL" 2>/dev/null || echo "000")
      if [ "$CODE" != "000" ]; then echo "OK (HTTP $CODE)"; else echo "FAIL"; fi
    done
    printf "  %-14s " "出口 IP:"
    curl -x "http://127.0.0.1:$PROXY_PORT" -sS https://ipinfo.io/json 2>/dev/null | python3 -c "
import json, sys
d = json.load(sys.stdin)
print(f\"{d.get('ip')} ({d.get('city')}, {d.get('country')})\")" 2>/dev/null || echo "无法获取"
    ;;

  update-sub)
    if [ -z "$2" ]; then echo "用法: mh update-sub <订阅链接>"; exit 1; fi
    echo "下载订阅..."
    $S curl -sS -o "$INSTALL_DIR/config.yaml" -H "User-Agent: clash.meta" "$2"
    # 订阅默认 mode: rule，强制改为 global
    $S sed -i 's/^mode: .*/mode: global/' "$INSTALL_DIR/config.yaml"
    curl -s -X PUT "$API/configs?force=true" -H "Content-Type: application/json" -d "{\"path\":\"$INSTALL_DIR/config.yaml\"}" >/dev/null
    echo "订阅已更新并重载（已设为 global 模式）"
    ;;

  speedtest)
    FILTER="${2:-}"
    curl -s "$API/proxies" | python3 -c "
import json, sys, urllib.request, urllib.parse
data = json.load(sys.stdin).get('proxies', {})
skip = {'Selector','URLTest','Fallback','Direct','Reject','Compatible','Pass',''}
nodes = [(n, i) for n, i in data.items() if i.get('type','') not in skip]
filt = '$FILTER'
if filt: nodes = [(n, i) for n, i in nodes if filt in n]
print(f'\u6d4b\u8bd5 {len(nodes)} \u4e2a\u8282\u70b9...')
results = []
for name, _ in nodes:
    encoded = urllib.parse.quote(name)
    try:
        resp = urllib.request.urlopen(f'http://127.0.0.1:$API_PORT/proxies/{encoded}/delay?timeout=5000&url=http://www.gstatic.com/generate_204', timeout=6)
        delay = json.loads(resp.read()).get('delay', 0)
        results.append((delay, name))
        print(f'  {delay:5}ms  {name}')
    except: print(f'  \u8d85\u65f6     {name}')
results.sort()
if results: print(f'\n\u6700\u5feb: {results[0][1]} ({results[0][0]}ms)')
" 2>/dev/null
    ;;

  *)
    echo "代理快捷操作工具"
    echo ""
    echo "服务管理:"
    echo "  mh start              启动代理"
    echo "  mh stop               停止代理"
    echo "  mh restart            重启代理"
    echo "  mh status             查看运行状态"
    echo "  mh log                查看实时日志"
    echo ""
    echo "模式切换:"
    echo "  mh mode               查看当前模式"
    echo "  mh mode global        全局模式"
    echo "  mh mode rule          规则模式"
    echo "  mh mode direct        直连模式"
    echo ""
    echo "节点管理:"
    echo "  mh groups             查看所有代理组"
    echo "  mh nodes [组名]       查看节点列表（默认 GLOBAL）"
    echo "  mh select 组名 节点名  切换节点"
    echo "  mh delay 节点名       测试延迟"
    echo "  mh speedtest [关键词] 批量测速"
    echo ""
    echo "信息查看:"
    echo "  mh ip                 查看出口 IP"
    echo "  mh conns              活跃连接"
    echo "  mh flush              关闭所有连接"
    echo "  mh test               测试连通性"
    echo ""
    echo "配置管理:"
    echo "  mh reload             热重载配置"
    echo "  mh update-sub <链接>  更新订阅"
    ;;
esac
