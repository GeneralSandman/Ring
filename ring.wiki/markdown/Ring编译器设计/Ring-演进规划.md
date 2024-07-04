# Ring 演进规划


> [!TIP|label:tip]
> 
> 世界上哪有不枯燥的事情呀。
> 
> 研究和学习一定要不甘寂寞，如果要是累了，就可以放天假呀。
>
> 静下心来，不要着急，人生是一个漫长的过程，造编译器也是一个漫长的过程，慢慢思考就好。
> 
> Ring还是非常有必要研究好的，虽然世界上有很多类似的语言，只要集中精力发展，Ring的未来还是会让现在的自己吃惊的！
> 


## 总规划


完善Ring的基本功能, 争取在2024-12-31之前发布第一个release版本.


### 数据类型

1. 基本数据类型: bool int double string
2. 派生数据类型: array class
3. array: 多维数组
4. class: field(各种数据类型的嵌套组合, 循环定义), method
5. 用法: 可见范围(全局变量、局部变量)、定义、初始化、赋值、copy、函数传递、gc、heap_size计算、类型转化、(是否要支持auto推断类型)
6. Any类型
7. 类型的强制转换 与 隐式转换

### 运算符

1. 运算符: + - * / % += -= *= /= %= ++ -- 
2. 运算符: == != > < >= <=
3. 运算符: and or not
4. 运算符: a?b:c
5. 用法: 运算符的优先级、操作数的数据类型


### 控制语句

1. 语句: if else for do-for break continue return 
2. 语句: switch-case


### function & method

1. 函数调用
2. 参数、局部变量、返回值、self关键字
3. 可变参数+any类型
4. 参数的深度copy, 浅copy


### 语义分析

1. 完善语义分析 报错机制


### GC

1. 实现了最简单的STW Mark&Sweep GC算法
2. 实现进阶版GC: 三色标记的 Incremental Mark and Sweep 算法

### 项目组织

1. package 源代码的组织形式 import/package
2. 第三方package的安装和下载
3. 项目编译过程中并发编译
4. 支持一个package中有多个文件

### 工具链

1. linux man手册
2. `ring man` 支持快速查看语法
3. `ring dump` 查看字节码详情
4. 实现一键安装ring release版本
5. 能够生成字节码, 加载字节码
6. 命令行终端调试器 RDB
7. 交互式编程 REPL
8. LSP
9. 开发Ring编译器工具: 命令行交互式调试虚拟机工具

### 标准库


1. 更加优化的方式实现 native-lib, ring方便调用c库
2. 实现相对完善的官方标准库 fmt sys math debug strings reflect
3. fmt: 完善内置 printf 函数, 支持可变参数, 参考format函数
4. reflect: 实现反射, 获取变量的类型


### 不成熟的想法

1. 支持Ring Eval, e.g.  ./bin/lua eval "fmt::println_string("hello world")";  默认导入所有的std package, 不能指定全局变量, 直接就是main函数中代码
2. Closure
3. 函数式编程
4. 中间代码优化, 死代码消除, 常量折叠
5. 搭建一个 Ring在线 Playground
   参考资料:https://studygolang.com/articles/8880
    启动一个docker去运行 https://github.com/xiam/go-playground
    通过 Jupyter配置后端编译器内核来实现 https://zhuanlan.zhihu.com/p/431298076
6. 实现 ring eval函数
7. 实现交互式编程, 第一种是类似于python lua, 第二种是能够输入一行代码, 能够实时的输出翻译之后的字节码
8. 实现一个类似于 gdb python-pdb 的交互式调试的工具

-----------------------------

## Ring编译器开发内容流程细分

将工作细化为以下几类工作：
- 调研: 深度理解某项功能
- 设计: 需求分析、规划，设计语法，设计功能，设计某项功能, 代码实现
- 测试: 完善测试用例
- 重构: 代码逻辑的重构
- 优化: 优化Ring本身的不足

- ⭕️ : 重点关注代办
- ✅ : 完成



-----------------------------



## 参考资料汇总



### Lua源码分析
1. Lua的LG结构lua_State和global_State  
    https://zhuanlan.zhihu.com/p/102415312
2. Lua设计与实现 基于lua源码对其设计与具体实现进行剖析
   https://www.zhihu.com/column/c_1097089416010567680
3. 《自己动手实现Lua：虚拟机、编译器和标准库》代码 
   https://github.com/GeneralSandman/luago-book
4. lua学习笔记
    https://github.com/GeneralSandman/GeneralSandman-lua-learn-node
5. 构建Lua解释器
   https://manistein.github.io/blog/tags/let-us-build-a-lua-interpreter/

#### 书籍
1. 《Lua设计与实现》https://github.com/lichuang/Lua-Source-Internal
2. 《自己动手实现Lua：虚拟机、编译器和标准库》



1. 实现自己的编程语言 
   https://github.com/codecrafters-io/build-your-own-x#build-your-own-programming-language

2. Mark-Sweep垃圾回收机制 
   https://journal.stuffwithstuff.com/2013/12/08/babys-first-garbage-collector/

3. Lua GC 算法介绍
   https://manistein.github.io/blog/post/program/let-us-build-a-lua-interpreter/%E6%9E%84%E5%BB%BAlua%E8%A7%A3%E9%87%8A%E5%99%A8part2/

4. https://maplant.com/ 
   比较喜欢他的网站 特别喜欢那种特别老式的网站布局，人只会聚焦与内容


### 其他相关工具链

1. Bison Official Document
https://www.gnu.org/software/bison/manual/html_node/index.html#SEC_Contents

2. Bison Error Handling
https://docs.oracle.com/cd/E19504-01/802-5880/6i9k05dh4/index.html



1. 通读 diksam_v0.4 
   - https://github.com/GeneralSandman/diksam_v0.4
   - 里边还是有很多值得借鉴的地方
2. 通读 Lua 5.x版本
   1. 好好掌握 Lua的语法用法
   2. 力求完全掌握设计逻辑、包括协程、table
   3. 重新读那本 《自己动手实现Lua：虚拟机、编译器和标准库》
3. 学习 Ocaml
4. 学习 V8

Golang Plan9 汇编
https://studygolang.com/articles/21931
https://xargin.com/plan9-assembly/

深入理解golang汇编
https://godmelon.com/2021/07/25/golang-plan9-sam/


Intel格式和AT&T格式汇编区别
https://www.cnblogs.com/hdk1993/p/4820353.html


-----------------------------


## Lua


### 关于研究Lua的方法论和路线图

1. 不能有急于求成的心态, 创建编译器是一个很大的工作量, 需要长时间的付出和规划
2. 需要集中精力研究 Lua的源代码 和 Ring
3. 研究的方向主要集中于
- gc
- 字节码格式




### 关于研究Lua的哪个版本

lua 所有的版本 https://www.lua.org/versions.html

#### 1. lua 4.0.1  https://github.com/GeneralSandman/lua-4.0.1
   
简单, stack-based virtual machine 
可能方便

时间有点久远, 2002 年发布的, 

gc算法比较老旧
没有 coroutine

#### 2. lua 5.4.6  https://github.com/GeneralSandman/lua-5.4.6

可能理解起来比较复杂, 

但是相关的设计都是比较现代的

TIP: 推荐 Lua 5.4.6 版本作为研究对象.

### 《自己动手实现Lua：虚拟机、编译器和标准库》

这个书籍有几个地方其实我不太认可, 就是在实现 virtual machine stack 的时候, 使用的golang 的 interface{} 去存储数据,
不太认可这样的办法, 可能借用Golang的特性, 简化的虚拟机的实现方式

基于 Lua 5.4.4


#### 1. 第二章 ———— 二进制chunk格式详解

了解Lua 5.4.4 版本的 bytecode的基本格式, 知道是如何解析的, 并且实现了解析 Lua Bytecode.
header: 校验码, 如何加载
body: proto 的基本格式


#### 2. 第三章 ———— 指令集

介绍Lua虚拟机指令集和指令编码格式, 对指令进行解码.

TODO: 这里还没通过代码实现


#### 3. 第四章 至 第六章

主要介绍如何要实现一个stack-based virtual machine, 可以解释执行大概一半的Lua虚拟机指令.

但是自己在 Ring 已经实现了 stack-based virtual machine, 其实这三章可以暂时略过.


#### 4. 第七章 至 第十二章

介绍 表, 函数调用, Closure&Upvalue, 元编程, 迭代器, 异常和错误处理

TODO: Closure&Upvalue




### Ring想要借鉴的一些语法


#### 1. lua 索引
```
索引
对 table 的索引使用方括号 []。Lua 也提供了 . 操作。

t[i]
t.i                 -- 当索引为字符串类型时的一种简化写法
gettable_event(t,i) -- 采用索引访问本质上是一个类似这样的函数调用


> site = {}
> site["key"] = "www.runoob.com"
> print(site["key"])
www.runoob.com
> print(site.key)
www.runoob.com
```


#### 2. 字符串的format

1. python 的 formate函数比较人性化, 需要自己改造一下


```
language = "Python"
school = "freeCodeCamp"
print(f"I'm learning {language} from {school}.")
```


```
txt = "For only {price:.2f} dollars!"
print(txt.format(price = 49))
```

2. java

```
int x = 10, y = 20;
String s = STR."\{x} + \{y} = \{x + y}";
```

-----------------------------

## 测试

### 测试集  ring run

```
2024-07-03


[TestInfo]:
TEST_LOOP_NUM     = 1
TEST_RING_BIN     = ./bin/ring
TEST_RING_OPTION  = -O1
TEST_RING_COMMAND = run
TEST_COMMAND      = ./bin/ring -O1 run
TEST_PATH         = ./test


[Result]:
Pass/All = 376/377
NotTest  = 5
Fail     = 1
Usetime  = 20S

[NotPassCase]source_code_file                                             err_nums                                                    
./test/062-std-package-reflect/reflect-001.ring              1            

```




### 测试集 ring dump ✅

```
2024-05-30

[Result]:
Pass/All = 23/23
NotTest  = 0
Fail     = 0
Usetime  = 1S
```


### 要完善的测试用例

