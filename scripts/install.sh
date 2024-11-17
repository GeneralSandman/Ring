#!/bin/bash

# 1. Download release Linux/MacOS/Windows.
# 2. Install std lib.
# 3. Install ring executable file.

UNAME=`uname`

MACOS_RELEASE="/Ring.tar.gz"
LINUX_RELEASE="/Ring.tar.gz"
WINDOWS_RELEASE="/Ring.tar.gz"


if [[ "$UNAME" = "Linux" ]]; then
    echo "Linux"
elif [[ "$UNAME" = "Darwin" ]]; then
    echo "Darwin"
elif [[ "$UNAME" = "Windows" ]]; then
    echo "Windows"
else 
    echo "Unknow Operating System"
    exit 1
fi


VERSION=""

wget https://ring.wiki/package/ring-v1.0.0-linux-386.tar.gz

echo "\033[32m[+]Download Ring Package Success\033[0m"

tar -zxvf ring-v1.0.0-linux-386.tar.gz
echo "\033[32m[+]Decompression Ring Package Success\033[0m"

cd Ring


INSTALL_TOP="/usr/local
INSTALL_BIN= $(INSTALL_TOP)/bin
INSTALL_PACK_STD = $(INSTALL_TOP)/lib/ring/std

CMD_INSTALL= install -p
CMD_INSTALL_EXEC= install -p -m 0755
CMD_INSTALL_DATA= install -p -m 0644


ring version
echo "\033[32m[+]Check Ring Version Success\033[0m"


install -p -m 0755 ring /usr/local/bin