
# Ring 历史版本


## Ring 里程碑



<iframe id="embed_dom" name="embed_dom" frameborder="0" style="display:block;width:550px; height:550px;" src="https://www.processon.com/embed/622821431e08535e1b8a5241"></iframe>


> [!TIP|style:flat|label:Ring里程碑制作]
> https://www.processon.com/embed/622821431e08535e1b8a5241
> 
> https://www.processon.com/diagraming/622821431e08535e1b8a5241
> 


---------------------


> [!NOTE|label:Ring Version]
> 
> 🔥表示release版本
> 未注明均为beta版本
>
> 


---------------------


## v0.2.16

> Date: 2024-08-13

### Features

1. 支持了 easy协程
2. std 标准库丰富了一下


---------------------


## v0.2.15

> Date: 2024-03-26

### Features

1. 新增基础数据类型 int64 (当前基础数据类型有：bool,int,int64,double,string)
2. 对运算符的操作数做了更加细致的语义检查。
3. fmt package 函数 `fmt::printf()` 和 `fmt::println()` 可以打印 数组和类详情

---------------------


## v0.2.14

> Date: 2024-03-26

### Features

1. 多维数组
   1. 语法上支持多维数组, 定义一个二维数组`var int[,] array;`, 或者`var int[!2] array;`
   2. 新建二维数组, `array = new int[2,3];` 2*3的数组
   3. 对数组进行访问, `array[1,2] = 1;`
   4. 可对数组的不同维度取 length capacity
   5. 可以通过for-range 访问多维数组
   6. 数组中的元素可以是  bool,int,double,string,class
   7. 同时可以支持多维数组常量
2. 类
   1. 类中的field 可以是 bool,int,double,string,class,数组
3. 删除 `++a` 前置自增操作符
4. bison中引入 左值和右值的概念
5. 继续优化了GC逻辑, 针对于 string, array, 但是 真对于array-class-object还是有点问题
6. 引入两个 源码依赖
   clipp: 解析命令行参数
   linenoise: 交互式命令行输入,提示,补全
7.  fmt package 添加函数 `fmt::printf()` 和 `fmt::println()`
8. reflect package 中 typeof() 操作多维数组时, 进行了优化
9. ring dump 可以支持多维数组和类
10. 实现了一个简单 debugger
    1.  设置/清除/列出 断点
    2.  实时打印栈
    3.  打印全局变量, 局部变量
    4.  stop-at-entry, 继续执行
    5.  单行执行


---------------------


## v0.2.13

> Date: 2024-01-08

### Features

1. 调整虚拟机执行过程中, 函数调用链的标识方法, 使用双向链表表示`RVM_CallInfo`
2. Ring 前端&后端的解耦: 但是仍旧有部分未完成
3. `debug:print_call_stack()` 打印当前的函数调用栈
4. `ring dump`输出编译的字节码详情
5. MacOS/Ubuntu/Centos 都编译运行测试
6. 类 method 支持 
   1. self变量
   2. 参数
   3. 临时变量
   4. 返回值
7. 重新优化了一轮编译报错


---------------------


## v0.2.12

> Date: 2023-12-05

### Features


1. 优化 class
   1. 支持 对象的初始化和赋值, 通过class-object常量 ```job_0 = Job{Running: false};```
   2. 支持 对对象的成员变量进行赋值, ``` job_0.Running = false; ```

2. for-range 语法实现
   1. 语法 ``` for(value in range array_value) {} ```
   2. 对 bool[] int[] double[] string[] class-object[] 支持了 for-ranges
   2. GC对象默认 标记为 WHITE
   3. 从根节点(static, runtime_stack)出发, 遍历对象, 标记对象访问可达(BLACK),
   4. 将 WHITE 的GC对象进行回收

3. 数组: 支持通过数组+索引给数组内的元素赋值
   1. 语法: ``` array_value[index] = value ```
   2. 对 bool[] int[] double[] string[] class-object[]

