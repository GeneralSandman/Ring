# The Ring Programming Language


> [!TIP|label:Ring Official Website]
> 
> https://ring.wiki
> 
> 备用网站
> https://ring-1252697766.cos-website.ap-beijing.myqcloud.com
>
> 

> [!NOTE|label:Ring Code Exapmle]
> 
> https://example.ring.wiki
> 
> 备用网站
> https://example-ring-1252697766.cos-website.ap-beijing.myqcloud.com
>
> 


## 1. What is Ring Language

**Ring** 是由GeneralSandman与2021年开始设计实现的高级编程语言，目标：轻量级脚本编程语言、解决目前现有编程语言的痛点。


- 静态类型系统

- 支持**面向过程式**、**面向对象**

- 简洁、灵活的语法规范

- 源代码编译生成字节码由**Ring虚拟机**执行

- 较为丰富的标准库

- 可原生调用C语言

- 跨平台运行

- 基于**C++11**设计实现



## 2. Get Ring Features

- 基础数据类型: bool, int, double, string
- 派生数据类型: array, class
- 数学运算
- 基本控制语句: if, else, for, for-range, do-for, break, continue
- 全局变量, 局部变量
- package包命名机制
- 动态内存管理&垃圾回收机制

## 3. Ring Future Features

- ~~具有原生的项目构建和包依赖管理工具 ```hobbit```~~
- ~~并发编译~~
- ~~实现一系列标准库：IO、字符串、文件操作、数学计算、Socket、网络~~


## 4. Ring发展规划

### 数据类型

1. 基本数据类型: bool int int64 double string
2. 派生数据类型: array class
3. array: 多维数组
4. class: field(各种数据类型的嵌套组合, 循环定义), method
5. tuple 元组
6. 枚举类型
7. 用法: 可见范围(全局变量、局部变量)、定义、初始化、赋值、copy、函数传递、gc、heap_size计算、类型转化、(是否要支持auto推断类型)
8. Any类型
9. 类型的强制转换 与 隐式转换

### 运算符

1. 运算符: + - * / % += -= *= /= %= ++ -- 
2. 运算符: == != > < >= <=
3. 运算符: and or not
4. 运算符: a?b:c
5. 用法: 运算符的优先级、操作数的数据类型


### 控制语句

1. 语句: if else for do-for break continue return 
2. 语句: switch-case
3. 模式匹配 match


### function & method

1. 函数调用/方法调用
2. 参数、局部变量、返回值、self关键字
3. 可变参数+any类型
4. 参数的深度copy, 浅copy
5. 匿名函数
6. 闭包
7. 函数作为变量/参数
8. 类中的静态方法和非静态方法


### 语义分析

1. 完善语义分析 报错机制
2. 完善各种语法限制，争取在编译过程中就报错提示，尽量不允许在运行过程中崩溃


### GC

1. 实现了最简单的STW Mark&Sweep GC算法
2. 实现进阶版GC: 三色标记的 Incremental Mark and Sweep 算法


### 协程

### 项目组织

1. package 源代码的组织形式 import/package
2. 第三方package的安装和下载
3. 项目编译过程中并发编译
4. 支持一个package中有多个文件
5. 原生的项目构建和包依赖管理工具 hobbit

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


1. 更加优化的方式实现 native-lib, ring方便调用c库, 与c库进行交互
2. 实现相对完善的官方标准库 fmt sys math debug strings reflect
3. fmt: 完善内置 printf 函数, 支持可变参数, 参考format函数
4. reflect: 实现反射, 获取变量的类型


## 5. 不成熟的想法

1. 支持Ring Eval, e.g.  ./bin/ring eval "fmt::println_string("hello world")";  默认导入所有的std package, 不能指定全局变量, 直接就是main函数中代码
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



### A. 字符串的format

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


3. ring 如何实现

f" a {test}"

对应一个 string builder

会处理成 fmt::sprintf(" a {}", test)

### B. 分发方式

目前发展规划主要在 字节码虚拟机执行 OR 机器码二进制执行

关于直接虚拟机还是二进制, 各自的优劣这里不再赘述. 
在这里我整理一个我认为着重考虑的点:
1. 虚拟机形式 很难实现自举, 强如Java迄今为止也没能实现.
2. 虚拟机形式 执行速度太慢, 不然为什么会出现JIT

通过自己对于目前发展方向的判断, 我认为直接生成二进制才是未来的主流, 他有几个极大的优势, 这个优势是虚拟机形式不能解决的:
1. 直接生成二进制, 可到处分发, 目标机器无需安装任何依赖.
   - 为什么这一点很重要呢, 我在腾讯和字节跳动都做过后台开发的工作, 其内部的网络访问策略非常严格, 发现在部署阶段, 如果需要遇到通过网络安装依赖, 经常需要寻找各种方案, 所以自己非常痛恨这种部署方式
2. 后期编译器成熟之后可以实现自举
3. 没有跟虚拟机一样, 运行时过于繁重, 


发展方向讨论到现在已经有了比较大的倾向, 那么接下来有一个非常值得关注的问题:

### C. 关于 编译生成可执行二进制的工作量

1. 深入了解各个CPU架构的汇编指令: x86-64, arm, 


### D. ring build

构建一个很大的字节码文件，这样在目标机器上也不用安装依赖了。
