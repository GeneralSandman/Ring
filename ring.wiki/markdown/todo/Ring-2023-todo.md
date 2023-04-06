# Ring 2023年 Todo List


2022年下半年因为面试的原因，没有尽力去全力以赴的完善Ring，在此定义一个2023年的todo list。
更新时间：2023-04-03

[TOC]

## 总规划

1. 通读 diksam_v0.4 https://github.com/GeneralSandman/diksam_v0.4
2. 使用 栈式虚拟机完善 全部功能
   1. 面向对象
   2. 闭包
   3. 生成字节码 到二进制文件 解析字节码
   4. 原文件可以分成包的形式
   5. 数组
   6. 优化字符串
   7. 优化内置 native函数
   8. 完善内置 printf 函数  很重要
3. 完善语义分析 报错机制
4. 通读 Lua 5.x版本
   1. 力求完全掌握设计逻辑、包括协程、table
   2. 重新读那本 用Go语言实现Lua虚拟机
5. 将 栈式虚拟机 转为 寄存式虚拟机

-----------------------------

## 1. 2023-04-03～2023-04-07 周规划

实现面向对象
- 暂时只设计 成员变量的场景  成员方法放在下一期
- 面向对象的语法设计
- diksam 面向对象的语法设计
- 虚拟机支持 面向对象的 内存分配
- 面向对象的测试用例
