#!/bin/bash

#===============================================================================
# 定时重启电脑 - systemd timer 安装脚本
# 用法: sudo ./setup-reboot-timer.sh [执行时间]
# 示例: sudo ./setup-reboot-timer.sh "Mon *-*-* 03:00:00"
#===============================================================================

# 默认配置：每周一凌晨3点
DEFAULT_SCHEDULE="Mon *-*-* 03:00:00"
SCHEDULE="${1:-$DEFAULT_SCHEDULE}"

TIMER_NAME="scheduled-reboot"
TIMER_FILE="/etc/systemd/system/${TIMER_NAME}.timer"
SERVICE_FILE="/etc/systemd/system/${TIMER_NAME}.service"

# 检查 root 权限
if [ "$EUID" -ne 0 ]; then
    echo "请使用 sudo 运行"
    exit 1
fi

# 验证时间格式
echo "执行时间: ${SCHEDULE}"
echo ""
echo "未来 5 次重启时间:"
systemd-analyze calendar "${SCHEDULE}" --iterations=5
echo ""

read -p "确认设置定时重启? (y/n): " confirm
[ "$confirm" != "y" ] && exit 0

# 创建 Timer
cat > "${TIMER_FILE}" << EOF
[Unit]
Description=定时重启电脑

[Timer]
OnCalendar=${SCHEDULE}
Persistent=true

[Install]
WantedBy=timers.target
EOF

# 创建 Service
cat > "${SERVICE_FILE}" << EOF
[Unit]
Description=重启电脑

[Service]
Type=oneshot
ExecStart=/usr/sbin/reboot
EOF

# 启用
systemctl daemon-reload
systemctl enable --now ${TIMER_NAME}.timer

echo ""
echo "✓ 设置完成"
systemctl list-timers | grep ${TIMER_NAME}

