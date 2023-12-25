#!/bin/bash

# build-release.sh
# Copyright (C) 2021-2023 ring.wiki, ZhenhuLi
# 
# 1. build release ring
# 2. tar
# 3. upload


# For Terminal Color
Red='\033[0;31m'            # Red
Green='\033[0;32m'          # Green
Yellow='\033[0;33m'         # Yellow
Color_Clear='\033[0m'       # clour Reset
#===================

# For Terminal Text
msg() {
  printf '%b\n' "$1" >&2
}
success() {
  msg "${Green}[✔]${Color_off} ${1}${2}"
}
info() {
  msg "${Blue}[➭]${Color_off} ${1}${2}"
}
error() {
  msg "${Red}[✘]${Color_off} ${1}${2}"
  exit 1
}
warn () {
  msg "${Yellow}[⚠]${Color_off} ${1}${2}"
}

echo_with_color () {
  printf '%b\n' "$1$2$Color_off" >&2
}
#===================


set -e

UNAME=`uname`


TAG="main"
# TAG 可选值:
# main
# v0.2.13


TARGET_OS=""
# TARGET_OS 有效值
# linux
# darwin


WORKSPACE="./tmp-Ring"
TMP_DIR="./ring-linux64"

RING_BIN="./bin/"
RING_STD="./std/"
RING_TEST="./test/"


if [[ "$UNAME" = "Linux" ]]; then
    TARGET_OS="linux"
elif [[ "$UNAME" = "Darwin" ]]; then
    TARGET_OS="darwin"
elif [[ "$UNAME" = "Windows" ]]; then
    echo "Not Support Windows"
    exit 1
else 
    echo "Unknow Operating System"
    exit 1
fi

OUTPUT_TARGET_1="./ring-${TARGET_OS}.tar.gz"
OUTPUT_TARGET_2="./ring-${TAG}-${TARGET_OS}.tar.gz"





install_linux_build_tool() {
    printf "Install Linux Build Tool\n"
    
    apt-get update && \
        apt-get -y install git && \
        apt-get -y install make && \
        apt-get -y install flex && \
        apt-get -y install bison && \
        apt-get -y install g++
}

install_darwin_build_tool() {
    printf "Install Darwin Build Tool\n"
}

install_build_tool() {
    if [[ "$TARGET_OS" = "linux" ]]; then
        install_linux_build_tool
    elif [[ "$TARGET_OS" = "darwin" ]]; then
        install_darwin_build_tool
    fi
}

clone_source_code() {
    if [ -d $WORKSPACE ]; then
        printf "\033[31m"
        printf "Error: ${WORKSPACE} alread exist, please remove it first\n"
        printf "\033[0m"
        exit 1

    fi
    git clone https://github.com/GeneralSandman/Ring $WORKSPACE
    cd $WORKSPACE

    if [[ "$TAG" != "main" ]]; then
        git checkout $TAG
    fi
}


build() {
    make clean && make 

    mkdir $TMP_DIR
    cp -r $RING_BIN/ring         $TMP_DIR/bin
    cp -r $RING_STD              $TMP_DIR/std
    cp -r $RING_TEST             $TMP_DIR/test
    echo  $TAG             >     $TMP_DIR/version.txt

    tar -zcf $OUTPUT_TARGET_1 $TMP_DIR
    cp $OUTPUT_TARGET_1 $OUTPUT_TARGET_2

    mv  $TMP_DIR tmp

    printf "\033[32m"
    printf "Build Relase Ring Done\n"
    printf "OS: %s\n" $TARGET_OS
    realpath $OUTPUT_TARGET_1
    realpath $OUTPUT_TARGET_2
    printf "\033[0m"
}


upload_release() {

}


main() {
    install_build_tool
    clone_source_code
    build
    upload_release
}

main
