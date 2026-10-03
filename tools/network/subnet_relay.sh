#!/bin/bash
# subnet_relay.sh —— 让一台"两只脚分别踩在两个网段"的 Linux 服务器当中继, 打通两个网段。
#
# 典型场景(2026-10 办公室):
#   光猫 192.168.1.1 ─┬─ 交换机 ── 摄像头 192.168.1.168 等        (1 网段, IN 侧)
#                    └─ Wi-Fi 路由器(NAT) ── Mac/服务器 192.168.110.x (110 网段, OUT 侧)
#   110 → 1 天然能通(路由器 NAT 出去); 1 → 110 不通(光猫不认识 110, 路由器也不放 WAN 侧进来的连接)。
#   3090 有线口在 1 网段、Wi-Fi 在 110 网段 → 用它中转 1 → 110 的流量。
#
# 原理(不用写代码, 全是内核自带能力):
#   1) ip_forward=1                  允许内核转发
#   2) FORWARD 放行 IN→OUT + 回程      Docker 会把 FORWARD 默认策略设成 DROP, 所以规则放进 DOCKER-USER
#   3) MASQUERADE(SNAT)               转进 OUT 网段的包, 源地址改成本机的 OUT 侧地址,
#                                     OUT 网段的设备就把回包发回本机, 不会走它自己的默认网关发丢
#   4) 端口转发(DNAT, 可选)            "访问 本机IN侧IP:端口 → 转到 OUT 网段某台机器:端口",
#                                     适合摄像头这类没法加静态路由的设备(把报警地址填成本机 IN 侧 IP 即可)
#   5) 替身地址(1:1 映射, 可选)        给 OUT 网段的某台设备在 IN 网段认领一个空闲地址(本机网卡辅助 IP /32),
#                                     IN 侧访问替身地址 = 访问那台 OUT 设备的全部端口/协议(含 ping)。
#                                     IN 侧设备什么都不用改(替身和它同网段, 不经网关) —— 光猫加不了路由时就靠它。
#                                     默认"末位相同": 192.168.110.N ↔ 192.168.1.N, 加之前用 arping 查冲突。
#   IN 侧设备要访问整个 OUT 网段(不只是转发端口)时, 还得让它们知道"去 OUT 网段找本机":
#     光猫/上级路由加静态路由  <OUT网段> via <本机IN侧IP>   (全网生效)
#     或单台电脑: ip route add <OUT网段> via <本机IN侧IP>
#
# 用法(需 root, 非 root 自动 sudo):
#   ./subnet_relay.sh up      --in enp2s0f0 --out wlxbcec434317f5     打通(网段从网卡自动识别)
#   ./subnet_relay.sh forward add 3546 192.168.110.204:3546 [tcp|udp] 端口转发
#   ./subnet_relay.sh forward del 3546 [tcp|udp]
#   ./subnet_relay.sh forward list
#   ./subnet_relay.sh map add 192.168.110.204 [192.168.1.204]           替身地址(不给 IN 地址则末位相同)
#   ./subnet_relay.sh map del 192.168.110.204
#   ./subnet_relay.sh map list
#   ./subnet_relay.sh scan                                            列出 IN 网段已被占用的地址
#   ./subnet_relay.sh status                                         看规则/网卡/提示
#   ./subnet_relay.sh down                                           撤销本脚本加的全部规则(不碰 Docker 等其他规则)
#   ./subnet_relay.sh enable-boot | disable-boot                    开机自动恢复(systemd, 在 docker 之后)
#   ./subnet_relay.sh apply                                          按配置文件重新应用(开机服务调用的就是它)
#
# 配置持久化在 /etc/subnet-relay.conf; 所有规则都带 comment "subnet-relay", 可重复执行、可精确撤销。
# 局限: 中继机必须开机; 中转带宽取决于中继机网卡(USB 无线网卡只适合 ssh/网页/报警回调, 扛不住多路视频)。

set -euo pipefail

TAG="subnet-relay"
CONF="/etc/subnet-relay.conf"
UNIT="/etc/systemd/system/subnet-relay.service"
SYSCTL_FILE="/etc/sysctl.d/99-subnet-relay.conf"
SELF="$(readlink -f "$0")"

S=""; [ "$(id -u)" -ne 0 ] && S="sudo"
ipt() { $S iptables "$@"; }

die() { echo "错误: $*" >&2; exit 1; }
info() { echo "[$TAG] $*"; }

