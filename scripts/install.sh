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



exit

# wget https://ring.wiki/Ring.tar.gz
curl -o Ring.tar.gz https://ring.wiki/Ring.tar.gz
echo "\033[32m[+]Download Ring Source Code Success\033[0m"

tar -zxf Ring.tar.gz
echo "\033[32m[+]Decompression Ring Source Code Success\033[0m"

cd Ring

make
echo "\033[32m[+]Build Success\033[0m"


make install
echo "\033[32m[+]Install Success\033[0m"


ring version
echo "\033[32m[+]Check Ring Version Success\033[0m"


