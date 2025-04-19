[Unit]
Description=frps - Fast Reverse Proxy Server
After=network.target

[Service]
ExecStart=/root/remote/frp_0.61.1/frps -c /root/remote/frp_0.61.1/frps.toml
WorkingDirectory=/root/remote/frp_0.61.1
Restart=always
RestartSec=5
User=root
Group=root

[Install]
WantedBy=multi-user.target
