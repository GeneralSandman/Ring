# ```Ring```基本语法编程示例


> [!NOTE|label:基本语法编程示例]
> 
> 为了让大家对Ring有更直观的认识，GitHub上提供了相当多的编程示例，同时，这些编程用例也被用来进行自动化测试。
> 
> 编程示例
> 
> https://github.com/GeneralSandman/Ring/tree/main/test

### 运行编程示例

```shell
cd Ring

make

./bin/ring version



./bin/ring run ./test/beat/basic-type/bool-000.ring

```


> [!NOTE|label:自动化测试]
> 
> 自动化测试shell脚本，主要就是运行自动化测试case，通过标准输出到文件中，并与预期结果进行比较。如果相同，则测试通过。
> 
> https://github.com/GeneralSandman/Ring/blob/main/automated-testing.sh
> 



### 运行自动化测试

```shell
cd Ring

make

./bin/ring version



sh ./automated-testing.sh
或者
make testall
```


### 测试Case分类


- 001-basic-type 基础数据类型
- 002-operator 运算操作符
- 003-native-function  原生函数
- 004-derive-function  自定义函数/库函数
- 005-control-flow  控制流
  - if-elseif-else
  - for
  - do-for
  - break continue return
- 006-variable  变量
- 数组
- 008-class 类
- 009-package  包
- 010-main-entry  main函数入口
- 011-global-variable  全局变量
- 012-local-variable  局部变量