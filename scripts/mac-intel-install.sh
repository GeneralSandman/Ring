#!/bin/bash

# install ring binary to macos

# Usage:
# 通过第一个参数指定 安装的版本号

VERSION="$1"
PLAT="$2"

ORIGIN="https://ring.wiki"
REMOTE="$ORIGIN/macos-intel"
if [[ "$VERSION" != "" ]]; then
    REMOTE="$ORIGIN/$VERSION/macos-intel"
fi

BINS=(ring)
LIBS=(os,io,debug,fmt,vm,math,strings,reflect)


INSTALL_TOP="/usr/local"
INSTALL_BIN="$INSTALL_TOP/bin"
INSTALL_PACK_STD="$INSTALL_TOP/lib/ring/std"

CMD_INSTALL="install -p"
CMD_INSTALL_EXEC="$CMD_INSTALL -m 0755"
CMD_INSTALL_DATA="$CMD_INSTALL -m 0644"

CMD_MKDIR="mkdir -p"
CMD_RM="rm -rf"



for bin in "${BINS[@]}"; do
  rm -f "$local/$bin"
done

for bin in "${BINS[@]}"; do
  echo "Downloading $remote/$bin to $local/$bin"
  curl -s -o "$local/$bin" "$remote/$bin" &
done


# install ring bins


# install ring libs



# check