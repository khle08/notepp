
sudo chmod 755 zlm.service
sudo cp zlm.service /etc/systemd/system/

sudo systemctl daemon-reload
sudo systemctl enable zlm
sudo systemctl start zlm
