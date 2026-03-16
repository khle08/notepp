# 代理服务部署与操作手册

本手册记录在无 GUI 的 Linux 服务器上部署和操作代理服务的完整步骤。
所有 Clash GUI 客户端的功能（切换模式、选择节点、测速等）均可通过终端命令实现。

> **重要：伪装命名**
>
> 为避免在国内服务器上因敏感词导致问题，所有安装路径、服务名、二进制文件名
> 统一使用 `ictyun` 代替真实内核名称。实际使用的内核为 [mihomo](https://github.com/MetaCubeX/mihomo)（Clash Meta），
> 但在服务器上你看到的只有 `ictyun` 和 `mh`。

**实测环境：** Ubuntu 22.04 LTS (x86_64)
**内核版本：** v1.19.8

---

## 目录

**第一部分：部署安装**

1. [概述](#1-概述)
2. [一键部署（推荐）](#2-一键部署推荐)
3. [手动安装](#3-手动安装)
4. [配置订阅](#4-配置订阅)
5. [Geodata 文件](#5-geodata-文件)
6. [systemd 服务管理](#6-systemd-服务管理)
7. [验证代理](#7-验证代理)

**第二部分：日常操作（Clash GUI 等价操作）**

8. [交互式控制面板 mhd（推荐）](#8-交互式控制面板-mhd推荐)
9. [代理开关（启动 / 停止 / 重启）](#9-代理开关启动--停止--重启)
10. [切换代理模式（Global / Rule / Direct）](#10-切换代理模式global--rule--direct)
11. [查看代理组和节点列表](#11-查看代理组和节点列表)
12. [切换节点（选择 Checkpoint）](#12-切换节点选择-checkpoint)
13. [测试节点延迟（测速）](#13-测试节点延迟测速)
14. [查看当前出口 IP](#14-查看当前出口-ip)
15. [查看和管理活跃连接](#15-查看和管理活跃连接)
16. [查看实时日志](#16-查看实时日志)
17. [查看分流规则](#17-查看分流规则)
18. [热重载配置](#18-热重载配置)
19. [更新订阅](#19-更新订阅)

**第三部分：进阶**

20. [在 Sub2API 中使用](#20-在-sub2api-中使用)
21. [升级内核和 Geodata](#21-升级内核和-geodata)
22. [故障排查](#22-故障排查)
23. [一键自毁（彻底清除）](#23-一键自毁彻底清除)
24. [快速命令速查表](#24-快速命令速查表)

---

# 第一部分：部署安装

## 1. 概述

本方案使用 mihomo（Clash Meta）内核，但为避免国内服务器敏感词问题，所有文件和服务使用 **`ictyun`** 作为伪装名称。

**特点：**
- 兼容 Clash 订阅格式，机场订阅可直接使用
- 支持 Hysteria2、VLESS、Trojan、Shadowsocks、VMess 等多种协议
- 支持规则分流（国内直连、海外走代理）
- 提供 HTTP + SOCKS5 混合代理端口
- RESTful API 支持通过终端完成所有 GUI 操作

### 命名映射

| 真实名称 | 服务器上的名称 | 说明 |
|---------|-------------|------|
| mihomo (二进制) | `/opt/ictyun/ictyun` | 主程序 |
| mihomo.service | `ictyun.service` | systemd 服务 |
| /opt/mihomo/ | `/opt/ictyun/` | 安装目录 |
| mihomo 日志 | `journalctl -u ictyun` | 日志查看 |

### 核心概念

| 概念 | 说明 | 类比 Clash GUI |
|------|------|----------------|
| **mixed-port** | HTTP + SOCKS5 混合代理端口 | GUI 中的「端口」设置 |
| **mode** | 代理模式：global / rule / direct | GUI 顶部的模式切换按钮 |
| **Selector** 组 | 手动选择节点的代理组 | GUI 中的节点列表（手动选） |
| **URLTest** 组 | 自动测速选最快节点的代理组 | GUI 中的「自动选择」 |
| **Fallback** 组 | 故障转移，依次尝试的代理组 | GUI 中的「故障转移」 |
| **GLOBAL** 组 | Global 模式下使用的代理组 | GUI 中 Global 模式的节点选择 |
| **external-controller** | RESTful API 端口 | GUI 本身就是通过此 API 工作 |

---

## 2. 一键部署（推荐）

使用 `deploy.sh` 脚本在本地执行，自动完成全部流程：

```bash
# 交互式（逐步输入服务器信息和订阅链接）
./deploy.sh

# 非交互式（CI/批量部署）
./deploy.sh --ip 1.2.3.4 --user root --pass mypass --sub "https://..."
```

脚本自动完成：
1. 从 GitHub 下载内核和 Geodata 到本地
2. 通过 SCP 传输到服务器（二进制重命名为 `ictyun`）
3. 配置订阅、调整端口
4. 创建 `ictyun.service` systemd 服务
5. 安装 `mh` 快捷命令工具
6. 切换 Global 模式并自动选择美国节点
7. 验证 Google / Anthropic / OpenAI 连通性

> **前提：** 本地可访问 GitHub，密码登录需安装 `sshpass`。

---

## 3. 手动安装

### 3.1 在本地下载（推荐，因国内服务器无法访问 GitHub）

```bash
# 根据服务器架构选择：amd64 或 arm64
VERSION="v1.19.8"
curl -L -o kernel.gz \
  "https://github.com/MetaCubeX/mihomo/releases/download/${VERSION}/mihomo-linux-amd64-${VERSION}.gz"

gzip -d kernel.gz
mv kernel ictyun
chmod +x ictyun

# 传输到服务器
scp ictyun root@YOUR_SERVER_IP:/root/ictyun
```

### 3.2 在服务器安装

```bash
ssh root@YOUR_SERVER_IP

mkdir -p /opt/ictyun
mv /root/ictyun /opt/ictyun/ictyun
chmod +x /opt/ictyun/ictyun

# 验证
/opt/ictyun/ictyun -v
```

---

## 4. 配置订阅

### 4.1 下载订阅配置

```bash
# 在服务器上下载
curl -o /opt/ictyun/config.yaml \
  -H "User-Agent: clash.meta" \
  "你的订阅链接"

head -20 /opt/ictyun/config.yaml
```

**订阅链接选择优先级：**
1. Mihomo内核(路由器) - 最佳
2. 导入到 Clash - 兼容
3. 复制订阅(通用) - 通用

### 4.2 关键配置项

```yaml
mixed-port: 7897                          # 代理端口
allow-lan: false                          # 不暴露给局域网
mode: global                              # 全局模式（部署脚本自动设置）
log-level: info
external-controller: '127.0.0.1:9097'     # RESTful API 端口
```

### 4.3 禁用 TUN 模式

服务器不需要 TUN（全局透明代理），确保关闭：

```yaml
tun:
  enable: false
```

---

## 5. Geodata 文件

内核需要 GeoIP/GeoSite 数据做规则分流。国内服务器无法从 GitHub 下载，需提前准备。

| 文件 | 用途 | 大小 |
|------|------|------|
| `country.mmdb` | MaxMind GeoIP 数据库 | ~8.3MB |
| `geoip.dat` | IP 地理位置数据 | ~19MB |
| `geosite.dat` | 域名分类数据 | ~3.9MB |

```bash
# 本地下载
BASE_URL="https://github.com/MetaCubeX/meta-rules-dat/releases/download/latest"
curl -sL -o /tmp/country.mmdb "${BASE_URL}/country.mmdb"
curl -sL -o /tmp/geoip.dat "${BASE_URL}/geoip.dat"
curl -sL -o /tmp/geosite.dat "${BASE_URL}/geosite.dat"

# 传输到服务器
scp /tmp/country.mmdb /tmp/geoip.dat /tmp/geosite.dat root@YOUR_SERVER_IP:/opt/ictyun/
```

> **缺少这些文件时的错误：** `can't download MMDB: context deadline exceeded`

---

## 6. systemd 服务管理

### 6.1 创建服务文件

```bash
cat > /etc/systemd/system/ictyun.service << 'EOF'
[Unit]
Description=ICTyun Network Service
After=network.target

[Service]
Type=simple
ExecStart=/opt/ictyun/ictyun -d /opt/ictyun
Restart=on-failure
RestartSec=5
LimitNOFILE=65535

[Install]
WantedBy=multi-user.target
EOF
```

### 6.2 启动服务

```bash
systemctl daemon-reload
systemctl start ictyun
systemctl enable ictyun    # 开机自启
systemctl status ictyun    # 查看状态
```

---

## 7. 验证代理

```bash
# 检查端口
ss -tlnp | grep 7897

# 测试 Google
curl -x http://127.0.0.1:7897 https://www.google.com -o /dev/null -w "HTTP %{http_code}\n" -sS

# 测试 AI API
curl -x http://127.0.0.1:7897 https://api.anthropic.com -o /dev/null -w "HTTP %{http_code}\n" -sS

# 查看出口 IP
curl -x http://127.0.0.1:7897 https://ipinfo.io/json -sS
```

> **注意：** `ping` 使用 ICMP 协议，**无法走 HTTP 代理**。即使代理工作正常，`ping google.com` 仍然不通。必须用 `curl` 测试。

---

# 第二部分：日常操作（Clash GUI 等价操作）

> 以下操作提供两种方式：
> - **`mhd`** — 交互式控制面板，一条命令搞定所有操作（推荐管理员日常使用）
> - **`mh`** — 单条命令工具，适合脚本和快速操作
> - **curl** — 手动调用 RESTful API

**API 变量设置（手动 curl 时使用）：**

```bash
API="http://127.0.0.1:9097"
```

---

## 8. 交互式控制面板 mhd（推荐）

`mhd` 是一个交互式菜单工具，一条命令即可查看状态、切换模式、选择节点、测速，无需记忆各种命令。

### 安装

由 `deploy.sh` 自动安装。手动安装：

```bash
# 从本地上传（脚本源码文件名带 _ictyun 后缀，方便辨认用途）
scp mhd_ictyun.sh root@YOUR_SERVER_IP:/opt/ictyun/mhd
ssh root@YOUR_SERVER_IP 'chmod +x /opt/ictyun/mhd && ln -sf /opt/ictyun/mhd /usr/local/bin/mhd'
```

### 使用

```bash
mhd              # 进入交互式面板
mhd status       # 仅查看状态（不进入交互）
mhd s            # 同上，简写
```

### 交互式面板功能

运行 `mhd` 后会显示当前状态总览，然后提供操作菜单：

```
═══════════════════════════════════════════
  代理控制面板
═══════════════════════════════════════════
  服务状态:  ● 运行中
  当前模式:  Global (全局代理)

  代理组:
    手动   GLOBAL → 🇺🇸29美国旧金山-全网优化(hy2)  (51节点)
    手动   hy2 → 🇺🇸11美国西集群-全网优化(hy2)  (28节点)
    自动   ♻️自动选择 → 🇸🇬24新加坡-专线(TCP)  (43节点)
    ...

  出口 IP:   38.107.236.124 (San Francisco, US)
═══════════════════════════════════════════

  操作:
    1) 切换模式 (Global/Rule/Direct)
    2) 切换节点
    3) 测速选节点
    4) 测试连通性
    5) 刷新状态
    q) 退出
```

**操作说明：**

| 选项 | 功能 | 说明 |
|------|------|------|
| **1) 切换模式** | Global / Rule / Direct 三选一 | 选择后立即生效 |
| **2) 切换节点** | 先选代理组，再选节点 | 支持输入序号或关键词过滤（如输入"美国"只显示美国节点） |
| **3) 测速选节点** | 批量测速后选择 | 支持关键词过滤，结果按延迟排序，可直接选择切换 |
| **4) 测试连通性** | 测试 Google/Claude/OpenAI | 显示 HTTP 状态码 |
| **5) 刷新状态** | 重新显示状态面板 | 切换节点后用此查看最新状态 |

### 典型使用流程

**场景：切换到美国低延迟节点**

```
$ mhd
# 看到当前状态后，输入 3 (测速选节点)
# 输入关键词: 美国
# 等待测速完成，显示排序结果
# 输入最快节点的序号
# 完成切换
# 输入 5 刷新查看新状态
# 输入 q 退出
```

**场景：快速查看当前状态**

```
$ mhd s
# 显示状态面板后自动退出，不进入交互
```

---

## 9. 代理开关（启动 / 停止 / 重启）

对应 Clash GUI 中的「启动/关闭代理」开关。

```bash
mh start          # 或 systemctl start ictyun
mh stop           # 或 systemctl stop ictyun
mh restart        # 或 systemctl restart ictyun
mh status         # 或 systemctl status ictyun

# 开机自启
systemctl enable ictyun
systemctl disable ictyun
```

---

## 10. 切换代理模式（Global / Rule / Direct）

对应 Clash GUI 顶部的模式切换按钮。

| 模式 | 说明 | 适用场景 |
|------|------|---------|
| `global` | 所有流量走 GLOBAL 组选中的代理节点 | 需要全部走代理时 |
| `rule` | 按规则分流（国内直连，国外走代理） | 日常使用（默认） |
| `direct` | 所有流量直连 | 临时关闭代理 |

```bash
mh mode              # 查看当前模式
mh mode global       # 切换到 Global
mh mode rule         # 切换到 Rule
mh mode direct       # 切换到 Direct
```

手动 curl：

```bash
# 查看
curl -s $API/configs | python3 -c "import json,sys; print(json.load(sys.stdin).get('mode'))"

# 切换
curl -X PATCH $API/configs -H "Content-Type: application/json" -d '{"mode":"global"}'
```

> **Global 模式说明：** 切换到 Global 后，还需要在 GLOBAL 组中选择一个节点（见第 11 节）。

---

## 11. 查看代理组和节点列表

对应 Clash GUI 中的 **Proxies（代理）** 页面。

```bash
mh groups                  # 查看所有代理组及当前选择
mh nodes                   # 查看 GLOBAL 组的节点
mh nodes "组名"            # 查看指定组的节点
```

手动 curl：

```bash
# 所有代理组
curl -s $API/proxies | python3 -c "
import json, sys
data = json.load(sys.stdin).get('proxies', {})
for name in sorted(data):
    info = data[name]
    t = info.get('type', '')
    if t in ('Selector', 'URLTest', 'Fallback'):
        now = info.get('now', '?')
        count = len(info.get('all', []))
        print(f'  [{t:10}] {name} -> {now}  ({count}个节点)')
"

# 某个组的节点列表
GROUP="GLOBAL"
encoded=$(python3 -c "import urllib.parse; print(urllib.parse.quote('$GROUP'))")
curl -s "$API/proxies/$encoded" | python3 -c "
import json, sys
d = json.load(sys.stdin)
now = d.get('now', '')
for i, n in enumerate(d.get('all', []), 1):
    marker = ' <--' if n == now else ''
    print(f'  {i:3}. {n}{marker}')
"
```

---

## 12. 切换节点（选择 Checkpoint）

对应 Clash GUI 中点击代理组然后选择节点。

```bash
# 在 GLOBAL 组中切换节点
mh select GLOBAL "节点名称"

# 在其他组中切换
mh select "组名" "节点名称"
```

手动 curl：

```bash
GROUP="GLOBAL"
NODE="🇺🇸29美国旧金山-全网优化(hy2)"

encoded=$(python3 -c "import urllib.parse; print(urllib.parse.quote('$GROUP'))")
curl -s -X PUT "$API/proxies/$encoded" \
  -H "Content-Type: application/json" \
  -d "{\"name\":\"$NODE\"}"
```

> **注意：** 只有 `Selector` 类型的代理组可以手动切换。`URLTest` 和 `Fallback` 由系统自动选择。

---

## 13. 测试节点延迟（测速）

对应 Clash GUI 中的测速按钮。

```bash
mh delay "节点名"              # 测试单个节点
mh speedtest                   # 测试所有节点
mh speedtest 美国              # 只测美国节点
mh speedtest hy2               # 只测 Hysteria2 节点
```

手动 curl：

```bash
NODE="🇺🇸29美国旧金山-全网优化(hy2)"
encoded=$(python3 -c "import urllib.parse; print(urllib.parse.quote('$NODE'))")
curl -s "$API/proxies/$encoded/delay?timeout=5000&url=http://www.gstatic.com/generate_204"
```

---

## 14. 查看当前出口 IP

```bash
mh ip
```

手动 curl：

```bash
# 通过代理查看出口 IP
curl -x http://127.0.0.1:7897 -sS https://ipinfo.io/json

# 不通过代理查看本机真实 IP（对比用）
curl -sS https://ipinfo.io/json
```

---

## 15. 查看和管理活跃连接

对应 Clash GUI 中的 **Connections** 页面。

```bash
mh conns         # 查看活跃连接
mh flush         # 关闭所有连接
```

手动 curl：

```bash
# 查看连接
curl -s $API/connections | python3 -c "
import json, sys
d = json.load(sys.stdin)
conns = d.get('connections', [])
print(f'活跃连接数: {len(conns)}')
for c in conns[:20]:
    meta = c.get('metadata', {})
    host = meta.get('host', '') or meta.get('destinationIP', '')
    print(f'  {host}:{meta.get(\"destinationPort\",\"\")}  {c.get(\"rule\",\"\")}')
"

# 关闭所有连接
curl -X DELETE $API/connections
```

---

## 16. 查看实时日志

对应 Clash GUI 中的 **Logs** 页面。

```bash
mh log                            # 实时跟踪
journalctl -u ictyun -n 50        # 最近 50 行
journalctl -u ictyun --since today  # 今天的日志
```

修改日志级别：

```bash
# debug 可以看到每条连接的规则和节点
curl -X PATCH $API/configs -H "Content-Type: application/json" -d '{"log-level":"debug"}'

# 恢复 info
curl -X PATCH $API/configs -H "Content-Type: application/json" -d '{"log-level":"info"}'
```

---

## 17. 查看分流规则

对应 Clash GUI 中的 **Rules** 页面。

```bash
curl -s $API/rules | python3 -c "
import json, sys
rules = json.load(sys.stdin).get('rules', [])
print(f'共 {len(rules)} 条规则')
for r in rules[:30]:
    print(f'  {r.get(\"type\",\"\"):20} {r.get(\"payload\",\"\"):40} -> {r.get(\"proxy\",\"\")}')
"
```

---

## 18. 热重载配置

对应 Clash GUI 中的「重载配置」。不需要重启服务，代理不中断。

```bash
mh reload
```

手动 curl：

```bash
curl -X PUT "$API/configs?force=true" \
  -H "Content-Type: application/json" \
  -d '{"path":"/opt/ictyun/config.yaml"}'
```

---

## 19. 更新订阅

对应 Clash GUI 中的「更新订阅」。

```bash
# 使用 mh 工具
mh update-sub "你的订阅链接"

# 手动操作
curl -o /opt/ictyun/config.yaml -H "User-Agent: clash.meta" "你的订阅链接"
mh reload    # 或 mh restart
```

---

# 第三部分：进阶

## 20. 在 Sub2API 中使用

### 账号级代理（推荐）

管理后台 → 账号管理 → 编辑账号 → 代理地址：

```
http://127.0.0.1:7897
```

或 SOCKS5：

```
socks5://127.0.0.1:7897
```

### 辅助服务代理

Sub2API 的 `config.yaml` 中：

```yaml
update:
  proxy_url: "http://127.0.0.1:7897"
```

### 注意

- **不需要**设置系统环境变量（`http_proxy` / `https_proxy`）
- Sub2API 支持为每个账号配置独立代理
- 代理端口取决于配置中的 `mixed-port` 值

---

## 21. 升级内核和 Geodata

### 升级内核

```bash
# 在本地下载新版本
VERSION="v1.xx.x"
curl -L -o kernel.gz \
  "https://github.com/MetaCubeX/mihomo/releases/download/${VERSION}/mihomo-linux-amd64-${VERSION}.gz"
gzip -d kernel.gz && mv kernel ictyun && chmod +x ictyun

# 传输并替换
scp ictyun root@YOUR_SERVER_IP:/opt/ictyun/ictyun.new
ssh root@YOUR_SERVER_IP 'systemctl stop ictyun && mv /opt/ictyun/ictyun.new /opt/ictyun/ictyun && chmod +x /opt/ictyun/ictyun && systemctl start ictyun'
```

### 更新 Geodata

```bash
BASE_URL="https://github.com/MetaCubeX/meta-rules-dat/releases/download/latest"
curl -sL -o /tmp/country.mmdb "${BASE_URL}/country.mmdb"
curl -sL -o /tmp/geoip.dat "${BASE_URL}/geoip.dat"
curl -sL -o /tmp/geosite.dat "${BASE_URL}/geosite.dat"

scp /tmp/country.mmdb /tmp/geoip.dat /tmp/geosite.dat root@YOUR_SERVER_IP:/opt/ictyun/
ssh root@YOUR_SERVER_IP systemctl restart ictyun
```

---

## 22. 故障排查

### ping 不通 Google

**这是正常的。** `ping` 使用 ICMP 协议，无法走 HTTP/SOCKS5 代理。用 `curl` 测试：

```bash
curl -x http://127.0.0.1:7897 https://www.google.com
```

### 启动失败：can't download MMDB

```
can't download MMDB: context deadline exceeded
```

**原因：** 缺少 GeoIP 数据库，服务器无法从 GitHub 下载
**解决：** 参照第 5 节，本地下载后传输

### 代理不通

```bash
mh status                          # 1. 检查服务状态
ss -tlnp | grep 7897               # 2. 检查端口
journalctl -u ictyun -n 30         # 3. 查看日志
mh test                            # 4. 完整连通性测试
```

### 节点切换不生效

```bash
mh mode              # 确认当前模式
# Global 模式：需在 GLOBAL 组切换节点
# Rule 模式：流量由规则决定走哪个代理组
```

### 速度慢

```bash
mh speedtest          # 测试所有节点
mh speedtest 美国     # 只测美国节点，选最快的
```

---

## 23. 一键自毁（彻底清除）

当需要完全移除代理服务且不留任何痕迹时，使用自毁脚本。

**清除范围：**
- systemd 服务（ictyun / mihomo）
- 安装目录（/opt/ictyun / /opt/mihomo）
- 快捷命令（mh / mhd）
- 系统日志中的相关记录
- bash 历史中的相关命令记录
- /tmp 中的残留文件

### 方式一：在服务器上直接执行

```bash
# 先上传脚本
scp destroy_ictyun.sh root@YOUR_SERVER_IP:/tmp/

# SSH 到服务器执行
ssh root@YOUR_SERVER_IP
bash /tmp/destroy_ictyun.sh
```

### 方式二：本地远程执行（无需登录服务器）

```bash
sshpass -p "密码" ssh root@服务器IP 'bash -s' < destroy_ictyun.sh
```

### 方式三：通过 deploy.sh 同目录执行

```bash
# 非交互式远程自毁
sshpass -p "密码" ssh root@服务器IP 'bash -s' < destroy_ictyun.sh
```

执行后会要求输入 `YES` 确认，完成后自动验证是否清除干净。

> **注意：** 此操作不可逆。执行后需重新运行 `deploy.sh` 才能恢复。

---

## 24. 快速命令速查表

`mh` 工具由 `deploy.sh` 自动安装到 `/usr/local/bin/mh`，也可手动安装：

```bash
# 从本地上传 mh 脚本到服务器
scp mh_ictyun.sh root@YOUR_SERVER_IP:/opt/ictyun/mh
ssh root@YOUR_SERVER_IP 'chmod +x /opt/ictyun/mh && ln -sf /opt/ictyun/mh /usr/local/bin/mh'

# 上传 mhd 交互式面板
scp mhd_ictyun.sh root@YOUR_SERVER_IP:/opt/ictyun/mhd
ssh root@YOUR_SERVER_IP 'chmod +x /opt/ictyun/mhd && ln -sf /opt/ictyun/mhd /usr/local/bin/mhd'
```

### 命令一览

| 命令 | 说明 | 对应 Clash GUI |
|------|------|----------------|
| `mhd` | **交互式控制面板** | 整个 GUI |
| `mhd status` | 查看状态总览（不进入交互） | 主界面 |
| `mh start` | 启动代理 | 开关按钮 |
| `mh stop` | 停止代理 | 开关按钮 |
| `mh restart` | 重启代理 | - |
| `mh status` | 查看状态 | 状态指示灯 |
| `mh log` | 实时日志 | Logs 页面 |
| `mh mode` | 查看当前模式 | 模式显示 |
| `mh mode global` | 全局模式 | Global 按钮 |
| `mh mode rule` | 规则模式 | Rule 按钮 |
| `mh mode direct` | 直连模式 | Direct 按钮 |
| `mh groups` | 查看代理组 | Proxies 页面 |
| `mh nodes [组名]` | 查看节点 | 节点列表 |
| `mh select 组 节点` | 切换节点 | 点击节点 |
| `mh delay 节点` | 测延迟 | 测速按钮 |
| `mh speedtest [词]` | 批量测速 | 全部测速 |
| `mh ip` | 出口 IP | IP 显示 |
| `mh conns` | 活跃连接 | Connections 页面 |
| `mh flush` | 关闭所有连接 | 清除按钮 |
| `mh test` | 连通性测试 | - |
| `mh reload` | 热重载配置 | 重载按钮 |
| `mh update-sub <链接>` | 更新订阅 | 更新订阅按钮 |

---

## 附：文件结构

**本地 docs/mihomo/ 目录（部署工具包）：**

```
docs/mihomo/
├── README.md            # 本手册
├── deploy.sh            # 一键部署脚本
├── destroy_ictyun.sh    # 一键自毁脚本
├── mh_ictyun.sh         # CLI 工具源码
└── mhd_ictyun.sh        # 交互式面板源码
```

**服务器上的文件：**

```
/opt/ictyun/
├── ictyun          # 代理内核（实际为 mihomo 二进制，已重命名）
├── mh              # 单条命令快捷工具
├── mhd             # 交互式控制面板
├── config.yaml     # 主配置文件（来自订阅）
├── country.mmdb    # GeoIP MMDB 数据库
├── geoip.dat       # GeoIP 数据
├── geoip.metadb    # 内核自动生成的索引
└── geosite.dat     # GeoSite 域名分类数据

/etc/systemd/system/
└── ictyun.service  # systemd 服务文件

/usr/local/bin/
├── mh  -> /opt/ictyun/mh    # 单条命令工具
└── mhd -> /opt/ictyun/mhd   # 交互式控制面板
```

## 附：本次部署实际配置

| 项目 | 值 |
|------|-----|
| 服务器 OS | Ubuntu 22.04 LTS (x86_64) |
| 内核版本 | v1.19.8 |
| 安装路径 | `/opt/ictyun/` |
| 服务名 | `ictyun` |
| 代理端口 | `7897`（HTTP + SOCKS5 混合） |
| API 端口 | `9097`（仅 localhost） |
| 配置来源 | 机场订阅 |
| 代理协议 | Hysteria2 / Trojan |
| 当前模式 | Global |