# ---------- 配置读写 ----------
IN_IF=""; OUT_IF=""; FORWARDS=(); MAPS=()   # FORWARDS: "proto port dest_ip:dest_port"; MAPS: "out_ip in_ip"
ALIAS_LABEL_SUFFIX=":sr"   # 替身辅助 IP 的网卡标签后缀, down 时据此精确删除

load_conf() {
    [ -f "$CONF" ] || return 0
    while IFS= read -r line; do
        case "$line" in
            IN_IF=*)  IN_IF="${line#IN_IF=}" ;;
            OUT_IF=*) OUT_IF="${line#OUT_IF=}" ;;
            FORWARD=*) FORWARDS+=("${line#FORWARD=}") ;;
            MAP=*)     MAPS+=("${line#MAP=}") ;;
        esac
    done < "$CONF"
}

save_conf() {
    {
        echo "# subnet_relay.sh 生成, 手工改完执行: $SELF apply"
        echo "IN_IF=$IN_IF"
        echo "OUT_IF=$OUT_IF"
        for f in "${FORWARDS[@]+"${FORWARDS[@]}"}"; do echo "FORWARD=$f"; done
        for m in "${MAPS[@]+"${MAPS[@]}"}"; do echo "MAP=$m"; done
    } | $S tee "$CONF" >/dev/null
}

# 网卡 → 网段(如 192.168.1.0/24) / 本机地址
if_net()  { { ip -4 -o addr show dev "$1" 2>/dev/null | grep -v -- "$ALIAS_LABEL_SUFFIX" || true; } | awk '{print $4}' | head -1 | python3 -c "import ipaddress,sys; s=sys.stdin.read().strip(); print(ipaddress.ip_interface(s).network if s else '')"; }
if_addr() { { ip -4 -o addr show dev "$1" 2>/dev/null | grep -v -- "$ALIAS_LABEL_SUFFIX" || true; } | awk '{print $4}' | head -1 | cut -d/ -f1; }

in_net_of() { python3 -c "import ipaddress,sys; print(ipaddress.ip_address(sys.argv[1]) in ipaddress.ip_network(sys.argv[2]))" "$1" "$2"; }

# 替身辅助 IP: 只删/加带本脚本标签的, 不碰网卡原有地址
purge_aliases() {
    local dev line addr
    for dev in $(ip -o link show | awk -F': ' '{print $2}' | cut -d@ -f1); do
        { ip -4 -o addr show dev "$dev" 2>/dev/null | grep -- "$ALIAS_LABEL_SUFFIX" || true; } | awk '{print $4}' | while read -r addr; do
            $S ip addr del "$addr" dev "$dev" 2>/dev/null || true
        done
    done
}

need_ifs() {
    [ -n "$IN_IF" ] && [ -n "$OUT_IF" ] || die "未指定网卡。先执行: $0 up --in <IN侧网卡> --out <OUT侧网卡>"
    ip link show "$IN_IF"  >/dev/null 2>&1 || die "网卡 $IN_IF 不存在"
    ip link show "$OUT_IF" >/dev/null 2>&1 || die "网卡 $OUT_IF 不存在"
    IN_NET=$(if_net "$IN_IF");   OUT_NET=$(if_net "$OUT_IF")
    IN_ADDR=$(if_addr "$IN_IF"); OUT_ADDR=$(if_addr "$OUT_IF")
    [ -n "$IN_NET" ]  || die "网卡 $IN_IF 没有 IPv4 地址"
    [ -n "$OUT_NET" ] || die "网卡 $OUT_IF 没有 IPv4 地址"
}

# Docker 在时 FORWARD 默认 DROP, 且 Docker 会重排 FORWARD; 放进它预留给用户的 DOCKER-USER 才稳
fwd_chain() { ipt -nL DOCKER-USER >/dev/null 2>&1 && echo DOCKER-USER || echo FORWARD; }

# 幂等添加: 已存在(-C)就跳过
add_rule() {   # add_rule <table> <chain> <规则参数...>
    local t="$1" c="$2"; shift 2
    ipt -t "$t" -C "$c" "$@" -m comment --comment "$TAG" 2>/dev/null && return 0
    if [ "$c" = DOCKER-USER ] || [ "$c" = FORWARD ]; then
        ipt -t "$t" -I "$c" 1 "$@" -m comment --comment "$TAG"   # 放到最前, 抢在 DROP/RETURN 之前
    else
        ipt -t "$t" -A "$c" "$@" -m comment --comment "$TAG"
    fi
}

