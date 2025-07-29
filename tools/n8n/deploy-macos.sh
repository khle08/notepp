
# docker pull n8nio/n8n:latest

# sudo mkdir -p /Users/guojunlin/Docker/workspace/n8n
# sudo chown -R 1000:1000 /Users/guojunlin/Docker/workspace/n8n
# sudo chmod -R 755 /Users/guojunlin/Docker/workspace/n8n

docker volume create n8n
docker run -d --name n8n -p 5678:5678 \
           -v n8n:/home/node/.n8n \
           -e GENERIC_TIMEZONE=Asia/Shanghai \
           -e N8N_ENFORCE_SETTINGS_FILE_PERMISSIONS=true \
           -e N8N_SECURE_COOKIE=false \
           -e N8N_RUNNERS_ENABLED=true \
           n8nio/n8n:latest
