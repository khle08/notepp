
docker pull n8nio/n8n:latest

sudo mkdir -p /root/docker/n8n
sudo chown -R 1000:1000 /root/docker/n8n
sudo chmod -R 755 /root/docker/n8n

docker run -d --name n8n -p 5678:5678 \
           -v /root/docker/n8n:/home/node/.n8n \
           -e GENERIC_TIMEZONE=Asia/Shanghai \
           -e N8N_ENFORCE_SETTINGS_FILE_PERMISSIONS=true \
           -e N8N_SECURE_COOKIE=false \
           -e N8N_RUNNERS_ENABLED=true \
           n8nio/n8n:latest
