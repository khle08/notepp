#!/bin/bash
#
# mh-auto - 自动选择最低延迟节点
#
# 用法:
#   mh-auto                     立即测速并切换到最快节点
#   mh-auto --country 日本       指定国家关键词
#   mh-auto --group ChatGPT     指定代理组（默认 GLOBAL）
#   mh-auto --interval 5        安装 cron 定时任务（每 N 分钟）
#   mh-auto --stop              移除 cron 定时任务
#   mh-auto --status            查看定时任务状态和切换记录
#

APP_NAME="ictyun"
CONFIG="/opt/$APP_NAME/config.yaml"
LOG_FILE="/opt/$APP_NAME/mh-auto.log"
CRON_TAG="# mh-auto"

S=""; [ "$(id -u)" -ne 0 ] && S="sudo"
export PYTHONIOENCODING=utf-8

API_PORT=$(grep -oP 'external-controller.*:\K[0-9]+' "$CONFIG" 2>/dev/null || echo "9097")
API="http://127.0.0.1:$API_PORT"

# 默认值
COUNTRY='美国|🇺🇸'
GROUP="GLOBAL"
ACTION="run"

# ── 解析参数 ──
while [ $# -gt 0 ]; do
    case "$1" in
        --country)  COUNTRY="$2"; shift 2 ;;
        --group)    GROUP="$2"; shift 2 ;;
        --interval) ACTION="install"; INTERVAL="$2"; shift 2 ;;
        --stop)     ACTION="stop"; shift ;;
        --status)   ACTION="status"; shift ;;
        --help|-h)
            echo "mh-auto - \u81ea\u52a8\u9009\u62e9\u6700\u4f4e\u5ef6\u8fdf\u8282\u70b9"
            echo ""
            echo "\u7528\u6cd5:"
            echo "  mh-auto                     \u7acb\u5373\u6d4b\u901f\u5e76\u5207\u6362"
            echo "  mh-auto --country \u65e5\u672c       \u6307\u5b9a\u56fd\u5bb6\u5173\u952e\u8bcd"
            echo "  mh-auto --group ChatGPT     \u6307\u5b9a\u4ee3\u7406\u7ec4\uff08\u9ed8\u8ba4 GLOBAL\uff09"
            echo "  mh-auto --interval 5        \u5b89\u88c5 cron \u5b9a\u65f6\u4efb\u52a1\uff08\u6bcf N \u5206\u949f\uff09"
            echo "  mh-auto --stop              \u79fb\u9664\u5b9a\u65f6\u4efb\u52a1"
            echo "  mh-auto --status            \u67e5\u770b\u72b6\u6001\u548c\u5207\u6362\u8bb0\u5f55"
            exit 0
            ;;
        *) echo "unknown: $1"; exit 1 ;;
    esac
done

# ── 安装 cron ──
install_cron() {
    if [ -z "$INTERVAL" ] || [ "$INTERVAL" -lt 1 ] 2>/dev/null; then
        echo "interval must be >= 1 (minutes)"
        exit 1
    fi
    # 移除旧条目
    $S crontab -l 2>/dev/null | grep -v "$CRON_TAG" | $S crontab -
    # 添加新条目
    ($S crontab -l 2>/dev/null; echo "*/$INTERVAL * * * * /usr/local/bin/mh-auto >> $LOG_FILE 2>&1 $CRON_TAG") | $S crontab -
    echo "OK: cron installed, every $INTERVAL min"
    echo "log: $LOG_FILE"
}

# ── 移除 cron ──
stop_cron() {
    $S crontab -l 2>/dev/null | grep -v "$CRON_TAG" | $S crontab -
    echo "OK: cron removed"
}

# ── 查看状态 ──
show_status() {
    echo "=== cron ==="
    CRON_LINE=$($S crontab -l 2>/dev/null | grep "$CRON_TAG")
    if [ -n "$CRON_LINE" ]; then
        echo "  active: $CRON_LINE"
    else
        echo "  not installed"
    fi
    echo ""
    echo "=== last 10 switches ==="
    if [ -f "$LOG_FILE" ]; then
        grep "SWITCH" "$LOG_FILE" | tail -10
    else
        echo "  no log yet"
    fi
}

