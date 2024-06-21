# Ring/test 测试用例说明



## 在根目录 执行 make testall 

脚本文件 ./test/000-auto-test-script/automated-testing.sh

通过运行 `./bin/ring run xxx.ring` 命令进行测试, 得到的结果 与 `xxx.ring.result` 进行比对



## 在根目录 执行 make testdump

脚本文件 ./test/000-auto-test-script/automated-testing-dump.sh

通过运行 `./bin/ring dump xxx.ring` 命令进行测试, 得到的结果 与 `xxx.ring.dump` 进行比对

与 ./test/automated-testing.sh 相比, 没有必要全部比对.