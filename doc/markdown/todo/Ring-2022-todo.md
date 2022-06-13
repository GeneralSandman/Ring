# Ring 2022 todo/bug list


## 括号实现运算优先级

double常量/变量比较大小

## 强制类型转换

<int>1.12;
<double>1;
<bool>1;
<bool>0;

<string>123; fmt.sprintf("{}", 123);
<string>1.23;



int 应该 类似  c语言 longlong 
-9,223,372,036,854,775,807 - 1
9,223,372,036,854,775,807


优化虚拟机调试函数调用的功能。
step into
step over
step out

优化LineNumber 功能，类似于luac -l 查看字节码



## 完成语义报错提示

语法错误提示


## 字节码的生成与加载


 




# typedef

typedef class Student {

};


typedef int BillType; // BillType 必须大写
typedef string BillKind; // BillKind 必须大写

var int int_value;

var BillType bill_type;
var BillKind bill_kind;

var Student zhenhuli;



const BillKind cos = "from cos";
const BillKind iss = "from iss";


enum {
    BillKind cos = "from cos";
};


## package 

package main


## import

package main

import {
    io;
    time -> tm;
    os -> oss;
}

function main() -> (int) {
    return 0;
}



## 系统printf

关于如何实现 四个主要的 输出函数：print println printf printfln

function typeof(var auto arg) -> (int);

function print(var auto... value) -> (int);
function println(var auto... value) -> (int);
function printf(var string format, var auto... value) -> (int);
function printfln(var string format, var auto... value) -> (int);


print(1, 1.2, "afsdf");
println(1, 1.2, "asdfa");
printf("{} is {}", "zhenhuli", 123);
printfln("{} is {}", "zhenhuli", 123);


可变参数列表转化为数组

1. 要实现 类型 auto，类似于go的interface，可以将任何变量转换为auto
2. 实现反射，在函数内部能够获取 变量的类型，实现不同的打印函数。
3. 还要实现可变参，能够类似于go和c 如何获取可变参数。
4. 还要实现枚举，枚举 bool int double string auto 用于判断类型。

go 的反射实现 https://draveness.me/golang/docs/part2-foundation/ch04-basic/golang-reflect/
http://c.biancheng.net/view/4407.html







## 编程语言如何设计调试器、dap协议




## 库的依赖


首先遍历所有的文件，生成依赖，写入文件中，为后续依赖提供依据。



## 如何实现数组


## 如何实现对double数量的比较


## 三目运算符


condition_expression ? true_expression : false_expression;

if(condition_expression) {
    true_expression;
} else {
    false_expression;
}



不能是赋值表达式，因为赋值表达式是没有运算返回值的，且运用它们会是代码逻辑变得复杂，因此 三目运算有如下限制：
condition_expression、true_expression、false_expression 只能是 变量标识符、逻辑运算、关系运算、算术运算、位移运算；


如： a ? a=1 : a=2; // 非法


if、else中代码块是statement，是没有返回值的，而三目运算是有返回值的。


如

var string result;

result = int_value1==int_value2 ? "match" : "dismatch";

if(int_value1==int_value2){
    result = "match";
} else {
    result = "dismatch";
}



## 位移运算

<html>
    <table border="0">
        <tr>
            <td>
                ```
                var string result;

result = int_value1==int_value2 ? "match" : "dismatch";

if(int_value1==int_value2){
    result = "match";
} else {
    result = "dismatch";
}
                ```
            </td>
            <td>
                <!--右侧内容-->
                右侧
            </td>
        </tr>
    </table>
</html>


## switch case







学习 lua-4.0.1


lua 函数 return的设计
https://blog.csdn.net/weixin_43652106/article/details/107684621




补足自动化测试


lua c函数 要编译成 so dll 放到对应的目录，这里应该抛弃这种用法，只需要下发 一个 ringc 即可。


lua 的 Instruction 是 unsinged long



bison 第三章 显式指定优先级，消除Ring所有的shift/reduce 错误


## 吉祥物 owl 猫头鹰