# ── 核心：测速并切换 ──
run_auto() {
    ENCODED_GROUP=$(python3 -c "import urllib.parse; print(urllib.parse.quote('$GROUP'))")

    # 触发组内批量测速
    curl -s "$API/group/$ENCODED_GROUP/delay?url=http://www.gstatic.com/generate_204&timeout=5000" >/dev/null 2>&1
    sleep 1

    # 获取节点列表，筛选国家，取最低延迟
    RESULT=$(curl -s "$API/proxies/$ENCODED_GROUP" | \
        COUNTRY_FILTER="$COUNTRY" API_PORT_VAL="$API_PORT" python3 -c '
import json, sys, urllib.parse, urllib.request, os, re

api_port = os.environ.get("API_PORT_VAL", "9097")
country = os.environ.get("COUNTRY_FILTER", "")
try:
    country = country.encode("utf-8", "surrogateescape").decode("utf-8")
except (UnicodeDecodeError, UnicodeEncodeError):
    pass
d = json.load(sys.stdin)
now = d.get("now", "")
nodes = d.get("all", [])

# filter by country keywords
keywords = [k.strip() for k in country.split("|") if k.strip()]
if keywords:
    nodes = [n for n in nodes if any(k in n for k in keywords)]

if not nodes:
    print("NO_MATCH")
    sys.exit(0)

# get delay for each node
results = []
for name in nodes:
    encoded = urllib.parse.quote(name)
    try:
        resp = urllib.request.urlopen(
            f"http://127.0.0.1:{api_port}/proxies/{encoded}", timeout=3)
        info = json.loads(resp.read())
        history = info.get("history", [])
        delay = history[-1].get("delay", 0) if history else 0
        if delay > 0:
            results.append((delay, name))
    except:
        pass

if not results:
    print("ALL_TIMEOUT")
    sys.exit(0)

results.sort()
best_delay, best_name = results[0]

# check current node delay
now_delay = 0
for d_val, n_val in results:
    if n_val == now:
        now_delay = d_val
        break

if best_name == now:
    print(f"KEEP|{best_delay}|{best_name}|{len(results)}")
elif now_delay > 0 and now_delay <= 300:
    print(f"KEEP|{now_delay}|{now}|{len(results)}")
else:
    print(f"SWITCH|{best_delay}|{best_name}|{len(results)}|{now}")
' 2>/dev/null)

    TS=$(date '+%Y-%m-%d %H:%M:%S')

    case "$RESULT" in
        NO_MATCH)
            echo "[$TS] NO_MATCH: no nodes match country filter"
            ;;
        ALL_TIMEOUT)
            echo "[$TS] ALL_TIMEOUT: all matched nodes timed out"
            ;;
        KEEP\|*)
            IFS='|' read -r _ delay name total <<< "$RESULT"
            echo "[$TS] KEEP: ${name} (${delay}ms) best of ${total} nodes"
            ;;
        SWITCH\|*)
            IFS='|' read -r _ delay name total old <<< "$RESULT"
            # do the switch
            curl -s -X PUT "$API/proxies/$ENCODED_GROUP" \
                -H "Content-Type: application/json" \
                -d "{\"name\":\"$name\"}" >/dev/null
            echo "[$TS] SWITCH: ${old} -> ${name} (${delay}ms) best of ${total} nodes"
            ;;
        *)
            echo "[$TS] ERROR: unexpected result"
            ;;
    esac

    # trim log to last 200 lines
    if [ -f "$LOG_FILE" ]; then
        LINES=$(wc -l < "$LOG_FILE")
        if [ "$LINES" -gt 200 ]; then
            tail -100 "$LOG_FILE" > "$LOG_FILE.tmp" && mv "$LOG_FILE.tmp" "$LOG_FILE"
        fi
    fi
}

# ── 分发 ──
case "$ACTION" in
    run)     run_auto ;;
    install) install_cron ;;
    stop)    stop_cron ;;
    status)  show_status ;;
esac
