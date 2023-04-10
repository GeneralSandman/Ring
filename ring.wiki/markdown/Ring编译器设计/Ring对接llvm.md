# llvm 学习笔记

简称 low level virtual machine

是模块化的编译器组件、工具链, 用来开发编译器的前段和后端

1. llvm 的基本设计原理

    LLVM提供了一套适合编译器系统的中间语言（Intermediate Representation，IR），有大量变换和优化都围绕其实现。

    经过变换和优化后的中间语言，可以转换为目标平台相关的汇编语言代码。

    LLVM可以和GCC工具链一起工作，允许它与为该项目编写的大量现有编译器一起使用。

    LLVM还可以在编译、链接时生成可重新定位的程式码（Relocatable Code），甚至在运行时生成二进制机器码。




2. 中间表示

LLVM的中间语言与具体的语言、指令集、类型系统无关，其中每条指令都是静态单赋值形式（SSA）， 
即每个变量只能被赋值一次。
这有助于简化变量之间的依赖分析。
LLVM允许静态编译代码，或者通过实时编译（JIT）机制将中间表示转换为机器码（类似Java）。


TIP: 什么是静态单赋值形式（SSA）
```
每个变量仅被赋值一次, 
```






## 2023-03-08 

钻研 指令选择 instructions selection.

https://www.geeksforgeeks.org/peephole-optimization-in-compiler-design/

Peephole optimization is a type of code Optimization performed on a small part of the code. It is performed on a very small set of instructions in a segment of code.


a. Redunant load and store elimination
b. Constant folding
c. strength reduction
d. useless operations delete.
e. combine operations


现代编译器 通常使用 模式匹配 来实现 窥孔优化. 

Peephole optimization
https://en.wikipedia.org/wiki/Peephole_optimization

Pattern Matching
https://en.wikipedia.org/wiki/Pattern_matching


## 2023-03-10

### llvm 的一些工具

1. opt 对IR级程序进行优化的工具
  - 输入: llvm位码
  - 输出: llvm位码
2. llc 通过特定后端将llvm位码转换成目标机器汇编语言文件或目标文件 的工具
  - 可以通过传递参数选择优化的等级, 调试选项, 特定目标的优化
3. llvm-mc 能够汇编指令并产生诸如ELF、MachO、PE 格式的目标文件.
  - 也可以反汇编相同的对象 从而存储指令的相应的汇编信息和内部LLVM机器指令数据结构
4. lli   llvm IP的解释器 和 JIT 编译器
5. llvm-link  将llvm位码链接在一起, 产生包含所有输入的llvm位码
6. llvm-as  将人工刻度的llvm IR 转换成 llvm位码
7. llvm-ds 将llvm位码解码成llvm汇编码


```
有源文件  main.c  sum.c
.bc 标识llvm位码文件扩展名
.ll 标识人工可读的llvm汇编码文件扩展名

一步到位  clang main.c sum.c -o sum


-emit-llvm -c 共同使用, 生成一个llvm位码格式的文件
clang -emit-llvm -c main.c -o main.bc
clang -emit-llvm -c sum.c -o sum.bc

-emit-llvm -S 共同使用, 生成人工可读的llvm汇编码文件
clang -emit-llvm -S main.c -o main.ll
clang -emit-llvm -S sum.c -o sum.ll


nm 可以查看 .o 目标文件
nm -n -C sum.o  

```

gcc/g++ 实战之编译的四个过程
https://www.cnblogs.com/zjiaxing/p/5557549.html

Linux nm 工具查看 目标文件内容
https://www.cnblogs.com/downey-blog/p/9583765.html


llvm手册
https://www.llvm.org/docs/LangRef.html

llvm官方mini项目
https://www.llvm.org/docs/tutorial/index.html


## 某位大佬利用 llvm 实现的 一个编译器

该项目已经可以实现前端的大部分功能了，已经生成AST了
https://github.com/rui314/chibicc

8cc 是 chibicc的原始版本, is a compiler for the C programming language.
https://github.com/rui314/8cc

llfs 利用 chibicc的AST  和 llvm 去生成字节码
https://github.com/bigconvience/llfs
