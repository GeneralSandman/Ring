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


## 4. Get Ring Basic Ability

<table>
<tr>
  <th>类别</th>
  <th>细节</th>
  <th>进度</th>
  <th>BugList</th>
</tr>

<tr>
  <td rowspan="4">基本数据类型</td>
  <td>bool</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>int</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>double</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>string</td>
  <td>✅</td>
  <td></td>
</tr>


<tr>
  <td rowspan="7">变量</td>
  <td>定义</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>初始化</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>赋值、多重赋值</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>区分全局变量、局部变量</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>区分作用域、变量的可见性</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>类型转换</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>类型推导：auto like 语句</td>
  <td>❌</td>
  <td></td>
</tr>


<tr>
  <td rowspan="9">运算操作</td>
  <td>赋值运算、多重赋值运算</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>算术运算：+ - * / %</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>算术运算且赋值运算：+= -= *= /= %= </td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>前缀/后缀 自增/自减运算：++ --</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>关系运算：==、!=、>=、>、<=、<、</td>
  <td>✅</td>
  <td>对于 double 类型，还有bug，见print_heart.</td>
</tr>
<tr>
  <td>逻辑运算：and or not</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>位运算</td>
  <td>❌</td>
  <td></td>
</tr>
<tr>
  <td>三目条件运算 a?b:c; </td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>运算优先级 </td>
  <td>✅</td>
  <td>need more test</td>
</tr>



<tr>
  <td rowspan="3">控制语句</td>
  <td>if-else-elseif 判断语句</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>for 循环语句：支持 break、continue</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>do-for 循环语句：支持 break、continue</td>
  <td>✅</td>
  <td></td>
</tr>


<tr>
  <td rowspan="5">函数</td>
  <td>函数定义</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>类函数声明</td>
  <td>❌</td>
  <td></td>
</tr>
<tr>
  <td>return 多个返回值</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>全局变量的访问</td>
  <td>✅</td>
  <td></td>
</tr>
<tr>
  <td>局部变量的定义与访问</td>
  <td>✅</td>
  <td>some bug</td>
</tr>


</table>

