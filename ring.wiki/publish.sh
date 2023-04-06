#!/bin/bash


# 通过 docsify 渲染

# 通过 cos-bucket website 功能部署


cd ring.wiki
# coscmd config -a AKIDVv9JH381KRM5dyC60rWzHNGzVpxso9Wk  -s Jn6D8sQnxvhHeqpcDcswozznPs9OWYN0 -b ring-1252697766 -r ap-beijing
coscmd upload -r ./ / 

#--ignore "./.git/*,./leetcode/leetcode-crawler/*"%

echo "open https://ring-1252697766.cos-website.ap-beijing.myqcloud.com\n"
echo "open http://ring.wiki\n"