4. 数组/字符串: 获取 length capacity
   1. 语法: ``` len(string_value) ```  ``` capacity(string_value) ```
   2. 语法: ``` len(array_value) ```  ``` capacity(array_value) ```

5. 数组: push pop
   1. 语法: ``` push(array_value, value) ```  ``` value = pop(array_value) ```

6. 内置函数: to_string
   1. bool int double 都可以转成string

7. 引入MemoryPool
   1. 前期作为内存管理的方式, 主要用于检验gc算法的正确性, 后期不用MemPool, 完全依赖gc
   2. 目前分为这几个内存池:   
      1. front_mem_pool: 编译器前端MemPool, 主要存放AST, 包信息等结构
      2. rvm->data_pool: 存放rvm运行过程中分配的数据
      3. rvm->meta_pool: 存放rvm运行过程中分配的元信息, (因为rvm是有runtime的, 需要维护常量表等等数据结构)
   3. 在前端编译完成之后, 强制释放 front_mem_pool, 用于前后端的解耦


8. 可以通过工具快速到处字节码的详情, 输出markdown格式




### Changed

1. 编译过程中, 之前使用的c语言的方式去管理数组, 这里使用 std::vector 进行管理
2. 调整目录结构, 分为 src/ test/ ring.wiki/ bin/
   1. 分为两个 Makefile, 互不影响
3. Debug宏可以 展示 Memory Pool 内存分配的详情
   1. 打开 DEBUG_RVM_MEM_POOL_DETAIL 即可
4. 将所有的动态内存 统一在 MemoryPool中进行分配, 易于管理




---------------------


## v0.2.11

> Date: 2023-10-31

### Features

1. Garbage Collection 实现
   1. 实现了最简单的STW Mark&Sweep GC算法
   2. GC对象默认 标记为 WHITE
   3. 从根节点(static, runtime_stack)出发, 遍历对象, 标记对象访问可达(BLACK),
   4. 将 WHITE 的GC对象进行回收
2. Garbage Collection Usage
   1. vm package 中添加 函数: vm::garbage_collect()
   2. 用户程序需要手动触发垃圾回收  ``` vm::garbage_collect() ```
   3. vm::heap_size() 可以查看当前 heap 分配的内存
3. 重构了一下 heap 分配内存的函数细节
   1. 分配内存 添加到 heap双向链表中
   2. 对 GC对象进行回收 就是从双向链表中删除
4. 添加了个工具: 可以自动化导出当前 VM 字节码的细节, 树出一个 markdown 文档
5. 添加一个 reflect std-package, 能打印出变量的类型
6. 支持了 string数组
   1. 定义 string 数组: var string[] string_value;
   2. new 开盘空间: string_value = new string[10];
   3. 通过 string 常量初始化 string数组: string_value = string[]{"a", "b"};
   4. 通过index 访问 string数组: fmt::println_string(string_value[0]);
7. 支持了 bool数组
   1. 定义 bool 数组: var bool[] bool_value;
   2. new 开盘空间: bool_value = new bool[10];
   3. 通过 bool 常量初始化 bool数组: bool_value = bool[]{false, true};
   4. 通过index 访问 bool数组: fmt::println_bools(bool_value[0]);


### Changed

1. Debug宏可以打印字节码的详情
   1. 打开 DEBUG_GENERATE_OUTPUT_VMCODE 即可
2. Debug宏可以打印GC详情
   1. 打开 DEBUG_RVM_GC_DETAIL 即可
3. RVM 交互式 调试 可以 展示 fmt::println_string() 打印的数据
4. 在调用derive函数的时候, runtime_stack 存储 callinfo 的形式做了改变, 直接用指针存储


---------------------

## 历史版本

