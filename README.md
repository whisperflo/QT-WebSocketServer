------

~~~markdown
# Qt WebSocket Server

使用 Qt 实现的 WebSocket 服务器，支持多客户端连接、路径分发、定时消息推送等功能，适用于轻量级的服务端通信场景。

---

## 🧩 项目概述

该项目包含以下核心组件：

- **Main**：程序入口，初始化并启动调度模块。
- **TaskWebSchedule**：任务调度器，统一管理 WebSocket 任务。
- **TaskWebSocket**：WebSocket 任务处理类，定时向客户端发送消息。
- **WebSocketService**：WebSocket 服务，处理连接与断开，路径与客户端的映射关系。
- **WebsocketImpLayer**：路径业务解释器，根据请求路径分发不同业务逻辑。

---

## 🧭 架构流程

```plaintext
[ main.cpp ]
    │
    ▼
[ TaskWebSchedule ]
    │
    └── 创建与注册 TaskWebSocket
               │
               ├── 设置路径处理器
               ├── 管理客户端定时推送
               └── 与 WebSocketService 协作
                           │
                           ├── 路径连接映射管理
                           └── 向特定路径客户端推送数据
                                      │
                                      ▼
                       [ WebsocketImpLayer ]
                            └── 路径业务逻辑处理
~~~

------

## 🔧 编译与运行

### ✅ 环境要求

- Qt ≥ 5.15.16（含 QtWebSockets 和 QtNetwork）
- C++17 及以上
- Linux/macOS 环境（可移植到 Windows）

### 📦 编译步骤

```bash
git clone git@github.com:whisperflo/QT-WebSocketServer.git
cd QT-WebSocketServer
git checkout business
./make.sh clean     # 清理构建文件
./make.sh build     # 构建并运行
```

------

## 🗂️ 项目结构

```plaintext
.
├── Common
│   ├── DataStructure.h
│   └── ThreadPool.h.bk
├── main.cpp
├── Makefile
├── make.sh
├── Schedule
│   ├── websocketSchedule.cpp
│   └── websocketSchedule.h
├── Service
│   ├── webSocketService.cpp
│   └── webSocketService.h
├── Task
│   ├── websocketTask.cpp
│   └── websocketTask.h
├── WebSocketServer.pro
└── WorkLayer
    ├── websocketImpLayer.cpp
    └── websocketImpLayer.h
```

------

## 🚀 功能亮点

- **路径分发**：根据 WebSocket 路径解析并执行相应逻辑。
- **多客户端支持**：同一服务可接入多个客户端连接。
- **定时推送**：默认每 2 秒主动推送消息给客户端。
- **连接管理**：断开连接自动清理，稳定可靠。
- **结构清晰**：采用分层设计，扩展性强。

------

## 🧠 核心技术点

| 分类     | 技术要点                                        |
| -------- | ----------------------------------------------- |
| Qt 模块  | QtWebSockets、QtNetwork、QTimer、QUrl、信号与槽 |
| C++ 能力 | 智能指针、lambda、RAII、OOP、标准库容器         |
| 网络通信 | WebSocket 协议、路径映射、事件驱动              |
| 异步机制 | 信号与槽实现非阻塞通信、定时器驱动              |

------

## 🏗️ 使用的设计模式

| 模式                 | 应用场景说明                               |
| -------------------- | ------------------------------------------ |
| **观察者模式**       | 使用 Qt 信号与槽响应连接、消息、断开等事件 |
| **职责链模式**       | `WebsocketImpLayer` 按路径分发处理逻辑     |
| **策略模式**         | 每个路径对应不同策略，支持动态扩展业务     |
| **工厂模式（隐含）** | 调度模块负责初始化任务与服务组件           |
| **单一职责原则**     | 各类模块职责单一，职责清晰                 |
| **开闭原则**         | 添加路径或逻辑无需修改已有代码结构         |

------

## 🧼 构建脚本说明（make.sh）

```bash
#!/bin/bash

QMAKE=/usr/local/Qt-5.15.16/bin/qmake
MAKE=make
TARGET=WebSocketServer

function build() {
    echo "🔧 正在构建项目..."
    "$QMAKE" || { echo "❌ qmake 失败"; exit 1; }
    $MAKE || { echo "❌ 构建失败"; exit 1; }
    echo "✅ 构建成功"
}

if [ "$1" == "clean" ]; then
    echo "🧹 清理中..."
    rm -f Makefile *.o "$TARGET" moc_* *.a *.so *.exe
    echo "✅ 清理完成"
    exit 0
fi

if [ ! -f "$TARGET" ]; then
    echo "📁 可执行文件未找到，开始构建..."
    build
fi

echo "🚀 启动程序..."
./"$TARGET"
```

------

## 👤 作者

- **hjx**

