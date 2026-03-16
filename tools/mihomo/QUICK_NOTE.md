# 代理快速操作手册

SSH 登录服务器后，使用 `mh`（命令行）或 `mhd`（交互面板）管理代理。

---

## 1. 查看当前状态

```bash
mhd status          # 一目了然：服务状态、模式、代理组、出口 IP
# 或
mh status           # 仅看 systemd 服务状态
```

## 2. 启动 / 停止 / 重启

```bash
mh start            # 启动
mh stop             # 停止
mh restart          # 重启
```

## 3. 切换模式

| 模式 | 说明 | 命令 |
|------|------|------|
| Global | 所有流量走代理 | `mh mode global` |
| Rule | 按规则分流（国内直连，国外走代理） | `mh mode rule` |
| Direct | 全部直连（临时关闭代理） | `mh mode direct` |

```bash
mh mode             # 查看当前模式
mh mode global      # 切换到全局模式（推荐）
```

## 4. 查看节点

```bash
mh groups           # 查看所有代理组及当前选中节点
mh nodes            # 查看 GLOBAL 组的全部节点（带延迟测速）
mh nodes 🔥ChatGPT  # 查看指定组的节点
```

## 5. 切换节点

```bash
# 方式一：命令行直接切换
mh select GLOBAL '节点名称'

# 方式二：交互式切换（推荐，支持关键词搜索）
mhd
# → 选择 2) 切换节点
# → 选择代理组
# → 输入序号或关键词（如"美国"）筛选
```

## 6. 测速选节点

```bash
# 方式一：命令行
mh speedtest             # 全部节点测速
mh speedtest 美国        # 只测含"美国"的节点

# 方式二：交互式
mhd
# → 选择 3) 测速选节点
# → 输入关键词过滤 → 选最快的节点自动切换
```

## 7. 测试连通性

```bash
mh test             # 测试 Google / Anthropic / OpenAI 是否可达
mh ip               # 查看当前出口 IP 和地区
```

## 8. 更新订阅

```bash
mh update-sub 'https://你的订阅链接'    # 下载新配置并自动热重载
mh reload                               # 仅热重载当前配置（不重新下载）
```

## 9. 连接管理

```bash
mh conns            # 查看活跃连接数和流量统计
mh flush            # 关闭所有活跃连接（切换节点后建议执行）
```

## 10. 自动切换最快节点

```bash
# 立即执行：测速美国节点，切换到最快的
mh-auto

# 指定国家
mh-auto --country 日本

# 指定代理组
mh-auto --group ChatGPT

# 设为定时任务（每 5 分钟自动切换）
mh-auto --interval 5

# 查看状态和切换记录
mh-auto --status

# 关闭定时任务
mh-auto --stop
```

## 11. 查看日志

```bash
mh log              # 实时日志（Ctrl+C 退出）
```

---

## 常用操作速查

```
┌─────────────────────────────────────────────────┐
│  日常使用                                         │
│                                                   │
│  看状态    mhd status                             │
│  全局代理  mh mode global                         │
│  切节点    mhd → 2 → 选组 → 输关键词              │
│  测速切换  mhd → 3 → 输关键词 → 选最快             │
│  自动切换  mh-auto --interval 5                   │
│  看出口IP  mh ip                                  │
│  测连通    mh test                                │
│                                                   │
│  维护操作                                         │
│                                                   │
│  更新订阅  mh update-sub '链接'                    │
│  重启服务  mh restart                             │
│  看日志    mh log                                 │
│  清连接    mh flush                               │
└─────────────────────────────────────────────────┘
```