| 时间       | 版本    | 特性                                                                                                                                      |
| ---------- | ------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
|            |         | 生态：支持网络连接                                                                                                                        |
|            |         | 生态：自己写点 系统调用函数、字符串操作库函数、文件读写、能够处理一些简单的日常场景                                                       |
|            |         | 模块：支持并发编译                                                                                                                        |
|            |         | 模块：支持import导包                                                                                                                      |
|            |         | 模块：支持package命名包                                                                                                                   |
|            |         | 异常：支持异常的抛出与捕获                                                                                                                |
|            |         | 面向对象：支持类，如果没有成员函数时，就是struct，无性能损耗                                                                              |
|            | hard    | 数据类型：支持 指针 new delete                                                                                                            |
|            | hard    | 数据类型：数据类型精细划分 int32 uint32 int64 uint64 double                                                                               |
|            | hard    | 运算符：只是类似c语言的 sizeof 获取数据类型的空间大小                                                                                     |
|            | hard    | 数据类型：如何设计指针                                                                                                                    |
|            |         | 函数：调用时支持参数名匹配参数值，参数的顺序可以与声明时不一致                                                                            |
|            |         | 函数：支持默认参数                                                                                                                        |
|            |         | 函数：支持 main 函数                                                                                                                      |
|            |         | 数据类型：在一个子代码块中如果想要实访问全局变量，必须使用global 声明这个变量。否则视为语法错误。                                         |
|            |         | 语义分析：优化报错信息。                                                                                                                  |
|            |         | 语义分析：优化完善语义分析，扫描各种语义错误，优化报错分析                                                                                |
|            |         | 控制语句：支持defer语句                                                                                                                   |
|            |         | 函数：支持 匿名函数                                                                                                                       |
|            |         | 函数：支持 函数变量、赋值、bind、指定定义函数类型，函数参数支持传递函数变量                                                               |
|            |         | 设计：把Ring的源代码转成 c++11，这样对于内部使用string，map自己就不用重新实现了。                                                         |
|            |         | 控制语句：优化 if-else、for、do-for 语句，与函数相结合时，里边需要支持 return                                                             |
|            |         | 表达式：支持通过括号来定义操作符的优先级。                                                                                                |
|            |         | 数据类型-数组：索引支持负数                                                                                                               |
|            |         | 语法：支持/**/ 注释                                                                                                                       |
|            |         | inner：修改内部创建语法树时的block                                                                                                        |
| 2023-10-20 | v0.2.10 | 优化：添加了 os、io、reflect std-package, 准备开始写GC 和 完善内存管理                                                                    |
| 2023-09-20 | v0.2.9  | 优化：部分语义分析、native-function 返回值的问题、字符串的bug                                                                             |
| 2023-08-25 | v0.2.8  | 优化：报错提示& ring man <keyword> 提示语法规则                                                                                           |
| 2023-08-09 | v0.2.7  | 优化：全局变量&局部变量的初始化时机                                                                                                       |
| 2023-08-09 | v0.2.6  | 优化：优化编译报错机制、make instll 标准库的安装位置;                                                                                     |
| 2023-08-04 | v0.2.5  | 数组：int/double 支持创建 数组常量, 通过数组常量来快速对一个数组进行初始化：int_array = new int[3];  int_array = int[]{1, 2, 3};          |
| 2023-07-28 | v0.2.4  | 数组：支持定义double数组变量，支持new数组，支持访问数组；但是只支持 double数组，仍然有很多bug，后续需要慢慢修复                           |
| 2023-07-27 | v0.2.3  | 数组：支持定义int数组变量，支持new数组，支持访问数组；但是只支持 int数组，仍然有很多bug，后续需要慢慢修复                                 |
| 2023-06-20 | v0.2.2  | 标准库：标准库通过makefile 安装到 系统  /usr/local/ring 目录中                                                                            |
| 2023-04-25 | v0.2.1  | 较大版本的优化，支持 std-package，优化类，优化native函数                                                                                  |
| 2022-08-12 | v0.2.0  | 类：支持类的定义，支持在static空间创建类对象，支持类成员变量的初始化，类成员变量的访问，暂时不支持类成员变量的修改和赋值                  |
| ---------- | ------- | ---------------------------                                                                                                               |
| 2022-06-15 | v0.1.19 | 类型转换：支持基础类型的转换，支持字符串的拼接，修复double类型运算时的一些bug，但仍有一些bug。类型转换：double_value = <double>int_value; |
| 2022-06-15 | v0.1.18 | 函数调用：添加更加遍历的打印函数  print println printf printfln ，支持可变参数                                                            |
| 2022-06-13 | v0.1.17 | 函数调用：消除函数返回值的bug，在函数调用完成时释放运行栈内的函数实参。  表达式：支持三目条件表达式 true ? true : false;                  |
| 2022-05-31 | v0.1.16 | 变量：支持同时定义多个相同类型的变量和初始化， var int a = 1; var int b,c = 1,2;                                                          |
| 2022-05-31 | v0.1.15 | 函数：支持函数定义的实参（parameter）和函数调用的形参（argument），以及函数的局部变量，实参+局部变量的数量 最多 支持164个。               |
| 2022-05-27 | v0.1.14 | 函数：支持return语句，类似Go语言，可以返回多个返回值，同时赋值运算可以在函数返回后多重赋值运算  ```a,b,c = func();```                     |
| 2022-05-27 | v0.1.13 | 运算符：对于赋值运算符号，支持多重赋值运算，如：a,b,c=1,2,3;                                                                              |
| 2022-05-26 | v0.1.12 | 控制流：对 for do-for 语句block，支持continue语句：继续新循环                                                                             |
| 2022-05-26 | v0.1.11 | 控制流：对 for do-for 语句block，支持break语句：跳出循环                                                                                  |
| 2022-05-25 | v0.1.10 | 运算符：对自增/自减运算符区分 前缀和后缀的区别。见 test case self-increase-001.ring                                                       |
| 2022-05-25 | v0.1.9  | 自动化测试：优化自动化测试                                                                                                                |
| 2022-05-24 | v0.1.8  | 函数：支持 定义局部变量和使用全局变量，变量作用域的隐藏与可见。                                                                           |
| 2022-05-20 | v0.1.7  | 函数：支持 用户自定义 derive函数                                                                                                          |
| 2022-05-18 | v0.1.6  | 自动化测试：支持自动化测试                                                                                                                |
| 2022-05-18 | v0.1.5  | 变量：支持string变量：拼接、比较、判断。                                                                                                  |
| 2022-05-16 | v0.1.4  | 虚拟机：v0.0.35的功能基本通过虚拟机可以实现，但是某些细节需要继续优化;                                                                    |
| 2022-05-16 | v0.1.3  | 虚拟机：添加native函数 println_bool println_int println_double println_string exit;                                                       |
| 2022-04-21 | v0.1.2  | 虚拟机：可以执行native函数print、println，暂时只支持打印int常量;                                                                          |
| 2022-03-10 | v0.1.1  | 虚拟机：可以简单翻译全局变量的赋值运算;                                                                                                   |
| 2022-03-09 | v0.1.0  | 虚拟机：把AST翻译成栈虚拟机IR代码，已经可以翻译四则运算                                                                                   |
| ---------- | ------- | ---------------------------                                                                                                               |
| 2022-03-04 | v0.0.35 | 运算：添加 ++、-- 区分 i++ ++i i-- --i;                                                                                                   |
| 2022-03-02 | v0.0.34 | 运算：完善基本运算 加减乘除模：+ - * / % ；添加+=、-=、*=、/=、%=;                                                                        |
| 2022-03-01 | v0.0.33 | 控制语句：支持 三目运算符 a ? b : c;                                                                                                      |
| 2022-02-28 | v0.0.32 | 数据类型-数组：支持int数组，但是必须在定义的时候设置大小，暂不能自动扩展、暂时不能支持赋值。                                              |
| 2022-02-18 | v0.0.31 | 控制语句：支持 do while 语句                                                                                                              |
| 2022-02-16 | v0.0.30 | 数据类型：支持 变量定义时即可赋值，同时支持const int a，TODO:需要添加在语义分析中                                                         |
| 2022-02-16 | v0.0.29 | 数据类型：bool、int、double 变量在定义时如果未初始化，应该以默认值初始化                                                                  |
| 2022-02-15 | v0.0.28 | 函数：函数返回值return语句支持多个返回值，但是 variable 测试用例有随机性bug                                                               |
| 2022-02-15 | v0.0.27 | 表达式：变量支持并行赋值，如 a,b=1231,1.1;                                                                                                |
| 2022-02-15 | v0.0.26 | 控制语句：支持 break contitnue语句                                                                                                        |
| 2022-02-11 | v0.0.25 | 函数：更改函数的定义方式。                                                                                                                |
| 2022-02-11 | v0.0.24 | 优化交互式编程。                                                                                                                          |
| 2022-02-09 | v0.0.23 | 控制语句：支持 if elseif else 语句                                                                                                        |
| 2022-02-09 | v0.0.22 | 不支持隐式类型转换，编程需要 bool、int、double 的强制类型转换, 有点bug                                                                    |
| 2022-02-09 | v0.0.21 | 支持交互式编程 类似 ipython，但是bug有点多                                                                                                |
| 2022-02-08 | v0.0.20 | 定义 int double bool 支持变量初始化                                                                                                       |
| 2022-02-08 | v0.0.19 | 控制语句：优化 for语句 ，init condition post 均支持空                                                                                     |
| 2022-02-08 | v0.0.18 | 控制语句：支持 for语句 ，但是不支持 break 和 continue语句                                                                                 |
| 2022-02-08 | v0.0.17 | 控制语句：优化 if else 语句                                                                                                               |
| 2022-02-08 | v0.0.16 | 控制语句：支持 if else语句                                                                                                                |
| 2022-02-08 | v0.0.15 | 表达式：支持一元运算操作 负号（-）                                                                                                        |
| 2022-02-08 | v0.0.14 | 表达式：支持一元运算操作 逻辑非（not）                                                                                                    |
| 2022-02-07 | v0.0.13 | 表达式：支持二元逻辑运算操作 and、or                                                                                                      |
| 2022-02-07 | v0.0.12 | 表达式：支持二元关系运算符 > >= < <= == !=                                                                                                |
| 2022-02-07 | v0.0.11 | print 支持多个不同类型的参数，如：print(a," ", b," ", c,"\n");                                                                            |
| 2022-02-07 | v0.0.10 | 变量：支持bool型变量 赋值、打印，true、false                                                                                              |
| 2022-02-05 | v0.0.9  | 函数：支持函数返回值 return语句                                                                                                           |
| 2022-02-04 | v0.0.8  | 函数：函数调用支持传递变量                                                                                                                |
| 2022-02-04 | v0.0.7  | 函数：自定义函数在使用变量时 需要区分作用域                                                                                               |
| 2022-01-28 | v0.0.6  | 运算符：修复算术运算的bug（支持传递变量标识符）                                                                                           |
| 2022-01-28 | v0.0.5  | 支持自定义函数,无参数、无返回值(但是函数的递归调用存在bug)。编译错误时，打印当前行的内容、并提示错误编译的信息。                          |
| 2022-01-26 | v0.0.4  | int/double/string 变量的赋值操作，int/double 四则运算，支持打印 int/double/string 变量/常量 ，添加自动化测试脚本                          |
| 2022-01-25 | v0.0.3  | 支持解析 + - * / 运算法表达式，和 int string 变量的赋值操作，支持打印 int变量、string变量、string常量，DEBUG日志支持颜色分类              |
| 2022-01-20 | v0.0.2  | 支持解析 string变量定义，string变量赋值，print打印string常量                                                                              |
| 2022-01-19 | v0.0.1  | 支持解析print函数、但是还没有调用成功                                                                                                     |
| 2022-01-18 | v0.0.0  | 支持解析 注释 string变量定义和复制                                                                                                        |