# 按标签删掉本脚本在某表所有链里加的规则
purge_table() {
    local t="$1" rule
    # 【|| true 不能省】set -o pipefail 下, grep 无匹配返回 1 会让整个脚本静默退出(实测踩过两次:
    #  purge_table 无旧规则、purge_aliases 无旧替身)。本文件凡是 grep 进管道的都要带 || true。
    { ipt -t "$t" -S 2>/dev/null | grep -- "--comment $TAG" || true; } | sed 's/^-A /-D /' | while read -r rule; do
        eval "$S iptables -t $t $rule" 2>/dev/null || true
    done
}

# ---------- 动作 ----------
apply_rules() {
    need_ifs
    local C; C=$(fwd_chain)

    $S sysctl -qw net.ipv4.ip_forward=1
    echo "net.ipv4.ip_forward = 1" | $S tee "$SYSCTL_FILE" >/dev/null

    purge_table filter; purge_table nat; purge_aliases   # 先清旧的(网卡/网段可能变了), 再按当前配置重建

    # IN → OUT 放行, 以及回程
    add_rule filter "$C" -i "$IN_IF" -o "$OUT_IF" -s "$IN_NET" -d "$OUT_NET" -j ACCEPT
    add_rule filter "$C" -i "$OUT_IF" -o "$IN_IF" -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT
    # 转进 OUT 网段的包伪装成本机 OUT 侧地址, 回包才会回到本机
    add_rule nat POSTROUTING -s "$IN_NET" -d "$OUT_NET" -o "$OUT_IF" -j MASQUERADE

    # 端口转发
    local f proto port dest
    for f in "${FORWARDS[@]+"${FORWARDS[@]}"}"; do
        read -r proto port dest <<< "$f"
        add_rule nat PREROUTING -i "$IN_IF" -p "$proto" --dport "$port" -j DNAT --to-destination "$dest"
        add_rule filter "$C" -i "$IN_IF" -o "$OUT_IF" -p "$proto" -d "${dest%:*}" --dport "${dest##*:}" -j ACCEPT
        # 目标若不在 OUT 网段的直连范围内也能回: 统一伪装成本机 OUT 侧地址
        add_rule nat POSTROUTING -o "$OUT_IF" -p "$proto" -d "${dest%:*}" --dport "${dest##*:}" -j MASQUERADE
    done
    # 替身地址: 本机 IN 网卡加 /32 辅助 IP 认领它(会回应 ARP), 进来的包 DNAT 到 OUT 设备;
    # 放行与伪装沿用上面 IN_NET→OUT_NET 的两条, 不用另加
    local m oip iip
    for m in "${MAPS[@]+"${MAPS[@]}"}"; do
        read -r oip iip <<< "$m"
        $S ip addr add "$iip/32" dev "$IN_IF" label "${IN_IF}${ALIAS_LABEL_SUFFIX}" 2>/dev/null || true
        add_rule nat PREROUTING -i "$IN_IF" -d "$iip" -j DNAT --to-destination "$oip"
        # 宣告一下, 让 IN 网段设备刷新 ARP 缓存(之前若有人缓存过这个地址的旧 MAC)
        command -v arping >/dev/null && $S arping -q -U -c 1 -I "$IN_IF" "$iip" >/dev/null 2>&1 || true
    done
    info "已应用: $IN_IF($IN_NET, 本机 $IN_ADDR) → $OUT_IF($OUT_NET, 本机 $OUT_ADDR), 转发链 $C, 端口转发 ${#FORWARDS[@]} 条, 替身 ${#MAPS[@]} 个"
}

cmd_up() {
    load_conf
    while [ $# -gt 0 ]; do
        case "$1" in
            --in)  IN_IF="$2"; shift 2 ;;
            --out) OUT_IF="$2"; shift 2 ;;
            *) die "未知参数 $1" ;;
        esac
    done
    need_ifs
    save_conf
    apply_rules
    hint_routes
}