1. 函数参数的传递    (Path: ./test/004-derive-function/pass-argument/*)
   1. 参数的类型是基础类型  bool/int/int64/double/string
   2. 参数的类型是类       class
   3. 参数的类型是数组     bool[]/int[]/int64[]/double[]/string[]
   4. 参数的类型是类数组   class[]
2. 函数返回          (Path: ./test/004-derive-function/return-value/*)
   1. 返回值的类型是基础类型 bool/int/int64/double/string
   2. 返回值的类型是类      class
   3. 返回值的类型是数组    bool[]/int[]/int64[]/double[]/string[]
   4. 返回值的类型是数组    class[]
3. 全局变量
   1. 变量的定义+初始化 (Path: ./test/011-global-variable/def-and-init-*)
4. 局部变量
   1. 变量的定义+初始化 (Path: ./test/012-local-variable/def-and-init-*)
   

5. function return class object ✅
6. Pass class object as parameter to function ✅
7. Pass string as parameters to function       ✅
8.  Return class object from function        ✅
9.  Return string from function          ✅
10. Array & ClassObject
11. Array & String  ✅
12. Test array bool(global/local/argument/return)  ✅ 
13. Test array int(global/local/argument/return)  ✅ 
14. Test array double (global/local/argument/return)  ✅ 
15. Test array string(global/local/argument/return)  ✅ 
16. Test array class object(global/local/argument/return)

17. 一个 package中 有多个 class定义, 超过255个

18. 多维数组
19. 多维数组中 是 class

-----------------------------


## 开发专项-语义报错

1. 变量名称重复
   1. block中定义的 局部变量重复(函数没有参数)
   2. block中定义的 局部变量和 函数参数中的变量 名称重复
   3. 函数参数中的变量 他们之间重复

2. 函数名重复
   1. 一个package中函数名称重复

3. function/method 返回值
   1. 返回值数量不对
   2. 返回值类型不对
   3. 调用函数 接受返回值的数量不对
   4. 调用函数 接受返回值的类型不对

4. function/method 参数
   1. 参数数量不对
   2. 参数类型不对 


5. class field/method
   1. field 重复
   2. method 重复
   3. field method 不能重复, 得是唯一id
   4. field 只能是 bool int double string 


6. import std package
   1. 没有找到标准包
   2. import重复

7. 变量
   1. 全局变量的数量
   2. 局部变量的数量
8. 函数定义
   1. 返回值的数量不能超过 255

-----------------------------


## 开发专项-类

1. field类型
   1. bool ✅ 
   2. int ✅ 
   3. double ✅ 
   4. string ✅ 
   5. class (class的嵌套定义与引用)


-----------------------------


## 开发专项-数组

1. 数组 new 支持动态，e.g.  `array = new int[a,b,c];`

bool  ✅ 
int  ✅ 
double  ✅ 
string  ✅ 
class-object  ✅ 

2. 多维数组的语法糖 var int[!8]; 表示八维数组 ✅ 
   1. 创建多维数组的时候，不允许 !8
   2. !8 这个位置只能是个int常量，不能是变量


3. jobs[0].Running = false;  ✅ 
   这里有一个隐喻，就是jobs[0] 取出来应该得是个指针，
   不能是深度copy
   不然继续访问 jobs[0].Running 还是老的Value。


-----------------------------


## 开发专项-关于编译速度

 348444 行代码的ring, 都放在一个main函数中, 编译+运行 总共耗时 2346.94s.  但是编译没有报错.


-----------------------------


## 开发专项-丰富标准库


-----------------------------


## 2024-07-01周

### A. 函数定义中，参数的名字和局部变量的名字不能一样，需要报错提示


### B. 隐式类型和显式类型转化

因为 存在 int/int64/double ，如何不及早的考虑这个问题，Ring还是不太易用。



### C. 对于 function-call method-call 没有做详细语义检查，尤其是参数匹配

### D. function/method 的参数/返回值 最大不能超过 8, 除了可变参数


### E. 这样 会 报错优化

./test/999-bug-list/class.ring    

```
var Job1 local_job1_value_0 = Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
```


这样不会报错：
```
var Job1 local_job1_value_0;
	
	local_job1_value_0 = Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
```



也就是说对于类，在定义变量并且初始化的过程中，会存在问题，需要在 fix_ast中看一看



### F. 测试所有类型的 定义并初始化

1. bool/int/int64/double/string  通过常量初始化，通过变量初始化
2. class 通过常量初始化，通过变量初始化
3. 数组 通过常量初始化，通过变量初始化



### G. 测试所有类型的 赋值

1. bool/int/int64/double/string  通过常量赋值，通过变量赋值
2. class 通过常量赋值，通过变量赋值
3. 数组 通过常量赋值，通过变量赋值



### H. 编译需要提示

```
var int a,b = 1;
```

这种情况下需要报错提示。

-----------------------------


## 2024-06-24周


### A. 一个 Package中如何支持多个 源码文件

测试历程：test/997-feature

需要改进一下编译架构/流程，并发编译，提高编译速度

需要确认几点：
1. bison 如何支持并发编译
2. 多个文件，语义分析的过程如何进行
3. ./bin/ring run <file1> <file2>
4. ./bin/ring run ./   找到当前文件下的所有 ring文件进行编译链接


这个优化当前看来还有有点困难，是不是为时尚早？？？



### B. 如何支持项目组织

一个项目中含有多个Package，Package可以嵌套。


### C. 实现类rust 的模式匹配 match


### D. 定一个比较大的计划，调研 golang rust swift moonbit php python lua 等语法规范


### E. 调研 Lua JIT


-----------------------------


## 2024-06-11周

### A. 中间代码优化-实现简单的常量折叠




### B. 中间代码优化-实现简单的死代码删除


### C. 为了比较好实现在编译过程中解析 int64常量，需要在数字常量的后边手动添加一个 L ✅ 

这样实现可以让编译器比较方便的认为他是一个 int64常量，但是后续这个肯定是要进行优化的。

如：
```
0L;
-1L;

var int64 int64_value;

int64_value = 288L; 
int64_value = 288; // 编译错误
```


### D. int64 数据类型的测试用例要覆盖的全一点


### F. 针对fix_ast中的 要优化的编译报错，进行统一处理

1. 数学运算 + - * / %
2. 逻辑运算 and or
3. 非运算 not
4. 负号 -
5. 三目条件运算： ? :
6. 比较运算 < > <= >= == !=
7. 字符串拼接运算 ..


1. left right 操作数 的类型要一致
2. 不同的运算符 支持不同的操作数类型


### G. dlv的调试命令参考一下 dlv gdb, 


### H. 当前 int/int64/double/string 才能进行 大小比较运算

如果 有一个class，class的两个对象，如何运用到 大小比较运算
这里初步想到了两个解决办法：
1. 类似于cpp，通过method重载运算符
2. 类似于python，使用 重写以下方法：__gt__ __lt__ __ge__ __le__ __eq__ __ne__


### M. int/int64/double 支持 ++ -- ✅ 

TODO: 这里对应了 六个字节码，后续需要进行简化。

### N. self increase/decrease 实现的存在问题 ✅ 

只能对  int 自增，需要扩展到 int64/double

做一个全面的测试
1. int/int64/double ✅ 
2. 全局变量/局部变量   ✅ 
3. 类中的元素         ✅ 
4. 数组中的元素       ✅ 


### K. 对 ring -O2 dump 进行自动化测试


-O2 会开启编译优化，精简字节码，所以需要有一个专门的测试用例脚本用来测试。

### Q. 关于 unitary 表达式的语义检查，操作数的类型

unitary 有 - not ++ --

他的操作数可以是：
1. 常量
2. 局部变量
3. 全局变量
4. 类中的成员
5. 数组中的元素
6. 函数调用返回值 （++ -- 不行，他们不是左值）
7. method调用返回值（++ -- 不行，他们不是左值）


但是这种情况是可以的, 所以又成了左值和右值的问题：
```
func main() {
	return_job().ID++         // 编译错误
	return_job_pointer().ID++ // 可以
}


func return_job() Job {
	job := Job{ID: 1, Name: "Job1"}
	return job
}

func return_job_pointer() *Job {
	job := Job{ID: 1, Name: "Job1"}
	return &job
}
```

-----------------------------


## 2024-06-03周

### B. break point 信息优化


### C. 如何判断 class 递归定义


### D. 一个package中含有多个ring源代码文件


### E. 当前只能在main package中定义全局变量, 

如何在非main package中定义全局变量, 并能够在别的包中使用其他包的全局变量.
涉及到一个问题: 
1. 全局变量如何排布. 
2. 全局变量的初始化顺序


### F. 当前只能在main package中定义 class


### G. string 支持 utf-8编码


### H. ring 关于 relational-comp 相关字节码的行为优化 ✅ 

```
case RVM_CODE_RELATIONAL_LE_INT:
    STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) <= STACK_GET_INT_OFFSET(rvm, -1));
    runtime_stack->top_index--;
    rvm->pc++;
    break;
```

这里的流程设计的稍微不太好, 
```
STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) <= STACK_GET_INT_OFFSET(rvm, -1));
```

应该是 
```
bool_value =  (STACK_GET_INT_OFFSET(rvm, -2) <= STACK_GET_INT_OFFSET(rvm, -1));
STACK_SET_BOOL_OFFSET(rvm, -2, bool_value);
```


### B. 有个重大bug

就是 int常量 给 int64 赋值的时候 会存在问题.


./test/002-int/int-000.ring: 这个编译会报错
2147483648 在编译器认为是个 int64, 直接赋值给 int32 编译器会报错

```
	var int int_value_1 = 0;
    int_value_1 = -2147483648;
```


2. bug
```
	// TODO: 2147483648 在编译器认为是个 int64, 直接赋值给 int32 编译器会报错
	// int_value = 2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == 2147483648);

	// TODO: 2147483648 在编译器认为是个 int64, 直接赋值给 int32 编译器会报错
	// int_value = -2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == -2147483648);

	// TODO: 2147483648 在编译器认为是个 int64, 0 认为是 int32 , 编译器报错
	// int_value = 0-2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == -2147483648);
```


3. 报错优化

应该报错， 因为 1不是左值
```
1++;
```


### C. test/061-std-package-fmt/fmt-007.ring 这个测试用例需要再完善一下

完善一下 fmt::printf fmt::println 对于 类和数组的支持，需要验证 多层class的嵌套定义，包含数组类型等等。


### D. std package vm heap_size()  返回值统一改成 int64


### E. 支持 命名 any类型的 局部变量/全局变量

任何值都可以赋值给它，以此来实现范型。


### F. 检测 binary-expression 两边的表达式要保持一致

基本完成  ✅ 


### G. 这里有个bug

这里应该报错
```
var int64 sum = 0;
```


### H. 语义检查

这个语句是不允许的
```
sum = sum++;
```

不能将 自增/自减 运用到复杂表达式中。

-----------------------------


## 2024-05-27周

### A. 添加一个新的基础数据类型 int64 ✅ 

int 的数据范围有限, 为了扩大数据范围, 引入int64, 如其名, 64位数据. 在c语言中使用 long long 表示

1. 原先所有的 int 操作不便
2. 在 语法分析 运行虚拟机的过程中 添加 int64
3. 要系统性的分析 int 和 int64 在使用过程中的过中 显式转换&隐式转换
4. 能够跑通当前所有的测试用例

### B. 系统的规划 int64所需要的测试用例

1. fmt package
2. math operator
3. logical operator
4. relational operator
5. self incr/desc operator
6. 三目表达式

1. int64 数组
2. int64 类
3. int64 转string
4. int 转 int64
5. int64 转 double







### A. 实现新一代垃圾回收算法

#### 1. 重新规划一下 vm-execute 过程中 动态分配类型的流程逻辑

1.  heap_size() 返回值正确性
    1.  派生数据类型 类型分配计算的是否正确
2.  

string[] 数组的占用的内存是 capaity(array)* 8 这个需要再考究一下

#### 2. 关于RVM_Value 占用的内存优化

RVM_Value 中的字段 RVM_Value_Type 其实是个int, 占用了4字节, 这其实是一个很大的内存浪费,

需要调研一下, golang 中 interface的实现逻辑, python的实现逻辑

Golang 中 interface是如何实现的 https://halfrost.com/go_interface/


关于lua中, 如何用一个 struct 存放所有的数据类型, 也是 struct+(type&union)

```
/*
** Union of all Lua values
*/
typedef union Value {
    struct GCObject* gc; /* collectable objects */
    void*            p;  /* light userdata */
    lua_CFunction    f;  /* light C functions */
    lua_Integer      i;  /* integer numbers */
    lua_Number       n;  /* float numbers */
    /* not used, but may avoid warnings for uninitialized value */
    lu_byte ub;
} Value;


/*
** Tagged Values. This is the basic representation of values in Lua:
** an actual value plus a tag with its type.
*/

#define TValuefields \
    Value   value_;  \
    lu_byte tt_

typedef struct TValue {
    TValuefields;
} TValue;
```


#### 3. ring int 类型其实是 long long , 这样数据表达的范围更大


1. 将 RVM_Value 中的 int 不做更改, 还是32位
3. 在 RVM_Value 中 新添加一个 基础数据类型, int64, 然后对应的相应的虚拟机字节码都要 添加

然后还有一个棘手的问题就是 各种数据类型之间的转换, 隐式类型转换/显式类型转换, 还有各种地方的兼容性处理

3. array/class 中也要 支持 int64, 问题的复杂度一下就上升了 


这里还有一个关键的问题, 就是关于 len() capacity() 中 返回值是什么类型:
1. int
2. uint
3. int64

在这里, 不如比对一下golang是如何处理的: 
1. 使用 int 而不是 uint 的好处是这样无心智负担的写出这样的代码, 而不用担心程序崩溃
   
```
    // 倒序遍历数组
    for i := lenUInt(nums) - 1; i >= 0; i-- {
        fmt.Printf("i:%d -> num:%d\n", i, nums[i])
    }
```

2. 为什么使用 int, 而不是 int64

```

Go 语言的设计者 Rob Pike 在 Go 的邮件列表中曾经解释过这个问题。

len() 函数返回 int 而不是 int64 的原因主要有两个：

历史原因：Go 语言的前身是 Plan 9 的编程语言，Plan 9 中的 len() 函数也返回 int。在设计 Go 语言时，作者们决定保持这个惯例，以便更好地与 Plan 9 相兼容。
实际需求：在大多数情况下，int 类型足以表示容器的长度。即使在 32 位系统上，int 也可以表示非常大的数组或 slice。只有在非常特殊的情况下，例如处理非常大的数组或 slice 时，才需要使用 int64。
此外，使用 int 还有一个好处，那就是可以与其他语言更好地交互。例如，在 C 语言中，数组的索引通常是 int 类型的，而不是 int64。因此，如果 Go 语言的 len() 函数返回 int64，那么在与 C 语言交互时可能会出现问题。

总之，Go 语言的 len() 函数返回 int 是出于历史原因、实际需求和与其他语言的兼容性考虑的结果。
```





#### jvm 中的基本数据类型和对应的相关的字节码

```
Java 中有以下八种基础数据类型：

byte：8 位有符号整数，取值范围为 -128 到 127。
short：16 位有符号整数，取值范围为 -32768 到 32767。
int：32 位有符号整数，取值范围为 -2147483648 到 2147483647。
long：64 位有符号整数，取值范围为 -9223372036854775808 到 9223372036854775807 
float：32 位浮点数，取值范围为 -3.4e38 到 3.4e38。
double：64 位浮点数，取值范围为 -1.8e308 到 1.8e308。
boolean：布尔值，取值为 true 或 false。
char：16 位无符号整数，表示 Unicode 字符，取值范围为 0 到 65535。
这些基础数据类型是 Java 语言的基本组成部分，其他数据类型都是基于这些类型派生出来的。
```


```
Java 中的基础数据类型对应的 JVM 字节码如下：

byte：
加载：bload、baload
存储：bastore
操作：iinc、iadd、isub、imul、idiv、irem 等（使用 int 操作码，因为 byte 会被隐式转换为 int）


short：
加载：sload、saload
存储：sastore
操作：iinc、iadd、isub、imul、idiv、irem 等（使用 int 操作码，因为 short 会被隐式转换为 int）


int：
加载：iload、iaload
存储：iastore
操作：iinc、iadd、isub、imul、idiv、irem 等


long：
加载：lload、laload
存储：lastore
操作：linc、ladd、lsub、lmul、ldiv、lrem 等


float：
加载：fload、faload
存储：fastore
操作：finc、fadd、fsub、fmul、fdiv、frem 等


double：
加载：dload、daload
存储：dastore
操作：dinc、dadd、dsub、dmul、ddiv、drem 等


boolean：
加载：无特殊字节码，使用 iload 或 aload 加载 boolean 值
存储：无特殊字节码，使用 iastore 或 astore 存储 boolean 值
操作：使用 int 操作码，例如 iconst_0、iconst_1 等


char：
加载：aload、caload
存储：astore、castore
操作：使用 int 操作码，例如 iinc、iadd、isub 等（因为 char 会被隐式转换为 int）
需要注意的是，JVM 字节码并不是一一对应的，例如 int 操作码可以用于 byte、short 和 char 等类型的操作。


```


-----------------------------


## 2024-05-13周

### A. ring.hpp 中 Function 和 MethodMember 两个 struct融合为一个  ✅ 

Function MethodMember 派生自 FunctionTuple;

```cpp
#define FUNCTION_TUPLE_HEADER                                                    \
    std::string         source_file;       /*ring source file*/                  \
    unsigned int        start_line_number; /*start line no in ring source file*/ \
    unsigned int        end_line_number;   /*end   line no in ring source file*/ \
    Package*            package;           /*function's package*/                \
    RingFileStat*       ring_file_stat;    /*ring source file stat*/             \
    char*               identifier;                                              \
    unsigned int        parameter_list_size;                                     \
    Parameter*          parameter_list;                                          \
    unsigned int        return_list_size;                                        \
    FunctionReturnList* return_list;                                             \
    Block*              block;                                                   \
    FunctionTuple*      next;


struct FunctionTuple {
    FUNCTION_TUPLE_HEADER;
};

struct Function {
    FUNCTION_TUPLE_HEADER;

    unsigned int func_index;
    FunctionType type;
};

struct MethodMember {
    FUNCTION_TUPLE_HEADER;

    unsigned int index_of_class; // UPDATED_BY_FIX_AST
};
```



## B. return 语句 语义检查的 ✅ 

这个函数检查不过去, 需要优化

```
function pass_to_string(var string string_value) -> (string) {
    fmt::printf("string_value={}\n", string_value);
    return "#" + string_value;
}
```


-----------------------------


## 2024-05-06周

### A. variadic parameter 复杂测试用例 ✅ 

test/020-array-bool/func-variadic-parm-001.ring

test/020-array-bool/func-variadic-parm-002.ring


### B. 三目条件表达式 优化表达式的类型 ✅ 


a ? b : c; 
b 和 c 的表达式类型必须一致, 然后这个三元表达式的最终类型 就是 b c 表达式的类型.

./bin/ring run ./test/002-operator/condition-oper-001.ring

### C. ring rdb breakpoint 操作优化

1. break set 的时候, 行号如果是个空行, 怎么办

- 确定是最后一行
- 向后查找 第一个非空行 设置断点


2. break list 信息优化, 需要有以下信息

- 文件名
- 函数名
- 包名
- 行号
- 数量


### D. 完成 ./test/automated-testing-dump.sh 用于 测试 ring dump 命令 ✅ 


### E. CentOS Ubuntu 环境 coredump ✅ 

经定位, 是 linux g++ 有点问题 

```
char *dir;

std::string tmp = std::string(dir);

```

std::string(dir); 实现方式有问题.

应该直接这样即可:

```
char *dir;

std::string tmp = dir;
```


### F. 函数中 return 语句的合法性检查, 检查和函数定义中的函数返回值是否一致 TODO:


1. return 的语句中, 也不能 func()返回多个返回值 与单个返回值并存.
2. return 语句中, 支持 func()返回多个返回值, `递归调用场景`

method 中还不能进行强制检查 return 语句

这里基本实现了, 但是代码结构得重构一下.



-----------------------------


## 2024-04-22周



### A. BUG:ring package_unit 记录文件内容, 最后一行记录不了,  ✅ 


### B. CentOS Ubuntu 环境coredump ✅ 

TODO: file_stat 对应的 so 没有安装


### C. 可变参数类型 应用到 @derive函数中, 也就是如何访问可变参数类型 ✅ 

1. 语义检查: 将变量的类型变成数组, 如果变量的类型已经是数组了, 那就加一个维度
2. vm execute: 需要把参数转化成数组, 然后压入栈中, 然后后续通过数组的形式去访问可变参数
   - 可以对可变参数列表进行 for-range len() capacity() 操作


实现方式: 额外生成一个opcode, new_array_int. (当 var any... any_values, 需要对应那种字节码)

new_array_literal_bool 这个操作码 应该是在函数内部, 还是在函数外部

1. 如果要是放在函数外部, 实现起来不太优雅, 还要区分 @native @derive function, 因为 @native funciton 的便利性, 可以直接进行访问
2. 如果要是放在函数内部实现, 可能会破坏函数的字节码展示, 让user感觉多了好几个字节码
3. 如何去访问这个 临时的数组, 这个数组变量的identifier就是 parameter 的identifier


这里还有一个抉择, 就是关于 可变参数列表 转化成 数组,
这个操作 是单独用一个专门的字节码表示, 还是通过 在 init_derive_function_local_variable 中 实现(这样实现的话, 没有单独的字节码, 会在内部将列表转化为数组, 然后压入栈中, 这样需要在RVM_Function中需要详细记录参数的类型, 是不是可变参数, 根据可变参数进行详细的操作.)


### D. ring dump 中, 格式化 可变参数类型不正确 ✅ 


### E 多维数组 + 可变参数类型, 类型的多维展开  TODO:





-----------------------------


## 2024-04-15周

### A. ring debugger 完善一下 help 提示信息  ✅ 

对标 https://ring.wiki 中doc


### B. ring debugger bt 展示的行数不太对,  ✅ 

当前行数正确, 
上一层栈的行数不正确


### C. 修正bug ✅ 

fmt::println() 参数为string的时候,行为不太正确, 需要通过 length来控制


### D. 语义分析, 函数调用, 参数数量不对

### E. 语义分析, 函数调用, 参数类型不对

需要区分 any 类型 和可变参数类型

例如 

```
@native
function println(var any... any_value);

@native
function printf(var string format, var any... any_value);
```



### F. 关于函数多返回值的使用方式 ✅ 

函数定义:

```
function func_return_2_value() (bool, int) {

}
```


#### a. 应用到多项赋值的情况下

这样是可允许的, 因为 func_return_2_value() 的返回值是作为一个 整体 (bool, int), 函数调用表达式后边还有别的表达式, 所以 能够展开为 bool, int:

```
a, b = func_return_2_value();
```


但是这样是不被允许的, 因为 func_return_2_value() 的返回值是作为一个 整体 (bool, int), 函数调用表达式后边还有别的表达式, 所以不能够展开

```
a, b, c = func_return_2_value(), "str";
```


当然常规情况下, 这样是可以允许的:

```
a, b, c = true, 1, "aa";
```



#### b. 函数多返回值的 作为 下一个函数传递


这样是可允许的, 也是因为 func_return_2_value() 返回值作为一个整体, 可以继续展开:
```
    function func_pass_2_value(var bool bool_value, var int int_value) {
    
    }

    func_pass_2_value(func_return_2_value());
```


这样是不可允许的, 因为 func_return_2_value() 后边还有别的表达式, 不能继续展开:
```
    function func_pass_3_value(var bool bool_value, var int int_value, var string string_value) {
    
    }

    func_pass_3_value(func_return_2_value(), "str");
```



TODO: 关于展开
在这里, 多次取到一个名字叫做展开, 就是指 函数调用表达式后边还有别的表达式, 不能继续展开. 如何只是一个单独的表达式, 他自己是可以自己展开的
如何使用一种通用的方法去描述这种 能够展开的情况

### G. 关于 ring 语义分析 中, 强制检查变量的类型

TODO: 关于类型的比较
1. 基础类型的比较只需要比 TypeSpecifier.kind 即可
2. 对于 数组 类型的比较 (比较数组的维度, 和数组元素的类型 )
3. 对于 类   类型的比较 (类应该有一个全局的标识符, 这个标识符用来 作为 class的 unique-id, 如 package+class-identifier )
4. 对于函数有多项返回值的情况, 还需要处理是否能够展开
5. 还要考虑 函数调用中 any类型 和 可变参数类型
6. 当前, 函数还不能作为变量进行传递, 所以暂时先不考虑 函数类型的比较, 函数如何区分 unique-id.





-----------------------------


## 2024-04-08周


### A. ring debugger 实现 step-over step-into step-out ✅ 


### 命令: step over (命令缩写 n) ✅ 

- 执行被调用的函数或方法，而不进入其中。
- 当需要快速了解函数或方法的调用结果时使用。

### 命令: step into (命令缩写 i) ✅ 

- 进入被调用的函数或方法中，逐行执行代码。
- 当需要深入了解函数或方法的内部实现时使用。

### 命令: step out (命令缩写 o) ✅ 

- 退出当前执行的函数或方法，返回到调用它的位置。
- 当需要跳出嵌套的函数调用并继续执行主函数时使用。



1. FIXME: Break set 还有个bug, 如果某行为注释或者空行, breakpoint 可能不会生效, 验证测试下
2. cont 命令 是不是 跟 step命令一块放在一起比较好


### B. ring debugger 如何显示源代码文件的内容, 方便调试 ✅ 

命令: ```code list```

1. 显示当前位置 所在的 文件  ✅ 
2. 显示当前位置 所在的 行数  ✅ 
3. 显示当前位置 所在的 函数  TODO:
4. 显示当前位置 所在的 内容  ✅ 
5. 显示当前位置 前七行 后七行 总共15行内容.  ✅ 

实现: RingFileStat 记录源代码的元信息方便后续访问加载 ✅ 


### C. break points 可以保存到本地文件中, 可以方便下次加载

类似于 gdb 的 save breakpoints <file-name>

文件的格式可以参考一下 gdb是如何生成的

```
<breakpoint-type> <breakpoint-address> <breakpoint-enabled> <breakpoint-function> <breakpoint-line>
```


- <breakpoint-type> 是断点的类型，例如 breakpoint 或 watchpoint。
- <breakpoint-address> 是断点的地址。
- <breakpoint-enabled> 是一个布尔值，指示断点是否已启用。
- <breakpoint-function> 是断点设置处的函数名称（如果已知）。
- <breakpoint-line> 是断点设置处的行号（如果已知）。

breakpoint 0x100000f40 y main 10
watchpoint 0x100001000 y my_function 20




### D. ring程序终止之后, 不退出 rdb, 可以重新 run 当前的程序


这里可能比较难设计, 需要把当前运行的进程kill掉, 重新捕获命令后输入, 然后重新拉起任务(语法分析, 生成Opcode, 执行)


### D. ring debugger 设置断点的时候可以通过函数, 函数名字可以自动补全

break list 可以展示函数名字

break set function_name:line


### E. ring 中多个命令支持通过 && 一次输入, 方便快捷

-----------------------------


## 2024-04-01周


### A. 函数中 return了之后, 没有对返回值进行接收, 

或者一个 语句 `"bool"`; 栈空间会不太正确.


### B. 测试链式调用 ✅ 

1. 主要是要修正 function method 的 return_list  ✅ 
2. 测试 function method field各种相互组合的场景 ✅ 


例如:  ./test/008-class/class-052.ring:208


```
    job_1.printInfo();
    job_1.Job2.printInfo();
    job_1.Job2.Job3.printInfo();
    job_1.Job2.Job3.Job4.printInfo();
```


```
    job_1.returnSelf().Job2.Job3.returnSelf().Job4.printInfo();
```


```
copyJob4(
        copyJob3(
            copyJob2(
                copyJob1(job_1).Job2
                ).Job3
            ).Job4
        ).printInfo();
```



### C. duplicate字节码修改一下名字 ✅ 

duplicate 修改成 shallow_copy 更好理解,
与 deep_copy相对应


### D. class-object literal 中, 最后一个元素后边有没有逗号都可以 ✅ 



### E. 命令行交互式调试虚拟机工具


#### a. Stack详情 和 字节码详情 信息的展示做一个简单的重构 ✅ 

1. Stack详情: 可以详细展示数据的类型和数值
2. 字节码详情: 可以显示当前位置的前后20行字节码, 同时显示当前的所在的函数名称


#### b. printf标准输出 和 交互式的命令行展示信息 冲突 ✅ 

1. DEBUG_RVM_INTERACTIVE情况下: printf标准输出会重定向到文件 /tmp/ring-debug-vm.stdout.log
2. 交互式的命令行展示信息(Stack详情、字节码详情) 通过 stderr 的形式输出.



#### c. 目前只能一步一步的运行, 需要支持进入函数和不进入函数 // TODO:

Enter 一步一步
step:
next:
until:



### F. 针对函数调用专门优化语义报错 提示

1. 赋值操作 left 和 right 数量类型的是否正确一致 ✅ 
2. 参数的数量不一致
3. 参数的类型不一致
4. 返回值的数量不一致
5. 返回值的类型不一致

#### a.多项赋值和函数调用应该做一个限制

函数:
```
func test_0() {
}

func test_1() (bool) {
	return false
}

func test_2() (bool, int) {
	return false, 0
}

func main() {

    // 这种情况不应该允许
    // test_2() 的返回值是一个整体
	a, b, c := test_1(), test_2()

    // 这种情况不应该允许
    // test_0() 没有返回值
    a, b, c := test_0(), test_1(), test_1(), test_1()

    // 这种情况下应该允许
    // 函数的返回值只有一个
    a, b, c := test_1(), test_1(), test_1()
    a, b, c := test_1(), test_1(), false
	a, b, c := false, test_1(), test_1()

}
```

也就是多返回值不能作为多项赋值的右值

### G. 如果只有单独的表达式(push stack value) 但是没有 pop, 会造成栈空间的增长

```
1;
2;
"asefad";
test(); // 有返回值但是没有接手

```

白白浪费了一个stack空间.



### H. AST 路径的缩减



### I. fix_binary_math_expression()  fix_binary_relational_expression() 要做精细化的划分

把逻辑分开, 每层逻辑可以保持干净

-----------------------------


## 2024-03-25周


### A. 记录源代码 BUG

package_unit->line_offset_map 记录不了文件的最后一行的内容

package_unit 中记录了源代码文件, rdb在获取源代码内容的时候, 不太容易实现,
在这里, 要进行解耦合, 将记录源代码内容的数据结构, 从 PackageUnit中剥离出来, 
这样也能在 rdb 中获取源代码实现.


### B. fmt::sprintf(var string format, var any... any_value) -> string



### C. BUG: 返回值


```
method printInfo() {
    return fmt::printf("Job({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
}
```

FIXME: 这样写是会崩溃的, 因为本来没返回值, 这里却返回了, 需要强制检查返回值.


### D. 多项赋值 的深度 copy, 通过 RVM_CODE_DEEP_COPY 解决这个问题 ✅ 

#### a. 在这种情况下, 实际上是 对 数组元素class-object的deep-copy

```
for(i = 0; i<5; i++) {
    // FIXME: 这样写是有bug, 
    global_job_array_0[i], global_job_array_0[9-i] = global_job_array_0[9-i], global_job_array_0[i];
}
```


#### b. 在这种情况下, 实际上是 对 数组元素class-object的shallow-copy

```
global_job_array_0[9-i].Int = 1;
```




### E. 添加一个新的字节码: RVM_CODE_DEEP_COPY  ✅ 

RVM_CODE_DEEP_COPY 是对栈上的数据做深度copy.
RVM_CODE_SHALLOW_COPY 是对栈上的数据做浅copy.


TODO: 以后需要这样规划:
默认字节码是对栈上的数据做shallow-copy
但是对于 deep-copy的场景(赋值、函数传递), 需要显式生成一个字节码: RVM_CODE_DEEP_COPY , 专门处理数据的deep-copy





### F. 完善测试用例 ✅ 

#### a.  ✅ 

数组元素为 class-obect
通过索引访问数组元素并直接调用method
`global_job_array_0[i].printInfo();`


#### b. ✅ 

数组元素为 class-obect
通过for-range访问数组元素并直接调用method
```
for(local_job_value in range global_job_array_0) {
    local_job_value.printInfo();
}
```



#### c. ✅ 

数组的元素为 class-obect
Usage: 将数组内的所有的对象顺序反转
Code:
```
global_job_array_0[i], global_job_array_0[9-i] = global_job_array_0[9-i], global_job_array_0[i];
for(i = 0; i<5; i++) {
    global_job_array_0[i], global_job_array_0[9-i] = global_job_array_0[9-i], global_job_array_0[i];
}
```


#### d. ✅ 


数组的元素为 class-obect, 数组为二维数组
直接通过索引交换元素, 只不过是一次交换一整列
```
global_job_array_0 = new Job[2,2];
global_job_array_0[0], global_job_array_0[1] = global_job_array_0[1], global_job_array_0[0];
```


#### e. ✅ 

class有4级嵌套
测试对象嵌套的初始化
测试嵌套访问method
```
    job_1.printInfo();
    job_1.Job2.printInfo();
    job_1.Job2.Job3.printInfo();
    job_1.Job2.Job3.Job4.printInfo();
```


-----------------------------



## 2024-03-18周


### A. 设计Ring命令行交互式编程


设计: 
1. `ring rdb <filename>` 使用交互式调试功能
2. 在交互式中, 使用 clipp 解析命令行参数, 以后 ring命令行也是用 clipp解析
3. 进入交互式debugger之后, 会在main函数的入口处停止, 等待输入和调试

rdb命令:

1. global: 打印全局变量
2. global <variable>: 打印全局变量 //TODO: 后续支持, 
3. local: 打印局部变量
4. local <variable>: 打印局部变量 //TODO: 后续支持, 
5. cont/c: 继续执行, 直到遇到一个break-points
6. bt: 打印堆栈
7. clear: 清屏
8. quit/q: 退出 ctrl-c
9. code list: 打印当前行代码, 当前位置前后12行代码 //TODO: 后续支持, 这个还挺难实现的
10. step/s: 单步执行, 会进入函数体 //TODO: 后续支持, 
11. next/n: 单步执行, 不会进入函数体 //TODO: 后续支持, 
12. until <line-number>: 则继续执行直至行号大于或等于 line-number
13. step opcode: 一次执行一个ring虚拟机字节码 //TODO: 后续支持,

断点命令相关:
1. break set   <line-number>  放置断点, 会获得一个breakpointID
2. break clear <line-number>  清除断点
3. break list                 列出断点
4. break clear               清除所有断点


最后显示: 
```
The program '/Users/bytedance/Desktop/Ring/bin/ring' has exited with code 0 (0x00000000).
```



```
treminal> ./bin/ring rdb ./test/test.ring
ring-v0.2.14-beta Copyright (C) 2021-2023 ring.wiki, ZhenhuLi
Start Ring Debugger...

Input file: ./test/test.ring

rdb> break 8
Breakpoint 1 at: file test.ring:8

rdb> break 9
Breakpoint 1 at: file test.ring:9

rdb> break 10
Breakpoint 1 at: file test.ring:10

rdb> info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00005555555551b1 in main() at test.ring:8
2       breakpoint     keep y   0x00005555555551dc in main() at test.ring:9
3       breakpoint     keep y   0x0000555555555207 in main() at test.ring:10


rdb> cont
Continuing.
Breakpoint 1, main () at test.cpp:8
8           std::cout << "1" << std::endl;


rdb> cont
Continuing.
1

Breakpoint 2, main () at test.cpp:9
9           std::cout << "2" << std::endl;

rdb> c
Continuing.
2

Breakpoint 3, main () at test.cpp:10
10          std::cout << "3" << std::endl;







rdb> bt
#0  test4 () at test.cpp:9
#1  0x00005555555551da in test3 () at test.cpp:13
#2  0x00005555555551ea in test2 () at test.cpp:17
#3  0x00005555555551fa in test1 () at test.cpp:22
#4  0x00005555555552e1 in main () at test.cpp:31
```



-----------------------------




## 2024-03-11周

### A. 调研交互式编程

1. 类似于 python lua的交互式编程, 通过每一行的输入, 并执行, 同时得出执行结果, 这个相对复杂
2. ringc的交互式编程, 没输入一行内容, 就实时翻译编译后的字节码, 这个相对简单一点


调研 lua的交互式编程的实现.

repl: real-eval-print loop  https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop


使用 linenoise读入一行, 编译, 执行, 然后输出结果


设计:
1. ring repl
2. 进入之后, 打印 ring的版本号, 提示开始交互式编程
3. 前缀为 > 
4. 能够根据输入的关键字自动提示
5. 能够记录历史
6. 能够存储到本地目录
7. 定义默认导入的package
6. 快捷键: ctrl+c 退出, enter 下一行, shift+enter 开启新的block, 并自动开始运行



### B. 调研交互式调试工具

调研一下 python-debugger 和 lua-debugger

1. lua

debug.debug()    进入交互式的debug
debug.getlocal() 获取局部变量
debug.setlocal() 设置局部变量

test1.lua
```

function foo()
    print("function foo\n")
    local a = 10
    local b = 20
    local c = a + b
    local d = "hello world"
    local e
    printLocalVariables()
    initLocalVariables()
    printLocalVariables()
end

function printLocalVariables()
    local level = 2
    local localVarIndex = 1
    local name, value

    print("printLocalVariables--------------------")
    while true do
        name, value = debug.getlocal(level, localVarIndex)
        if not name then break end
        print("identifier:", name, "value:", value)
        localVarIndex = localVarIndex + 1
    end
end

function initLocalVariables()
    local level = 2
    local localVarIndex = 1
    local name, value

    print("initLocalVariables--------------------")
    while true do
        name = debug.setlocal(level, localVarIndex,
                              "local variable " .. tostring(localVarIndex))
        if not name then break end
        localVarIndex = localVarIndex + 1
    end
end

-- 通过 debug.getlocal() 获取局部变量, debug.setlocal() 设置局部变量
foo()


```


2. python的 python -m pdb test.py, 调用一个交互式的debugger




-----------------------------

## 2024-03-04周 


### A. BUG: ring dump  ✅ 

如何变量是 class Job, dump的时候显示`Job`, 而不是显示`class`


### B. TEST: 类 通过函数传递, 通过函数返回

bool array
int array
double array
string array
class-object array  ✅ 


### C. TEST: 类数组 通过函数传递, 通过函数返回

bool array
int array
double array
string array
class-object array  ✅ 


### D. TEST: for-range 测试多维数组

bool array
int array
double array
string array
class-object array  ✅ 


### E. 局部变量初始化 ✅ 


### F. 多维数组的 push pop


### G. 重新设计并验证gc

1. gc 对于 String
    string 全局变量, 局部变量, 变量返回值, 变量函数的传递
    to_string() 操作
    string_literal
    
2. gc 对于 class-object
3. gc 对于 array 


heap_size 的算法
gc的正确性



### H. 重新 设计 fmt::printf函数 ✅ 


rust的格式化输出 https://course.rs/basic/formatted-output.html

看这个测试用例:
test/061-std-package-fmt/fmt-005.ring

通过 {} 作为占位符，来格式化输出


### I. 设计 fmt::println 函数 ✅ 



-----------------------------

## 2024-02-26周 

### A. 转义字符的支持 ✅ 


### B. 多行字符串的支持 ✅ 

python 多行字符串的支持

```python
str1 = '''Le vent se lève, il faut tenter de vivre. 
起风了，唯有努力生存。
（纵有疾风起，人生不言弃。）'''
```



ring 采用和golang一样的逻辑

```ring
str1 = `multi string 
literal`
```

1. 在多行字符串中不支持转义,
2. 唯一支持的转义是 \` 用于和 多行字符串的边界区分



### C. 测试4层 class的嵌套定义 ✅



### D. 支持 对象递归的初始化 ✅


测试  ✅ 
```ring
job_1 = Job1{
        Bool:   false,
        Int:    1,
        Double: 1.1,
        String: "1.1",
        Job2:   Job2{
            Bool:   true,
            Int:    2,
            Double: 2.2,
            String: "2.2"
        }
    };
```

也可以这样:
测试  ✅ 
```ring

job_2 = Job2{
        Bool:   true,
        Int:    2,
        Double: 2.2,
        String: "2.2"
    };

job_1 = Job1{
        Bool:   false,
        Int:    1,
        Double: 1.1,
        String: "1.1",
        Job2:   job_2
    };
```




### F. 测试 字符串比较的时候, 要转化成 ne_string

FIXME:

```ring

var string[,] global_string_array_0;

if(global_string_array_0[i,j] != to_string(num)){
    fmt::println_string("test failed");
} 

```


### G. 引入多行字符串之后, 源代码的函数可能不太正确 ✅ 


测试源代码中包含:
1. block comment
2. block string

源代码的行数是否正确.


### H. 测试字符串常量的长度 超过 1024 ✅ 

-----------------------------

## 2024-02-20周 

### A. class method

测试
method 调用 method , 
method 调用 function



### C. 支持括号运算符

通过括号运算符可以明确运算的优先级



-----------------------------




## 2024-02-05周 


### A. 类中field为class的情况下要初始化默认值   ✅ 

### B. 函数调用中，局部变量的数量写死为20，如何处理一下

1. function 测试通过   ✅ 
2. method 测试通过 ✅ 


### C. 数组常量

目前已经支持了 一维数组常量 

```
int[]{1,2,3};
```


1. 需要支持二维数组常量  测试 ✅ 

```
int[,]{
    int[]{1,2,3},
    int[]{1,2,3},
    int[]{1,2,3}
};
```


2. 三维数组常量  测试 ✅ 

```
int[,,]{
    int[,]{
        int[]{1,2,3},
        int[]{1,2,3},
        int[]{1,2,3}
    },
    int[,]{
        int[]{1,2,3},
        int[]{1,2,3},
        int[]{1,2,3}
    },
    int[,]{
        int[]{1,2,3},
        int[]{1,2,3},
        int[]{1,2,3}
    }
}
```



3. 多维数组常量 TODO:测试


4. 当然这个也可以是个嵌套的，所以说通过单纯的语法分析是远远不够的，还需要语义分析 TODO:测试

```
array_0 = int[]{1,2,3}

int[,]{
    array_0,
    array_0,
}
```


### D. 关于多维数组通过 composite literal 赋值, 数组中的元素为 class object

1. 已经支持了 class-object 的 composite literal

```ring
Job {
    Bool: true,
    Int:  1,
    Double: 1.1
}
```


1. 需要支持 一维数组通过 class-object 的 composite literal 进行赋值  ✅ 

```ring
Job[] {
    Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
    Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
    Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
}
```



2. 需要支持 二维数组通过 class-object 的 composite literal 进行赋值  ✅ 

```
Job[,] {
    Job[] {
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
    },
    Job[] {
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
    }
}
```

3. 需要支持 三维数组通过 class-object 的 composite literal 进行赋值  ✅ 

```
Job[,,]{
    Job[,] {
        Job[] {
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
        },
        Job[] {
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
        }
    },
    Job[,] {
        Job[] {
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
        },
        Job[] {
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
        }
    }
}

```

4. TODO: 当然，这个也可以是个嵌套的，也可以这样，所以说通过单纯的语法分析是远远不够的，还需要语义分析

```ring

Job[,] {
    Job[]{job_value, job_value},
    Job[]{job_value, job_value}
}
```





### E. 在定义数组常量和class-object常量时，最后一个元素后边有没有逗号都可以  ✅



## 2024-01-29周 


### *A. Makefile检测 flex bison 的版本是否符合要求*  ✅ 

make echo  ✅ 
make help  ✅ 
make check: 检查源代码编译依赖  ✅ 

### *B. 重新设计并验证gc*


### *C. 测试 ring dump*


### *D. 完善 class-object literal*  ✅ 


1. new class-object literal的时候，Field的初始化顺序无需跟Class中定义的顺序一致
   
```
job_0 = Job{
        Runner: global_runner_value_0,
        Name: "1.1",
        Score: 1.1,
        JobID: 1, 
        Running: false
    };
```

### *E. 支持  class-object 多维数组*  ✅ 



### *F. 测试: 传递 string class-object array 到底是 值传递还是传递指针*


#### 多赋值 支持 array 或者是 member.field  ✅ 

./test/021-array-int/sort.ring 编译不过去, 
```
    for(i=0; i+1 < len(global_int_array_0); i+=2) {
        global_int_array_0[i], global_int_array_0[i+1] = global_int_array_0[i+1], global_int_array_0[i];
    }
```


#### 通过index访问array, index可以是个复杂表达式  ✅ 

更新 bison语法, 测试通过  ✅ 
 ./test/021-array-int/sort-2.ring 


#### 数组元素的自增运算 ✅ 

自增  ✅ 
自减  未测试 ⭕️ 

./test/021-array-int/sort-3.ring:23:36: 

global_int_array_0[j]++;

这个是编译不过去的


支持  job_value.ID++;



### *G. 区分左值和右值*  ✅ 


```
左值（L-value）是指可以放在赋值运算符左边的表达式，它代表一个具体的内存位置。左值可以被取地址、被修改、被引用，可以作为函数的参数或返回值。例如，变量、数组元素、对象成员、表达式的结果等都是左值。

右值（R-value）是指不能放在赋值运算符左边的表达式，它代表一个临时的值或表达式的结果。右值不能被取地址、不能被修改，可以被移动（move）或复制（copy）。例如，常量、字面量、临时变量、表达式的结果等都是右值。

```

这是不合法的：
```
func return_array() TreeNode {
	return TreeNode{}
}

func main() {
	return_array().Val++
}
```

这是合法的：

```
func return_array() *TreeNode {
	return &TreeNode{}
}

func main() {
	return_array().Val++
}
```


这是合法的：

```
func return_array() []TreeNode {
	return []TreeNode{}
}

func main() {
	return_array()[0].Val++
}
```


说白了，左值和右值，还得通过语义分析来判断


### *H. 自增自减运算符*

1. 没有支持前缀自增自减的运算语句，也就是不允许 ++a。
2. 运算符 ++ 和 -- 只能作为一个语句来使用，不可以作为表达式被赋值给其它的变量使用。

可以删除 generate中的 need_duplicate ✅ 


1. 自增自减运算符 运用到array上 ✅ 

2. 自增自减运算符 运用到class-field上 ✅ 


-----------------------------

## 2024-01-22周


### *A. 重构vm 中 string class-object array* ✅ 


TODO: 重构之后，heap_size要重新验证， gc要重新验证


### B. class 中支持存放array ✅ 

class中的field支持：
bool
int
double
string
class[]
bool[]
int[]
double[]
string[]
class[]

TODO: field支持多维数组


### C. 所有的没有处理的错误报错，都要添加上 ring_error_report ✅ 


### D. 如果一个数组是三维，可以访问第二维，第二维其实是个数组 ✅ 

```
    global_bool_array_0 = new bool[a,b,c,d,e,f,g,h];

    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(len(global_bool_array_0[0]));
    fmt::println_int(len(global_bool_array_0[0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0,0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0,0,0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0,0,0,0,0]));
```


### E. 要在语义检查中强制检查变量的类型

变量的定义
变量的赋值
变量的使用

函数参数的定义
函数参数的传递

函数返回值的定义
函数返回值的return
函数返回值的接收
函数返回值的数量



如何比对两个变量是否一致， TypeSpecifier, 递归比对。涉及到
- 递归比对
- field的比对
- array中value的比对
- 函数形参/实参的比对


### F. 多维数组 的 typeof 和 ring dump

1. typeof(多维数组)

多维数组 为 bool/int/double/string的时候，没有问题 ✅ 

FIXME: 当class-object的多维数组的时候，就有点问题了。


2. ring dump 多维数组


### G. class的嵌套定义与引用

在语法上要支持 job_0.Runner.Valid 多个member的调用

1. 支持递归访问field `job_0.Runner.Valid` ✅
2. 支持递归访问method `job_0.Runner.Doit()`  代测试⭕️
3. 如何检测class的递归定义（所以得引入指针的概念）


-----------------------------

## 2024-01-08周


### A. 设计支持多维数组


1. 语法层面的设计  ✅ 
2. 用户如何命名多维数组  ✅ 
3. 用户如何创建多维数组  ✅ 
4. 用户如何访问多维数组  ✅ 


1. TypeSpecifier如何组织多维数组
2. deep copy TypeSpecifier 如何copy多维数组
3. generate的时候需要支持多维数组

4. execute的时候需要支持多维数组

测试通过:
1. 多维数组 bool/int/double/string
   1. 创建 ✅ 
   2. 赋值 ✅ 
   3. 访问 ✅ 
   4. 通过 for 访问 ✅ 
2. 多维数组 支持 class-object


TODO: for-range引用到多维数组

TODO: 从多维数组中取出一个元素进行 capacity 和 length

TODO: 多维数组 literal 初始化

TODO: 对数组进行 printf, 类型不正确.

TODO: 函数调用是对参数的类型进行报错提示

TODO: ring dump 展示是否为多维数组


```
    global_int_array_0 = new int[2,4];

    fmt::println_int(len(global_int_array_0));
    fmt::println_int(len(global_int_array_0[1]));
```




如果对于一个二维数组 a[][], a[1] 其实是个一维数组, 还需要完善一下语义检查.

var int[] a; // 一维数组
var int[,] a; // 二维数组
var int[,,] a; // 三维数组

new int[10];    // 创建一维数组
new int[10,20]; // 创建二维数组 10*20
new int[10,20,30]; // 创建三维数组 10\*20\*30

a[1,2,3]; // 访问数组


如何 printf一个一维数组.

dimension: 纬度
size: 数组的大小

a[1,2,4] 纬度为3, 大小分别为 1, 2, 4 


new 多维数组的时候, size只能放int常量, 也就是还不能完全动态分配
a[1,2,4] 访问的时候, 可以放非int常量


 TODO: array literal 暂时只支持一维数组 


### 应该把 RVM_String 放在基础类型里边

-----------------------------

## 2024-01-01周

### *A. 优化: ring dump*

ring dump 支持 dump class的详情

class:
1. class 名称 ✅ 
2. class 对应的源代码文件,行数  ✅ 
3. field 数量/详情 ✅ 
4. method数量/详情 ✅ 
5. method局部变量的数量/详情 ✅ 
6. method返回值的数量  ✅ 


function/method:
1. 函数参数的数量/详情 ✅
2. 局部变量的数量/详情 ✅
3. 返回值的数量/详情


global 全局变量 ✅ 

constant 常量 ✅

数组变量 ✅ 




### *B. 类 method*


1. 定义 method的时候支持 传递参数 ✅ 
2. 调用 method的时候支持 传递参数 ✅ 
3. method中支持自定义 local variable ✅ 
4. method支持返回值 ✅ 
5. method 参数 + 局部变量的数量 不能超过 254. (self 占用一个)
6. function 参数 + 局部变量的数量 不能超过 255.
7. return list 也得有数量限制, 不能超过 255.
8. class 中 method 的数量不能超过 255 ✅ 
9. class 中 field 的数量不能超过 255 ✅ 



### *C. error-report的时候添加 location* ✅

bison  在报语法错误的时候, 需要将 TOKEN_XXX  转化成对应的字符, 方便用户查看.


ring 编译报错的时候添加一个 debug 控制 报错所在的位置,  __FILE__ __LINE__ 方便调试



### *E. print_call_stack 支持 打印 调用method的时栈信息* ✅


```

test case 1
0000$ring!Job.PrintInfo(var bool, var int, var double)
    ./test/060-std-package-debug/debug-stack-005.ring:16
0001$ring!main()
    ./test/060-std-package-debug/debug-stack-005.ring:31

test case 2
0000$ring!PrintInfo(var bool, var int, var double)
    ./test/060-std-package-debug/debug-stack-005.ring:25
0001$ring!main()
    ./test/060-std-package-debug/debug-stack-005.ring:31
```

Job.PrintInfo: 表示调用 method
PrintInfo: 表示调用 function


### *F. 需要写一个自动化工具, 编写测试用例一览图, 说明每个测试用例覆盖的场景* ✅

1. 在 测试用例的文件中, 需要用注释写明测试用途, `// TestDetail:` 前缀表示,
2. 在 `make testall` 的时候, 可以导出:
   1. 测试时间
   2. 测试数量
   3. 测试模块
   4. 测试文件
   5. 测试内容
   6. 是否通过


3. 参见 `test/automated-testing.sh`:

```
# 输出ring-测试用例表
# 是否输出测试用例表: 0/1
IS_EXPORT_TEST_DETAIL_SUMMARY=0 
# 输出测试用例表文件
TEST_DETAIL_SUMMARY="./test/ring-测试用例表.md"
```


### *G. 研究一下 bison的安装方法*

```
./configure

make && make install
```


bison 安装到指定位置之后, 需要动态设置 src/Makefile $(Bison) $(Flex)




### *H. class 中存放string* ✅




-----------------------------

## 2023-12-15周


### *A. 设计: 报错, 指示的列数不太对*


1. import package 重复 ✅



### *B. 设计: 编译错误如何自动化提示*

要继续好好研究一下 bison, bison的很多特性自己还不是特别熟悉.


1. 遇到错误如何定位到下一行, 进行错误恢复, 能够一次报出多个编译错误.
2. 编译报错的错误文案需要重新定义一下.




### *C. 设计: 类*

1. 调用 class method
2. support `self` variable in class-method.

self 不是个关键字, self可以是任何变量名, 但是在 method中比较特殊.

需要在 method 的中 添加一个隐藏的变量, self

在 method中, 只能通过 self.<field> 去访问成员变量

对象调用方法 ✅


目前method: (后续统一处理)
- 只能使用 self关键字
- 函数参数 只能为 void
- 函数返回值 只能为 void
- 不能定义局部变量
  
当前只能在 main-package 中定义



### *D. 重构: 调整相关API* ✅

所有copy函数的 dst src 都要调整成 std-api的那种形式


所有的 melloc 都调整一下格式, sizeof() 在前面, count在后面, 要注意多行折叠.



-----------------------------

## 2023-12-18周

### *A. 设计: native function 打印当前的函数调用栈*


debug::print_call_stack() 

展示当前的函数调用栈:
- 调用函数 ✅
- 调用函数所在的行数 ✅
- 调用函数对应的源码文件, 源文件行数 ✅



### *B. 如何一个源代码文件中超过10w行代码, 报错, 需要调整目录结构*

### *C. 调整 Script 脚本 用于 build, test*

-----------------------------

## 2023-12-11周

### *A. 设计: 函数调用 RVM_CallInfo 使用链表组织起来* ✅


### *B. 设计: 规划Ring 前端&后端的解耦*

目前在 RVM 执行字节码的过程中, 引用到了 AST 相关的数据, 耦合严重, 不利于后续的开发.

所以将 AST 中所有的数据结构都要进行销毁, 推进前端和后端的解耦, 为后续导出字节码奠定基础.

主要销毁的包括: 语句, 表达式, 函数, 类, 变量, 包

需要copy的:
- TypeSpecifier: 在rvm中, 根据变量的类型进行初始化 ✅
- RVM_Class:   rvm中, class-object 的初始化 ✅


### *C. 设计: 函数调用重新设计一下*


aragument_num
push_func
invoke_func 

这几个设计的有点过于繁琐了 ⭕️



CALL_INFO_SIZE_V2 需要删除掉 ⭕️


### *C. 设计: native function 打印当前的函数调用栈*


debug::print_call_stack() 

展示当前的函数调用栈:
- 调用函数 ✅



给 Function  RVM_Function 加一个字段, 就是所在的源文件名称, 和源码对应的行数

展示字节码的时候:
- 字节码 ✅
- 操作数: 分开区别 1BYTE 2BYTE 3BYTE ✅


### *D. 如何设计一个 native函数去 检测 ring当前的编译错误*

检验错误码 ⭕️
检验错误信息 ⭕️
检验错误的数量 ⭕️


### *E. ring dump 输出编译的字节码详情* 

ring dump <input-file>

1. 只输出 main package的编译情况  ✅
2. 输出 package, function, bytecode, 操作数, 对应的源代码, 函数参数的数量, 函数局部变量的数量  ✅
3. 输出 class-definition  ⭕️

TODO: ring dump 自动化测试如何设计 ⭕️



### *F. 将ring.wiki相关前端依赖存在cos, 统一使用cos提供服务*


### *G. MacOS/Ubuntu/Centos 都要编译运行测试* ✅

1. MacOS ✅
2. Ubuntu ✅
3. CentOS ✅



-----------------------------

## 2023-11-27周

### *A. 设计: 类的数组*

1. `类-数组` 类的成员支持 更新value

```
        global_job_array_0[index].Running = true;

```

这里其实有一个隐喻, 是取出 global_job_array_0[index] 的指针, 然后进行更新值


-----------------------------

## 2023-11-20周

### *A. 设计: vmcode 需要记录源代码的行数* ✅

#### 1. 要保证记录的准确性

#### 2. 能够输出源代码和字节码的映射


### *B. 设计: 类中放string*

### *C. 设计: 类的数组*

1. 声明`类` & 声明`类-数组` ✅

```
    typedef class Job {
        field bool    Running;
        field int     JobID;
        field double  Score;
    }

    var Job[] global_job_array_0;
```

2. `new`操作符为`类-数组`分配空间 ✅

```
    global_job_array_0 = new Job[200];
```


3. 通过整数索引访问数组内的元素 ✅

```
    fmt::println_bool(global_job_array_0[0].Running);
    fmt::println_int(global_job_array_0[0].JobID);
    fmt::println_double(global_job_array_0[0].Score);
```

4. for 循环访问数组内的类成员变量 ✅

```
    var int index = 0;
    for(index = 0; index < 200; index = index + 1) {
        fmt::println_bool(global_job_array_0[index].Running);
        fmt::println_int(global_job_array_0[index].JobID);
        fmt::println_double(global_job_array_0[index].Score);
    }
```


5. for-range 支持`类-数组`   ✅ 

```
    var Job job_value;

    for(job_value in range global_job_array_0) {
        fmt::println_bool(job_value.Running);
        fmt::println_int(job_value.JobID);
        fmt::println_double(job_value.Score);
    }
```

6. push 支持`类-数组`    ✅ 

```
    var Job global_job_value_0;
    global_job_value_0 = Job{
       Running: true,
       JobID: 200, 
       Score: 200.1
    };

    // push 一个 Job 变量
    push(global_job_array_0, global_job_value_0);

    // push 一个 Job 常量
    push(global_job_array_0, Job{
        Running: false,
        JobID: 201, 
        Score: 201.14
    });
```

7. pop 支持`类-数组`   ✅ 

```
    var Job global_job_value_0;

    // 从 global_job_array_0 的尾部 pop, 并获取尾部值
    global_job_value_0 = pop(global_job_array_0);

    fmt::println_bool(global_job_value_0.Running);
    fmt::println_int(global_job_value_0.JobID);
    fmt::println_double(global_job_value_0.Score);

```

8. 通过 索引为 数组内的类元素赋值  ✅ 

```
    // 通过 Job 常量 直接赋值
    global_job_array_0[0]  = Job{
        Running:  false,
        JobID:    0,
        Score:    0.0
    };

    // 通过 Job 变量 进行赋值
    global_job_value_0  = Job{
        Running:  true,
        JobID:    3,
        Score:    33.33
    };
    global_job_array_0[3] = global_job_value_0;
```

8. TODO: 

函数参数变量传递

函数返回值传递





### *D. 优化: fix_ast*

fix AST 的过程中需要对每个 expression 的 conver_type 依次进行修正

convert_type 在 generate完成之后, 可以统一销毁

1. 要解决多级嵌套的问题

```
global_class_array_0[0].Running
```


### *E. 设计: 内存池* ✅

是否有必要要考虑设计内存池, 这样在分配动态内存的时候, 直接从内存池中去取, 
能够减少内存碎片, 减少分配的速度, 同时还能检查 RVM 垃圾回收是否正常, 是否有内存泄漏

现在没有内存池的设计就是: 分配内存比较随意, 没有统一在一起, 而且查看内存分配的空间不方便, 比较粗放.

但是内存池会不会拖慢内存的分配、释放速度, 得好好测试一下, 开启内存池/未开始内存池.

所以这个功能还是急需的.

大三的时候设计过一款内存池, 所以要看看是否能够复用一下.



-----------------------------


## 2023-11-13周

### *A. 设计: import时, 各种异常情况都需要check, 人性化的报错*

#### 1. 用户导入包的顺序是可以任意的
#### 2. 用户导入的包不存在
#### 3. 用户导入的包不合法
#### 4. 用户导入的包重复



### *B. 设计: 数组/字符串的动态增长* ✅

#### 1. 如何往数组中添加元素, push 用来动态增长

```
push(array_value, 1);

value = pop(array_value);
```


注意: 
push的时候, 必须要保证 array_value 已经被new过了,  

`array_value = new int[100];`

这里看看后续是不是需要优化


#### 2. pop 用来删除最后一个元素, 删除元素之后获得最后一个元素

```
value = pop(array_value);
```

### *C. 调研: JVM switch 语句* 

### *D. 设计: 数组按照2倍增长*  ✅

bug:

```
global_bool_array_0 = new bool[0];

push(global_bool_array_0, true);

```

这样动态增长的时候, capacity 算的有问题, 因为*2, 所以一直是0


### *E. 设计: VM, 往vm中push value的时候, 没有pop的时候, 函数返回会报错, 需要对栈上的空间进行回收, call_info 的问题*

### *F. 设计: 数组+对象* ✅

### *G. 设计: to_string* ✅

```
string_value = to_string(bool_value);
string_value = to_string(int_value);
string_value = to_string(double_value);
```

添加新的字节码:
RVM_CODE_BOOL_2_STRING
RVM_CODE_INT_2_STRING
RVM_CODE_DOUBLE_2_STRING


### *H. 设计 fmt::println() fmt::printf()*

### *G. 009-package 测试用例继续拆分一下* ✅


-----------------------------



## 2023-11-06周




### *B. 设计: 数组/字符串 如何获得数组的长度&容量*  ✅


添加四个专业的字节码

```
    RVM_CODE_PUSH_ARRAY_LEN,
    RVM_CODE_PUSH_ARRAY_CAPACITY,
    RVM_CODE_PUSH_STRING_LEN,
    RVM_CODE_PUSH_STRING_CAPACITY,
```

usage:    
```
len(string_variable)
capacity(string_variable)
len(array_variable)
capacity(array_variable)
```

e.g.

```
var string local_string_value_0;

fmt::println_int(len(local_string_value_0));
fmt::println_int(capacity(local_string_value_0));


var bool[] local_bool_array_0;

fmt::println_int(len(local_bool_array_0));
fmt::println_int(capacity(local_bool_array_0));
```


### *C. 设计: 数组/字符串的越界访问*

1. 以下这几个函数在vm调用的时候, 如果超过数组的边界, 应该抛出异常, 在这里返回一个错误码, RUNTIME_ERR_OUT_OF_ARRAY_RANGE

- rvm_array_get_bool
- rvm_array_get_int
- rvm_array_get_double
- rvm_array_get_string

- rvm_array_set_bool
- rvm_array_set_int
- rvm_array_set_double
- rvm_array_set_string

2. 需要在访问数组的时候做一下处理, 报错要人性化, 能够打印出当时的调用栈信息


### *D. 设计: 数组/字符串的 for range 访问*  ✅

1. 支持了 bool[], int[], double[], string[]  的range操作

2. 语法示例:


Usage:
```
var bool[] bool_array_0 = bool[]{false, true, false};

var int index;
var bool value;
for(value = range bool_array_0) {
    fmt::println_bool(value);
}
```

Output

```
false
true
false
```

3. VM层面添加几个专用的字节码: 

```
    RVM_CODE_FOR_RANGE_ARRAY_BOOL,
    RVM_CODE_FOR_RANGE_ARRAY_INT,
    RVM_CODE_FOR_RANGE_ARRAY_DOUBLE,
    RVM_CODE_FOR_RANGE_ARRAY_STRING,
    RVM_CODE_FOR_RANGE_ARRAY_OBJECT,
    RVM_CODE_FOR_RANGE_STRING,
    RVM_CODE_FOR_RANGE,
    RVM_CODE_FOR_RANGE_FINISH,
```

### *E. 支持给数组中的元素赋值*  ✅

1. 支持对 bool[], int[], double[], string[] 中的元素进行复制

2. 语法示例:


Usage:
```
  var bool[] global_bool_array_0  = new bool[20];

  global_bool_array_0[0] = true;
```

### *F. 修正*  ✅

改回去
```
    if (declaration->type->next->kind == RING_BASIC_TYPE_BOOL) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_BOOL, (2 << 8) | (1), array_index_expression->line_number);
    } else if (declaration->type->next->kind == RING_BASIC_TYPE_INT) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_INT, (2 << 8) | (1), array_index_expression->line_number);
    } else if (declaration->type->next->kind == RING_BASIC_TYPE_DOUBLE) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_DOUBLE, (2 << 8) | (1), array_index_expression->line_number);
    } else if (declaration->type->next->kind == RING_BASIC_TYPE_STRING) {
        generate_vmcode(executer, opcode_buffer, RVM_CODE_PUSH_ARRAY_STRING, (2 << 8) | (1), array_index_expression->line_number);
    } else {
        printf("error: array index expression only support bool[] int[] double[] string[]\n");
        exit(1);
    }
```

---------------------


## 2023-10-30周

   

1. 修正一下 class object 相关的gc  ✅
2. 通过函数传递 class object
   1. 可以通过函数传递 但是是 浅copy,  ✅
   2. 需要优化成 深度 copy
3. array & class object
4. array & string
   1. 命名array-string: var string[] string_array; ✅
   2. 分配空间: string_array = new string[10]; ✅
   3. 分配空间初始化: string_array = string[]{"a"}; ✅
   4. 访问array-string: fmt::println_string(string_array[0]); ✅
   5. gc heap_size 计算的不对
   6. 还没有 check gc是否正常
   7. 内存分布还得好好重构一下
5. 数组访问 要panic报错 index越界
6. 支持 for range
7. 优化语义检查
8. string的动态增长
9. array的动态增长
10. 有了 var 之后, 是不是让 匿名函数变得复杂了
11. ast 中 每个 expression 都要 fix conver_type (TypeSpecifier*)
12. 修正 vm execute 过程中 写死的 local_variable_count = 20;

13. class-object 的初始化 暂时不用 constructor函数, 使用类似于Golang的 列表初始化

> var Job job_0 = Job{
> 
>    Running: false,
> 
>    JobID: 0,
> 
>    Score: 0.0
> 
> };
>

遗留问题:
    0. 简单测试没有问题  ✅
    1. 初始化列表的数量 必须要跟 class成员变量的数量 一致
    2. 初始化列表的顺序 必须要跟 class成员变量的顺序 一致

class 内部的 constructor 函数是不是要废弃
constructor 应该作为默认的初始化函数
> var Job job_0(); // 这里就是去调用 constructor函数
>


---------------------


## 2023-10-23周

1. 如何判断rvm上object是否发生了深度copy, 同时尽量不要通过在rvm中debug print的方式  ✅
> 通过 fmt::println_pointer 来打印实际存储数据的地址
> 
2. 重构 heap 内存分配 ✅
3. 通过工具 可以将 Ring 虚拟机指令集生成一个 markdown表格 ✅
> make tool_gen_vmcode_doc && ./bin/tool_gen_vmcode_doc
4. 函数 返回 array string object 去完成深度copy ✅
5. 函数可以返回 数组  ✅
6. 可以传递数组 给 函数  ✅
7. bug 数组不能赋值
8.  使用 bool 数组 (new bool[10], bool[]{})  ✅
> Usage:
> 
> var bool[] bool_array_0 = new bool[10];
>
> var bool[] bool_array_1 = bool[]{false, true};
9.  bug  ✅
    - string 的初始化, 默认值, 都要重新审视一下
    - fmt::println_string 有bug 如果数据很多会有bug
10. 实现一个简单的垃圾回收机制 mark&swap  ✅
11. native 函数 添加 vm::grbage_collect  ✅
12. Add native function vm::heap_size  ✅
13. 计算 heap_size 的方式需要重新计算  ✅ 
14. 要区分 length size capacity ✅


-----------------------------


## 2023-10-16周

1. 编译阶段和运行阶段某些工作要拆分开来
    某些结构体要及时释放, 不要相互依赖
2. 重新组织一下 std package 测试集
3. 每行后边的; 是不是可以去掉
4. 完善文档 Ring编译器开发规范 ✅
5. 重构一些代码和注释  ✅
6. 完善优化一下 vm_debug ✅
7. 完善一下 debug summary info  ✅
8.  完成一个简单的垃圾回收机制 mark&swap ✅


-----------------------------


## 2023-10-07周

1. 构想、实现 一下 reflect package ✅
2. 构想、实现 一下 any 类型 ✅
3. 把一键安装完善一下 https://cloud.tencent.com/developer/article/1884133
4. reflect 需要反射 bool int double string class array ✅
5. any 类型需要在语义分析的时候进行检查
6. 语法上还要支持可变参数 function println(var any... any_value_list); ✅
7. 函数内 读取可变参数列表，得需要某种方式，e.g.  for value := range any_value_list {}
8. golang 这个 example这个网站可以好好学习一下 ✅
    https://gobyexample.com/
    https://github.com/mmcgrana/gobyexample
    生成ring的example website    https://example.ring.wiki
9. 构想、实现一下 os io std-package


### bug 1

```
    function test(var any any_value) {
        fmt::println_string(reflect::typeof(any_value));
    }

    error: generate opcode error
```

### bug 2
    
```
function test(var int... int_value) {
}


@main
function main() {
    var int int_value_0;
    var int int_value_1;

    test(int_value_0, int_value_1);
}
```
执行的时候会挂掉

### reflect 构想 通过函数名字获取函数类型 

```
function test(var bool bool_value, var int int_value)->(string) {

}

reflect::typeof(test);  // function(bool, int)->(string)
```

### 构想一下 for range

```

var int[] int_array;
for (key, value = range int_array) {
    fmt::println(key);
    fmt::println(value);
}
```

-----------------------------


## 2023-09-25周

## 2023-09-18周

1. 完善类数组
2. 函数传递数组、类、类数组
3. 把一键安装完善一下
4. 再完善一下语义分析
5. 想着把 import 关键字 改成 using  评估一下


## 2023-09-11周

## 2023-09-04周

## 2023-08-28周


1. 完成一个简单的垃圾回收机制 mark&swap
2. 通过RVM_RuntimeHeap 去分配内存
3. 自动化测试automated-testing.sh展示有点简陋，看看是否可以用 GoTest来搞定自动化测试
4. 优化语义分析
5. 优化 break continue return goto
6. 修复一下测试用例中的bug ✅
    6.1 minus运算符 操作 double literal的时候失败  ✅
    6.2 var string string_value; 定义之后不使用，不赋值，就进行访问，会内存错误  ✅
7. 好好完善一下 Makefile 各种debug宏 ✅
8. 添加完善一键安装的功能
   1. curl -sSL https://ring.wiki/install.sh | sh  ✅
   2. 在每发布一个 release版本的时候，需要在cos上自动创建对应版本的源码，install安装脚本。通过 github action
9. 实现 jump 跳转指令 重新评估一下 ✅
10. std/vm 标准库获取heap_size native函数需要支持返回值 ✅
11. 要把 invoke_native_function 和 invoke_derive_function 的逻辑合起来
12. bug , 如果一个函数有返回值，但是没有收集返回值，会报错， vm::heap_size() 就会报错 ✅
13. 优化 std lib vm ✅


-----------------------------


## 2023-08-21周

1. 完成一个简单的垃圾回收机制 mark&swap
2. 通过RVM_RuntimeHeap 去分配内存
3. 自动化测试automated-testing.sh展示有点简陋，看看是否可以用 GoTest来搞定自动化测试
4. github action workflow 自动构建release 预编译版本 ✅
5. 调研：以下几种编译方式 ✅
    - 源代码安装
    - 预编译安装
    - apt yum brew 软件源安装

6. sizeof() typeof()
7. flex bison 记录的行号不是太准确，比如说，对于function的定义，他会跑到最后一行，应该定位到function 定义的第一行
8. function variable package 的名字不可以一样
clang：报错
 redefinition of 'a' as different kind of symbol
1. ring man <keyword> 快速提示语法结构 ✅


-----------------------------


## 2023-08-14周

1. 优化string
    - 动态内存分配 size capacity append 增长
    - 通过索引访问
    - 优化字符串的拼接
    - fmt::to_string 函数，这样的话，是需要反射的，因为传入的变量可以是 int double string
    - size() 获取string的长度
    - fmt::printf("string_value_1 value:{}, size:{}\n", string_value_1, size(string_value_1)); 这也是需要反射
2. 优化完成string之后，优化 fmt 函数， fmt::println() -> io::write(var string str)
3. 优化报错信息 ✅
4. 完成一下测试用例
    函数变量传递 array string class变量
5. 完善 array class
6. 完善 array string
7. 完善多维数组


-----------------------------


## 2023-08-07周

1. 优化 runtime_stack 空间，要通过局部变量的数量来动态增长 空间
2. 想清楚全局变量、局部变量 初始化的时机 ✅
2.1 用户在使用ring的时候，不能在 global{} 块中进行全局变量的初始化 ✅
    必须要通过 function init(){} 对全局变量进行初始化
    如果main包import 了 fmt:
        函数的调用顺序为：fmt::init() -> main::init() -> main::main()

测试：在global中 定义全局变量时，初始全局变量。

3. 优化报错信息  将所有的printf 改成 compile_error runtime_error
4. 报错脚本的自动化测试✅

```
通过 ErrorReportContext 来实现
ErrorReportContext context = {

};
ring_compile_error(&context); // 每次ring_compile_error 都要添加一下错误次数，错误次数多了才要退出
```

错误信息:

```
./test/998-error-report/error-000.ring:10:0:
|       a;
|       ^......use undeclared variable identifier `a`; E:ERROR_UNDECLARED_IDENTIFIER
Advice: definite variable `a` like: `var bool|int|double|string a;`

./test/998-error-report/error-000.ring:10:0:
|       a;
|       ^......use undeclared variable identifier `a`; E:ERROR_UNDECLARED_IDENTIFIER
Advice: definite variable `a` like: `var bool|int|double|string a;`


1 error generated.

```

compile
synx_
fix_ast

应该细分一下，首先进行语义分析，将错误尽可能的报出来，同时还要积攒数量。
不然的话，fix_ast 可能会出错。
语义分析的时机，编译完成之后，fix_ast 之前。
语义分析的对象是 Package

但是目前一个Package 里边只能有一个PackageUnit 也就是一个包只能有一个文件
一个package 中 可以含有多个 global{} 块。
一个package 中 可以含有多个 init() function{} , 需要通过 @init-priority:1 来生命初始化的优先级

5. 还有一个没有搞明白
    ring 的前端是依赖两个工具flex 和 bison
    如果某个输入有语法错误，那么bison将会直接退出，如何更好的做语法检测。这个还真不太好搞。


-----------------------------

## 2023-07-31周

1. 全面重构类型系统 ✅
2. 修复 int[] double[] 的相关bug ✅
3. 支持数组的初始化赋值，var int[] array = int[]{1, 2, 3, 4}; ✅


-----------------------------

## 2023-07-24周

1. global block 可以有多个，e.g.

```
global {
}
global {
}
```

2. 实现 var int[] array ✅
3. 实现 new int[10], 暂时只支持一维数组 ✅
4. 实现 array = new int[10]; ✅
5. 在 vm 中要实现类型map 的查找和匹配

-----------------------------

## 2023-06-05周

1. 通读《自己动手实现Lua：虚拟机、编译器和标准库》 1-13章
2. 对学到的支持 优化Ring 数组
3. make install bug & 标准库路径写死的bug ✅


-----------------------------

## 2023-05-29周

1. 自己建立一个新的项目，目的是对Lua的字节码有一个较深的理解
   1. 深度学习Lua字节码
   2. 参考 《自己动手实现Lua：虚拟机、编译器和标准库》 1-13章
   3. 参考 https://github.com/GeneralSandman/luago-book
   4. 自己的项目 就是通过CPP来解析Lua的字节码
   5. 项目地址：https://github.com/GeneralSandman/GeneralSandman-lua-learn-node


1. lua-learn-node
   1. 完成了第二章的学习，并可以顺利通过CPP完成对第二章要点的完全掌握。
2. 对知乎专栏Lua模块精讲的学习
   1. Lua设计与实现 基于lua源码对其设计与具体实现进行剖析 https://www.zhihu.com/column/c_1097089416010567680


- 调研标准库的方式
- 参考lua 的 linux man 手册的编写
    https://linux.cn/article-10130-1.html
- Lua 二进制 Chunk的形式，写一个解析程序。学习《自己动手实现Lua：虚拟机、编译器和标准库》 1-13章
- https://github.com/GeneralSandman/luago-book
- lua设计与实现 https://www.zhihu.com/column/c_1097089416010567680

- 思考：全局变量初始化的时机


-----------------------------

## 2023-04-23周

- import 导入包
- std 标准包
- 完善所有的测试用例
- 优化函数的 return list
- 优化 基础 类型 string

- 实现：import 的相关功能 通过import 使用package内的函数     操作符使用 ::  方法的定义也使用 ::✅
- 实现：导入std-fmt包，使用fmt相关库函数，同时要设计好native函数要怎样register才能更方便    --有bug  优先fix
- 实现：import 的相关功能 通过import 使用package内的函数     操作符使用 ::  方法的定义也使用 ::
  - package::函数 ✅
- 实现：导入std-fmt包，使用fmt相关库函数，同时要设计好native函数要怎样register才能更方便     ✅
- 实现：import 的相关功能 通过import 使用package内的函数     操作符使用 ::  方法的定义也使用 ::
  - package::全局变量 ✅
  - package::类定义
- 测试：把所有的测试case统一做了更新  ✅
- 实现：解决 std package 路径的问题
- 调研：调试器  ✅
- 优化：记录原始行号的功能  ✅
- 优化：优化全局变量的一些逻辑  ✅
- 重构：重构了一些代码逻辑  ✅


- 实现：函数的返回类型
- 优化：函数的调用栈
- 优化：函数的局部变量
- 实现：method 使用 self关键字


- 实现：类的构造函数
- 修复：全局变量的初始化
- 修复：类的局部变量的初始化
- 优化：统一 execute 的时候 调用 native derive  function 的方式
- 设计：全局变量初始化的时机 

-----------------------------


## 2023-04-17周

1. 关于源代码切分
- 实现：package import 
- 实现：分package编译 生成字节码 链接

包的名称 不能 和类变量的名称一样，不然会有逻辑问题

- 实现：PacageUnit等 static变量的优化 
- 实现：根据import-package名称去访问 package内的function
- 优化：单文件内 对象的访问
- 实现：class method使用self关键字
- 实现：class method参数和返回值
- 实现：class 构造method
- 测试：完善 class 的相关测试
- 实现：好好实现 std-fmt 库，同时优化 native函数
- 实现：实现比较好用printf函数
- 设计：设计可变参数
- 实现：function method 返回值的严格检验 与 返回值处理

- 实现：源代码的切分编译 ✅
- 实现：编译器从C语言全部转为C++ ✅
- 重构：源代码没有变量编译错误 bug  ✅
- 重构：源代码import为空时编译错误 bug  ✅
- 重构：创建AST时，将 class_definition_list 和 function_list 转为 CPP-vector，更好的管理内存 ✅
- 实现：源代码的切分编译、打包 ✅
- 实现：导入使用 package ✅
- 实现：定义package ✅
- 实现：main 函数  ✅
- 优化：一些编译告警  ✅
- 修复：一些全局变量的默认初始值的bug  ✅
- 实现：去除编译warn告警，提高编译速度 ✅
- 实现：全局变量的定义采用一个比较好的 方式 global{}  ✅
- 实现：import 的相关功能 通过import 使用package内的函数     操作符使用 ::  方法的定义也使用 ::


-----------------------------


## 2023-04-10周

1. 实现面向对象的部分逻辑
- 实现：面向对象 field
- 实现：面向对象 method
- 实现：属性@public @private @constructor

2. 关于字节码二进制
- 实现：源代码与字节码的对应关系 更好的debug
- 理解：Lua字节码的定义，如果生成字节码，如何解析字节码


3. 关于源代码切分
- 实现：package import 
- 实现：分package编译 生成字节码 链接

4. 一些想到的问题
- 实现：属性 @format 应用到某个类的成员函数 定义重载打印对象数据结构的
- 虚拟机：当时设计的不足，不如预先分配一个比较大的空间 不能获取局部变量的数量
- 调研：调研现在主流的调试器


- 实现：外部访问成员变量 ✅
- 实现：通过对象访问成员变量：如job_0.Running = false; 如 println_bool(job_0.Running) ✅
- 设计：self 不设计成系统关键字，也就是不再语法分析的时候，不把他当作是一个token ✅
- 实现：通过对象调用成员函数method，只是简单实现了，见 008-class/class-001.ring ✅
- 实现：在method中访问field，涉及到self关键字
- 实现：Class 定义里边重新进行编写   field 一个list  method 一个list
- 实现：构造method
- 实现：实现@public @private
- 理解：Diksam 在生成字节码的时候 同时记录与源代码之间的关系 LineNumber✅
- 实现：Ring实现记录字节码与源代码的映射关系✅
- 重构：简单重构一下代码✅
- 实现：main函数 @main
- 理解：Diksam 是如何实现源代码切分的，也就是require ✅
- 设计：Ring 多源代码输入的编译逻辑 ✅
- 实现：Ring 的package定义 和 import 导包 ✅
- 设计：Ring 多源代码输入的编译逻辑
  - 参考 GO env
- 调研：调试器

----------------------------------

## 2023-04-03周

实现面向对象
- 理解：diksam 面向对象、源代码切分、面向对象内存分配
- 设计：成员变量的场景  成员方法放在下一期
- 设计：面向对象的语法
- 实现：面向对象的语法
- 设计：虚拟机支持 面向对象的 内存分配
- 实现：虚拟机支持 面向对象的 内存分配
- 测试：面向对象的测试用例
- 设计：字节码二进制文件的生成、解析   好好参考一下 Lua


-----------------------------


## 错误提示

1. 使用有意义的错误消息：确保错误消息清晰明了，能够准确地指出问题所在。错误消息应该包含有关错误类型、位置和可能的解决方法的信息。
2. 提供上下文信息：在错误消息中提供尽可能多的上下文信息，以帮助用户理解问题。例如，可以包含相关的语法规则、输入符号和预期的符号等信息。
3. 提供详细的错误位置：在错误消息中指明具体的错误位置，以帮助用户快速定位问题。可以在错误消息中显示行号、列号或具体的代码片段。
4. 提供建议的修复方法：如果可能的话，可以在错误消息中提供一些建议的修复方法。这些建议可以是常见的错误修复方法，或者是根据上下文推断出的可能的解决方案。
5. 支持自定义错误处理：允许用户自定义错误处理函数，以便在发生错误时采取特定的行为。这样用户可以根据自己的需求自定义错误处理逻辑，例如记录错误日志、尝试自动修复等。
6. 提供详细的文档和示例：为bison工具提供详细的文档和示例，以帮助用户更好地理解和使用工具。文档应该包含有关错误处理的详细说明和示例代码，以及常见错误的解决方法。


要实现类似于Clang的智能化错误提示，需要进行更复杂的处理和分析。以下是一些可能的方法和技术：

1. 语法分析：使用更高级的语法分析技术，例如LLVM的Clang，可以检测和报告更复杂的语法错误。这可以包括缺失的分号、括号不匹配、不完整的语句等。
2. 语义分析：通过对代码进行语义分析，可以检测诸如未声明的变量、类型不匹配、函数调用错误等更高级的错误。这可能需要构建符号表、进行类型推断和类型检查等。
3. 数据流分析：通过数据流分析，可以检测和报告一些潜在的问题，例如未使用的变量、未初始化的变量、可能的空指针解引用等。
4. 代码规范检查：可以集成代码规范检查工具，例如Clang的静态分析器（Clang Static Analyzer）或其他工具，来检测代码中的潜在问题和违反规范的情况。
5. 模糊匹配和纠错：在发现错误时，可以使用模糊匹配和纠错技术，尝试推测用户的意图并提供可能的修复建议。例如，当用户在代码中输入了拼写错误时，可以通过推断正确的标识符并给出修复建议。
6. 上下文敏感的错误提示：利用上下文信息，可以更准确地定位错误和提供错误提示。例如，当用户在函数调用中传递错误的参数类型时，可以根据函数声明和调用上下文提供更具体的错误提示。



模糊匹配和纠错是一种常见的技术，用于推测用户的意图并提供可能的修复建议。以下是一些常见的模糊匹配和纠错方法：

1. 编辑距离：编辑距离是衡量两个字符串之间差异的度量，可以用于比较输入的错误单词与正确单词之间的相似程度。常见的编辑距离算法包括Levenshtein距离和Damerau-Levenshtein距离。可以计算输入单词与词典中的单词之间的编辑距离，并推荐与输入单词距离最近的正确单词作为纠错建议。
2. N-gram模型：N-gram模型是一种基于统计的语言模型，用于预测下一个词的可能性。可以使用N-gram模型来预测输入单词的下一个可能的单词，并给出基于上下文的纠错建议。
3. 词向量：词向量是将单词映射到连续向量空间的表示方法。可以使用词向量来计算输入单词与词典中的单词之间的相似度，并推荐与输入单词最相似的正确单词作为纠错建议。
4. 上下文信息：利用上下文信息，可以更准确地推测用户的意图和提供纠错建议。例如，当用户在代码中输入了拼写错误的标识符时，可以根据上下文中的其他标识符和语法规则推断正确的标识符。

以上方法可以结合使用，以提供更准确和智能的模糊匹配和纠错功能。具体的实现可以依赖于机器学习模型、自然语言处理技术和数据集的训练。例如，可以使用大规模的文本语料库进行训练，并构建模型来进行模糊匹配和纠错。同时，还可以根据特定领域的需求进行定制化的模型训练和优化。


上下文敏感的错误提示，这个怎么实现

实现上下文敏感的错误提示需要对代码的语法和语义进行深入分析，并根据上下文信息来判断可能的错误和提供相应的错误提示。以下是一些常见的实现方法：

1. 符号表：构建符号表来跟踪代码中的变量、函数和类型的声明和使用情况。通过分析符号表，可以检测未声明的变量、重复定义的变量、变量类型不匹配等错误，并在错误提示中提供准确的位置和相关信息。
2. 类型推断和类型检查：通过对代码进行类型推断和类型检查，可以检测类型不匹配、错误的函数调用、错误的操作符使用等错误。这需要构建和维护类型信息，并对代码进行静态分析。
3. 控制流分析：通过控制流分析，可以检测潜在的逻辑错误和代码路径不可达的情况。这可以帮助用户发现可能的错误逻辑和错误的条件分支。
4. 数据流分析：通过数据流分析，可以检测未使用的变量、未初始化的变量、可能的空指针解引用等问题。这需要跟踪变量的定义和使用情况，以及对数据流进行分析。
5. 模式匹配和规则检查：根据特定的代码规范和模式，可以检查代码中的潜在问题。例如，检测不安全的函数调用、内存泄漏、未释放的资源等。
6. 上下文窗口：维护一个上下文窗口，根据当前位置周围的代码片段提供错误提示。这可以包括相关的语法规则、变量使用情况、函数调用等信息，以帮助用户理解错误的上下文。
