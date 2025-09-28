
# sudo apt update
# sudo apt install openssh-server

sudo chmod 755 frpc.service
sudo cp frpc.service /etc/systemd/system/

sudo systemctl daemon-reload
sudo systemctl enable frpc
sudo systemctl start frpc
