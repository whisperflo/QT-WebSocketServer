#!/bin/bash

QMAKE=/usr/local/Qt-5.15.16/bin/qmake
MAKE=make
TARGET=WebSocketServer

# 构建函数
function build() {
    echo "🔧 正在构建项目..."
    "$QMAKE" || { echo "❌ qmake 失败"; exit 1; }
    $MAKE || { echo "❌ 构建失败"; exit 1; }
    echo "✅ 构建成功"
}

# 清理函数
if [ "$1" == "clean" ]; then
    echo "🧹 正在清理..."
    rm -f Makefile *.o "$TARGET"               # 删除 Makefile 和目标文件
    rm -f moc_*                                # 删除 moc 生成的文件
    rm -f *.a *.so *.exe                       # 删除可能生成的静态库、动态库和可执行文件
    echo "✅ 清理完成"
    exit 0
fi

# 检查可执行文件是否存在
if [ ! -f "$TARGET" ]; then
    echo "Executable not found, building first..."
    build
fi

# 启动程序
echo "🚀 启动程序..."
./"$TARGET"
