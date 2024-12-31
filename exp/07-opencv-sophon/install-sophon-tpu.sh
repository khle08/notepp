
# ref: https://doc.sophgo.com/sdk-docs/v24.04.01/docs_latest_release/docs/tpu-mlir/quick_start/html/02_env.html

# Install docker
sudo apt install docker.io
sudo systemctl start docker
sudo systemctl enable docker
sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker

# Download Image file
wget https://sophon-file.sophon.cn/...sophgo-tpuc_dev-v3.2_...tar.gz
docker load -i sophgo-tpuc_dev-v3.2_...tar.gz

# docker: Error response from daemon: Conflict. The container name “xxx“ is already in use b
# docker ps -a              # To get the container ID
# docker rm 5024e25b11e8    # Remove the container by ID

# Load Image file (the name "adas" should be unique)
docker run --privileged --name adas -v $PWD:/workspace -it sophgo/tpuc_dev:v3.2

# In docker
pip install tpu_mlir
pip install tpu_mlir[onnx,torch]

