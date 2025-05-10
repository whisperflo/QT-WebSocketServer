# EchoServer - Qt WebSocket 服务器示例

这是一个使用 Qt `QWebSocketServer` 实现的简易 WebSocket 服务器示例，支持多客户端连接、消息接收与回显（echo）功能。

---

## 📁 项目结构

```
.
├── EchoServer.pro         # Qt 工程文件
├── EchoServer.h           # EchoServer 类头文件
├── EchoServer.cpp         # EchoServer 类实现
├── main.cpp               # 主函数，启动服务器
├── make.sh                # 一键编译/运行/清理脚本
└── README.md              # 使用说明文档
```

---

## 🚀 快速开始

### 依赖环境

- 安装 Qt（推荐 Qt 5.9+ 或 Qt 6+）
- 系统中已配置 `qmake`（可通过 `which qmake` 检查）

---

### 构建项目

```bash
./make.sh
```

> 🔧 构建输出位于 `./build/` 目录，可执行文件为 `build/EchoServer`

---

### 运行服务器

```bash
./make.sh run
```

> 服务器启动后会监听端口 **9002**

---

### 清理构建产物

```bash
./make.sh clean
```

> 包括清理 `build/` 目录 和 源码目录中的 `Makefile` 等临时文件

---

## 🌐 测试方式

你可以使用浏览器开发者工具或 WebSocket 客户端测试：

```javascript
const ws = new WebSocket("ws://localhost:9002");
ws.onopen = () => ws.send("Hello from browser!");
ws.onmessage = e => console.log("Echo from server:", e.data);
```

---

## 📌 特性说明

- 支持多个客户端同时连接
- 每个客户端单独绑定信号槽
- Echo 回显逻辑通过 `sender()` 自动识别来源套接字
- 使用 `QList<QWebSocket*> m_clients` 管理连接

---

## 📄 示例日志

```
WebSocket Server started on port 9002
New client connected: 127.0.0.1
Received message: Hello
```

---

## 📎 备注

- 默认监听地址为 `QHostAddress::Any`
- 默认端口写死为 `9002`（可在 `EchoServer.cpp` 中修改）
- 脚本中使用 `nproc` 自动启用多核编译（Linux/macOS）

---

## 🧪 TODO

- 支持广播所有客户端
- 支持 JSON 消息结构
- 增加日志文件输出
- 增加 TLS 支持（`QWebSocketServer::SecureMode`）

---

## 📬 联系

如果你对本示例有任何建议或问题，欢迎交流！