cmd_forward() {
    load_conf
    local sub="${1:-list}"; shift || true
    case "$sub" in
        add)
            local port="${1:-}" dest="${2:-}" proto="${3:-tcp}"
            [[ "$port" =~ ^[0-9]+$ ]] || die "用法: forward add <本机端口> <目标IP:端口> [tcp|udp]"
            [[ "$dest" =~ ^[0-9.]+:[0-9]+$ ]] || die "目标格式应为 IP:端口, 如 192.168.110.204:3546"
            [[ "$proto" =~ ^(tcp|udp)$ ]] || die "协议只能是 tcp 或 udp"
            local kept=() f
            for f in "${FORWARDS[@]+"${FORWARDS[@]}"}"; do [[ "$f" == "$proto $port "* ]] || kept+=("$f"); done
            FORWARDS=("${kept[@]+"${kept[@]}"}" "$proto $port $dest")
            save_conf; apply_rules
            need_ifs; info "IN 侧访问 $IN_ADDR:$port ($proto) → $dest" ;;
        del)
            local port="${1:-}" proto="${2:-tcp}" kept=() f
            [[ "$port" =~ ^[0-9]+$ ]] || die "用法: forward del <本机端口> [tcp|udp]"
            for f in "${FORWARDS[@]+"${FORWARDS[@]}"}"; do [[ "$f" == "$proto $port "* ]] || kept+=("$f"); done
            FORWARDS=("${kept[@]+"${kept[@]}"}")
            save_conf; apply_rules ;;
        list)
            [ ${#FORWARDS[@]} -eq 0 ] && { echo "(没有端口转发)"; return; }
            local addr; addr=$( [ -n "$IN_IF" ] && if_addr "$IN_IF" || echo "<IN侧IP>")
            for f in "${FORWARDS[@]}"; do read -r p pt d <<< "$f"; echo "  $addr:$pt ($p) → $d"; done ;;
        *) die "forward 子命令: add | del | list" ;;
    esac
}

cmd_map() {
    load_conf
    local sub="${1:-list}"; shift || true
    case "$sub" in
        add)
            local oip="${1:-}" iip="${2:-}"
            [[ "$oip" =~ ^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+$ ]] || die "用法: map add <OUT侧设备IP> [IN侧替身IP]"
            need_ifs
            [ "$(in_net_of "$oip" "$OUT_NET")" = True ] || die "$oip 不在 OUT 网段 $OUT_NET"
            # 默认末位相同: 110.N → 1.N
            [ -n "$iip" ] || iip="$(python3 -c "import ipaddress,sys; n=ipaddress.ip_network(sys.argv[1]); print(n.network_address + int(sys.argv[2].split('.')[-1]))" "$IN_NET" "$oip")"
            [ "$(in_net_of "$iip" "$IN_NET")" = True ] || die "替身 $iip 不在 IN 网段 $IN_NET"
            [ "$iip" != "$IN_ADDR" ] || die "替身 $iip 是本机 IN 侧地址, 换一个"
            local m kept=()
            for m in "${MAPS[@]+"${MAPS[@]}"}"; do
                [[ "$m" == "$oip "* ]] && continue                      # 同一台设备重映射: 覆盖
                [[ "$m" == *" $iip" ]] && die "替身 $iip 已经映射给 ${m%% *} 了"
                kept+=("$m")
            done
            # 冲突检测: 替身地址在 IN 网段不能已有人用(本机已认领的除外)
            if ! ip -4 -o addr show dev "$IN_IF" | grep -q " $iip/"; then
                if command -v arping >/dev/null; then
                    $S arping -q -D -c 2 -w 3 -I "$IN_IF" "$iip" || die "$iip 在 IN 网段已有设备在用(arping 有应答), 换一个: map add $oip <空闲IP>"
                else
                    ping -c1 -W1 -I "$IN_IF" "$iip" >/dev/null 2>&1 && die "$iip 在 IN 网段已有设备在用, 换一个"
                fi
            fi
            MAPS=("${kept[@]+"${kept[@]}"}" "$oip $iip")
            save_conf; apply_rules
            info "IN 侧访问 $iip  ⇄  $oip (全部端口/协议)" ;;
        del)
            local oip="${1:-}" kept=() m
            [ -n "$oip" ] || die "用法: map del <OUT侧设备IP>"
            for m in "${MAPS[@]+"${MAPS[@]}"}"; do [[ "$m" == "$oip "* ]] || kept+=("$m"); done
            MAPS=("${kept[@]+"${kept[@]}"}")
            save_conf; apply_rules ;;
        list)
            [ ${#MAPS[@]} -eq 0 ] && { echo "(没有替身地址)"; return; }
            local oip iip
            for m in "${MAPS[@]}"; do read -r oip iip <<< "$m"; echo "  $iip  →  $oip"; done ;;
        *) die "map 子命令: add | del | list" ;;
    esac
}

