# The ```Ring``` Programming Language



> [!TIP|style:flat|label:What is Ring]
> 
> 
> ```Ring```是基于C语言开发的一个轻量级的脚本编程语言，支持**面向过程式**、**面向对象**两种编程范式，语法设计参考自**C、C++、Java、Go、Lua、PHP、Python、Rust**等语言规范。
> 
> ```Ring```源代码编译生成字节码后由**栈式虚拟机**执行。
> 
> ```Ring```编译器采用模块式设计：实现方法简单、轻巧，易扩展。


## 快速了解```Ring```特性

- 语法类似```C、C++、Go``` 语言
- 支持**面向过程式**、**面向对象**两种编程范式
- 静态类型
- 源代码编译生成字节码后由**栈式虚拟机**执行
- ~~跨平台运行~~
- ~~具有原生的项目构建和包依赖管理工具 ```hobbit```~~
- ~~支持Debug调试~~
- ~~支持交互式编程~~
- ~~并发编译、速度快~~
- ~~高级特性：支持**函数闭包**、**匿名函数**、**函数变量**~~
- ~~标准库：打印输出、字符串、文件操作、数学计算~~


#### [```Ring```一些宏远的规划](./markdown/Ring编译器设计/Ring未来展望)


> [!TIP|style:callout|label:Ring官方网站]
> 
> https://ring.wiki
> 
> https://ring-1252697766.cos-website.ap-beijing.myqcloud.com
> 



<h2>基础语法功能表</h2>
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
  <td>❌</td>
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






## Get Started


```shell

git clone https://github.com/GeneralSandman/Ring

cd Ring



make && make clean

make testall

make install



ring version

ring run test/helloworld.ring

ring help

```







