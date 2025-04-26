# Ring 参考资料




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


### Lua闭包

1. 《构建Lua解释器Part11：Upvalue》 
https://manistein.github.io/blog/post/program/let-us-build-a-lua-interpreter/%E6%9E%84%E5%BB%BAlua%E8%A7%A3%E9%87%8A%E5%99%A8part11/


2. 《用Rust实现Lua解释器 Upvalue的逃逸和闭包》
https://wubingzheng.github.io/build-lua-in-rust/zh/ch09-02.escape_and_closure.html


3. 《lua深入理解闭包》https://juejin.cn/post/7121555416420450317

#### 书籍
1. 《Lua设计与实现》https://github.com/lichuang/Lua-Source-Internal
2. 《自己动手实现Lua：虚拟机、编译器和标准库》
3. lua 中 lua_State 和 global_State 含义 

https://chenanbao.github.io/2018/07/27/Lua%E8%99%9A%E6%8B%9F%E6%9C%BA%E5%88%9B%E5%BB%BA%E5%88%86%E6%9E%90/


4. 实现自己的编程语言 
   https://github.com/codecrafters-io/build-your-own-x#build-your-own-programming-language


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
不太认可这样的办法, 借用了Golang的特性, 简化了虚拟机的实现方式。

基于 Lua 5.4.4


#### 1. 第二章 ———— 二进制chunk格式详解

了解Lua 5.4.4 版本的 bytecode的基本格式, 知道是如何解析的, 并且实现了解析 Lua Bytecode.
header: 校验码, 如何加载
body: proto 的基本格式


#### 2. 第三章 ———— 指令集

介绍Lua虚拟机指令集和指令编码格式, 对指令进行解码.



#### 3. 第四章 至 第六章

主要介绍如何要实现一个stack-based virtual machine, 可以解释执行大概一半的Lua虚拟机指令.

但是自己在 Ring 已经实现了 stack-based virtual machine, 其实这三章可以暂时略过.


#### 4. 第七章 至 第十二章

介绍 表, 函数调用, Closure&Upvalue, 元编程, 迭代器, 异常和错误处理



## QuickJS


1. QuickJS

官方
https://bellard.org/quickjs/

中文
https://github.com/quickjs-zh/QuickJS

推荐:
https://github.com/quickjs-ng/quickjs
Forked: https://github.com/GeneralSandman/quickjs


2. quickjs介绍

https://www.cnblogs.com/lsgxeva/p/17226032.html


3. QuciJS 需要参考的地方


quickjs 协程和golang协程 https://poe.com/s/tgHGQK5BaQYvVlmW67X9


## 如何编写一个vscode插件


从零开始为你的自制编程语言写一个专属VSCode插件
https://zhuanlan.zhihu.com/p/164736736


golang tmLanguage json
https://github.com/microsoft/vscode/blob/main/extensions/go/syntaxes/go.tmLanguage.json
https://github.com/worlpaker/go-syntax/blob/master/syntaxes/go.tmLanguage.json




## 垃圾回收专题

《Go 语言设计与实现 —— 7.2 垃圾收集器》
https://draveness.me/golang/docs/part3-runtime/ch07-memory/golang-garbage-collector/

《图示Golang垃圾回收机制》
https://zhuanlan.zhihu.com/p/297177002

简单实现  Mark-Sweep垃圾回收机制 
https://journal.stuffwithstuff.com/2013/12/08/babys-first-garbage-collector/



《构建Lua解释器Part2：Garbage Collection基础架构》 Incremental Mark and Sweep算法
https://manistein.github.io/blog/post/program/let-us-build-a-lua-interpreter/%E6%9E%84%E5%BB%BAlua%E8%A7%A3%E9%87%8A%E5%99%A8part2/