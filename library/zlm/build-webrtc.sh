
# WebRTC 拉流

# 如果是 RTSP 或 RTMP 推流，然后使用 WebRTC 拉流的话，需要把 `directProxy` 改成 0。
# 代码里面注释明确写了："如果你是rtsp推拉流，但是 WebRTC 播放，也建议关闭直接代理模式，
# 因为直接代理时，rtp中可能没有 sps pps，会导致 webrtc 无法播放"

# ======================================================================

# 基础依赖
sudo apt install -y cmake gcc g++ libssl-dev libsdl-dev libavcodec-dev libavutil-dev libswscale-dev libresample-dev

# ======================================================================

# # WebRTC 必需的 libsrtp
# sudo apt install -y libsrtp2-dev

# ======================================================================

# sudo apt install -y autoconf automake libtool
# cd libsrtp
# ./configure --enable-openssl
# make -j$(nproc)
# sudo make install

# 更新动态库缓存
sudo ldconfig

# ======================================================================

rm -rf build
mkdir build
cd build

# 关键参数：ENABLE_WEBRTC=ON
cmake .. \
    -DENABLE_WEBRTC=ON \
    -DENABLE_OPENSSL=ON \
    -DENABLE_RTPPROXY=ON \
    -DENABLE_API=ON

make -j2
sudo make install


# [rtc]
# # 监听端口
# port=8000
# # 外网IP（重要！客户端要能访问到）
# externIP=你的服务器外网IP
# # 如果在内网使用，填内网IP
# # externIP=192.168.1.120

# # UDP端口范围（用于媒体传输）
# rtp_port_range=50000-60000