# 列出 IN 网段已占用的地址(ping 扫一遍触发 ARP; 挡 ping 的设备也会回 ARP, 所以照样能看到)
cmd_scan() {
    load_conf; need_ifs
    local base; base="${IN_NET%.*}"
    info "扫描 $IN_NET (经 $IN_IF) ..."
    for i in $(seq 1 254); do ping -c1 -W1 -I "$IN_IF" "$base.$i" >/dev/null 2>&1 & done; wait
    echo "已占用: $IN_ADDR(本机) $({ ip neigh show dev "$IN_IF" | grep lladdr | grep -v FAILED || true; } | awk '{print $1}' | { grep -v : || true; } | sort -t. -k4 -n | tr '\n' ' ')"
    [ ${#MAPS[@]} -gt 0 ] && echo "本机替身: $(for m in "${MAPS[@]}"; do echo -n "${m##* } "; done)"
    return 0
}

cmd_down() {
    purge_table filter; purge_table nat; purge_aliases
    info "已撤销本脚本加的全部 iptables 规则(配置文件 $CONF 保留, 可用 apply 恢复)"
    info "ip_forward 未关闭(Docker 等也依赖它); 确需关闭: sudo sysctl -w net.ipv4.ip_forward=0 && sudo rm -f $SYSCTL_FILE"
}

cmd_status() {
    load_conf
    echo "== 配置 $CONF"; [ -f "$CONF" ] && grep -v '^#' "$CONF" || echo "(无)"
    echo "== ip_forward = $(cat /proc/sys/net/ipv4/ip_forward)"
    if [ -n "$IN_IF" ] && [ -n "$OUT_IF" ]; then
        echo "== 网卡: $IN_IF $(if_addr "$IN_IF")($(if_net "$IN_IF"))  →  $OUT_IF $(if_addr "$OUT_IF")($(if_net "$OUT_IF"))"
    fi
    echo "== 本脚本的规则"
    { ipt -S; ipt -t nat -S; } 2>/dev/null | grep -- "--comment $TAG" || echo "(当前未生效)"
    echo "== 开机自启: $(systemctl is-enabled subnet-relay 2>/dev/null || echo 未安装)"
    echo "== 端口转发"; cmd_forward list
    echo "== 替身地址"; cmd_map list
}

hint_routes() {
    need_ifs
    cat <<EOF

下一步(二选一, 让 IN 侧设备知道去 $OUT_NET 要找本机):
  · 光猫/上级路由加静态路由:  目的 $OUT_NET  下一跳 $IN_ADDR   (全网生效, 摄像头不用改)
  · 单台 Linux/Mac:  sudo ip route add $OUT_NET via $IN_ADDR   /   sudo route -n add -net $OUT_NET $IN_ADDR
  · 摄像头这类加不了路由的: 用端口转发, 把它的目标地址填成 $IN_ADDR:<端口>
     $0 forward add <端口> <OUT侧目标IP:端口>
注意: 本机 IN 侧地址 $IN_ADDR 若是 DHCP 分配的, 请在路由器上绑定或改静态, 否则地址一变路由就失效。
EOF
}

cmd_enable_boot() {
    load_conf; need_ifs
    $S tee "$UNIT" >/dev/null <<EOF
[Unit]
Description=subnet-relay: 打通 $IN_IF($IN_NET) → $OUT_IF($OUT_NET)
After=network-online.target docker.service
Wants=network-online.target

[Service]
Type=oneshot
RemainAfterExit=yes
# 网卡(尤其 USB 无线)开机拿到地址可能晚, 等最多 60 秒
ExecStartPre=/bin/bash -c 'for i in \$(seq 1 30); do ip -4 addr show dev $IN_IF | grep -q inet && ip -4 addr show dev $OUT_IF | grep -q inet && exit 0; sleep 2; done; exit 0'
ExecStart=/bin/bash $SELF apply
ExecStop=/bin/bash $SELF down

[Install]
WantedBy=multi-user.target
EOF
    $S systemctl daemon-reload
    $S systemctl enable subnet-relay >/dev/null 2>&1
    info "已设置开机自动恢复($UNIT)。脚本路径固定为 $SELF, 别挪走它。"
}

cmd_disable_boot() {
    $S systemctl disable subnet-relay >/dev/null 2>&1 || true
    $S rm -f "$UNIT"; $S systemctl daemon-reload
    info "已取消开机自动恢复(当前规则不受影响, 需要撤销请执行 down)"
}

case "${1:-}" in
    up)           shift; cmd_up "$@" ;;
    apply)        load_conf; apply_rules ;;
    forward)      shift; cmd_forward "$@" ;;
    map)          shift; cmd_map "$@" ;;
    scan)         cmd_scan ;;
    down)         cmd_down ;;
    status)       cmd_status ;;
    enable-boot)  cmd_enable_boot ;;
    disable-boot) cmd_disable_boot ;;
    *) sed -n '2,41p' "$SELF" | sed 's/^# \{0,1\}//'; exit 1 ;;
esac
