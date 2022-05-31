# ```Ring```基本语法编程示例


> [!NOTE|style:flat|label:基本语法编程示例]
> 
> 为了让大家对Ring有更直观的认识，GitHub上提供了相当多的编程示例，同时，这些编程用例也被用来进行自动化测试。
> 
> 编程示例
> 
> https://github.com/GeneralSandman/Ring/tree/main/test

### 运行编程示例：
```
cd Ring

make

./bin/ring --version



./bin/ring ./test/beat/basic-type/bool-000.ring

```


> [!NOTE|style:callout|label:自动化测试]
> 
> 自动化测试shell脚本，主要就是运行自动化测试case，通过标准输出到文件中，并与预期结果进行比较。如果相同，则测试通过。
> 
> https://github.com/GeneralSandman/Ring/blob/main/automated-testing.sh
> 



### 运行自动化测试：
```
cd Ring

make

./bin/ring --version



sh ./automated-testing.sh
或者
make testall
```


### 测试部分有：
- 基础数据类型
  - bool
  - int 
  - double
  - string
- 运算操作符
- 自定义函数/库函数
- 原生函数
- 控制流
  - if-elseif-else
  - for
  - do-for
  - break continue return
