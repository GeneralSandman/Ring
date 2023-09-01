#!/bin/bash

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


