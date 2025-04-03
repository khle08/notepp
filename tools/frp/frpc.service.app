[Unit]
Description=frpc - Fast Reverse Proxy Client
After=network.target

[Service]
ExecStart=/home/kcl/frp_0.61.1/frpc -c /home/kcl/frp_0.61.1/frpc.toml
WorkingDirectory=/home/kcl/frp_0.61.1
Restart=always
RestartSec=5
User=root
Group=root

[Install]
WantedBy=multi-user.target
