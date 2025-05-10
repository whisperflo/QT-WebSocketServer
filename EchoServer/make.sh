#!/bin/bash

set -e

BUILD_DIR="build"
EXECUTABLE="EchoServer"

function build() {
    echo "������ 开始构建..."
    mkdir -p $BUILD_DIR
    cd $BUILD_DIR
    qmake ../EchoServer.pro
    make -j$(nproc)
    cd ..
    echo -e "\n✅ 构建完成，生成可执行文件：$BUILD_DIR/$EXECUTABLE"
}

function run() {
    if [[ ! -f $BUILD_DIR/$EXECUTABLE ]]; then
        echo "⚠️ 可执行文件不存在，正在构建..."
        build
    fi
    echo "������ 运行中..."
    ./$BUILD_DIR/$EXECUTABLE
}

function clean() {
    echo "������ 正在清理构建目录..."
    rm -rf $BUILD_DIR
    echo "✅ build/ 清理完成"

    echo "������ 正在清理源码目录中的构建产物..."
    rm -f Makefile Makefile.Debug Makefile.Release *.o *.obj *.moc moc_*.cpp *.pro.user *.pro.user.*
    echo "✅ 源码目录清理完成"
}

# 检查是否误操作在源码目录构建
if [[ -f Makefile ]]; then
    echo "⚠️ 注意：检测到源码目录中存在 Makefile，建议仅在 build/ 目录中构建！"
fi

case "$1" in
    clean)
        clean
        ;;
    run)
        run
        ;;
    *)
        build
        ;;
esac

