# Ring 2022 todo/bug list


抛弃 const
应该跟 scala 一样

var int a;
val int b;


吸收 scala 的字符串 format

println(s"format1 $a")   a是变量

## how to implement a register-based virtual machine inside stack-based virtual machine.

通读买的Lua数据，首先要写一个程序，能够去解析 lua 的字节码。

然后去设计 instructions 

能够全部cover所有的 stack-based 功能。


再去实现闭包等高级操作


## 不单独支持数组

采用类的方式
array 为类似于c++的vector
所以还要支持范型

不需要导入包，作为默认的关键字


var array<int> jobs;
jobs.resize(10);
jobs.size();
jobs[1] = 1;
jobs[-1] = 2;
// 需要判断index合法性




## 支持类 和 对象

typedef int int32;

typedef class Student {
	var int age;
	var string name;

	function print_info();
	function set_age(var int _age);
	function set_name(var string _name);
};

function Student::print_info() {
	println(age, name);
}

function Student::set_age(var int _age) {
	age = _age;
}

function Student::set_name(var string _name) {
	name = _name;
}



var Student zhenhuli;
zhenhuli.set_age(25);
zhenhuli.set_name("zhenhuli");

zhenhuli.print_info();

## 实现函数变量


## 实现闭包



## runtime stack 空间自动扩展，不指定 1024*1024


## 优化函数 局部变量数量 和 函数参数数量 的问题


## auto 类型推导


function lambda = (var any a, var any b) -> (any) {

}

lambda(1, "1231");


var int int_value;


var any result = 123;

var any result like int_value;

var any result like int_value + double_value;

var any result = int_value;


function(var any a, var any b) -> (any) {

}


## 不支持函数重载


## derive function 不支持可变参数、native function 支持可变参数


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


 




## typedef

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


使用导入包的 类型定义、函数、变量


io.print("hello world");


var time:Time time;


time.GlobalValue = 1234;
time.GetTim();

## 符号 应用于 double的错误

+=
-=
*=
/=
%=
多重赋值


多重赋值 不能   a, b += 1, 2; // invalid

## bug 整数常量给 double 变量赋值。

var double double_value;

double_value = 123; //FIXME:BUG 需要语义检查


## 编程语言如何设计调试器、dap协议




## 库的依赖


首先遍历所有的文件，生成依赖，写入文件中，为后续依赖提供依据。



## 如何实现数组


## 如何实现对double数量的比较



## 位移运算


## switch case


## 拆分ring源代码文件

## 设计 class

## 设计 异常与捕获


## 消除Ring所有的shift/reduce 错误 2022-06-10:done


## 吉祥物 owl 猫头鹰




## bug , 在ring代码中没有声明native函数，但是注册了，会报错，需要修复 

只有在定义 derive的代码中才会出现。


## 三目运算符 2022-06-14:done


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




## 命令行 2022-06-14:done

ring run helloworld.ring
ring run helloworld.ringc

ring build helloworld.ring

ring dump helloworld.ringc


## 相对方便的 print println printf printfln  2022-06-15:done

目前的 println_bool println_int println_double println_string 有点复杂，为了方便使用，
新添加四个主要的 输出函数：print println printf printfln（类似于go语言）

可变参数列表转化为数组

1. 要实现 类型 auto，类似于go的interface，可以将任何变量转换为auto
2. 实现反射，在函数内部能够获取 变量的类型，实现不同的打印函数。
3. 还要实现可变参，能够类似于go和c 如何获取可变参数。
4. 还要实现枚举，枚举 bool int double string auto 用于判断类型。

go 的反射实现 https://draveness.me/golang/docs/part2-foundation/ch04-basic/golang-reflect/
http://c.biancheng.net/view/4407.html

```ring

function print(var auto... value) -> (int);
function println(var auto... value) -> (int);
function printf(var string format, var auto... value) -> (int);
function printfln(var string format, var auto... value) -> (int);


print(1, 1.2, "afsdf");
println(1, 1.2, "asdfa");
printf("{} is {}", "zhenhuli", 123);
printfln("{} is {}", "zhenhuli", 123);

```

go 是如何时间格式化控制输出

```go

func (p *pp) doPrintf(format string, a []any) {
	end := len(format)
	argNum := 0         // we process one argument per non-trivial format
	afterIndex := false // previous item in format was an index like [3].
	p.reordered = false
formatLoop:
	for i := 0; i < end; {
		p.goodArgNum = true
		lasti := i
		for i < end && format[i] != '%' {
			i++
		}
		if i > lasti {
			p.buf.writeString(format[lasti:i])
		}
		if i >= end {
			// done processing format string
			break
		}

		// Process one verb
		i++

		// Do we have flags?
		p.fmt.clearflags()
	simpleFormat:
		for ; i < end; i++ {
			c := format[i]
			switch c {
			case '#':
				p.fmt.sharp = true
			case '0':
				p.fmt.zero = !p.fmt.minus // Only allow zero padding to the left.
			case '+':
				p.fmt.plus = true
			case '-':
				p.fmt.minus = true
				p.fmt.zero = false // Do not pad with zeros to the right.
			case ' ':
				p.fmt.space = true
			default:
				// Fast path for common case of ascii lower case simple verbs
				// without precision or width or argument indices.
				if 'a' <= c && c <= 'z' && argNum < len(a) {
					if c == 'v' {
						// Go syntax
						p.fmt.sharpV = p.fmt.sharp
						p.fmt.sharp = false
						// Struct-field syntax
						p.fmt.plusV = p.fmt.plus
						p.fmt.plus = false
					}
					p.printArg(a[argNum], rune(c))
					argNum++
					i++
					continue formatLoop
				}
				// Format is more complex than simple flags and a verb or is malformed.
				break simpleFormat
			}
		}

		// Do we have an explicit argument index?
		argNum, i, afterIndex = p.argNumber(argNum, format, i, len(a))

		// Do we have width?
		if i < end && format[i] == '*' {
			i++
			p.fmt.wid, p.fmt.widPresent, argNum = intFromArg(a, argNum)

			if !p.fmt.widPresent {
				p.buf.writeString(badWidthString)
			}

			// We have a negative width, so take its value and ensure
			// that the minus flag is set
			if p.fmt.wid < 0 {
				p.fmt.wid = -p.fmt.wid
				p.fmt.minus = true
				p.fmt.zero = false // Do not pad with zeros to the right.
			}
			afterIndex = false
		} else {
			p.fmt.wid, p.fmt.widPresent, i = parsenum(format, i, end)
			if afterIndex && p.fmt.widPresent { // "%[3]2d"
				p.goodArgNum = false
			}
		}

		// Do we have precision?
		if i+1 < end && format[i] == '.' {
			i++
			if afterIndex { // "%[3].2d"
				p.goodArgNum = false
			}
			argNum, i, afterIndex = p.argNumber(argNum, format, i, len(a))
			if i < end && format[i] == '*' {
				i++
				p.fmt.prec, p.fmt.precPresent, argNum = intFromArg(a, argNum)
				// Negative precision arguments don't make sense
				if p.fmt.prec < 0 {
					p.fmt.prec = 0
					p.fmt.precPresent = false
				}
				if !p.fmt.precPresent {
					p.buf.writeString(badPrecString)
				}
				afterIndex = false
			} else {
				p.fmt.prec, p.fmt.precPresent, i = parsenum(format, i, end)
				if !p.fmt.precPresent {
					p.fmt.prec = 0
					p.fmt.precPresent = true
				}
			}
		}

		if !afterIndex {
			argNum, i, afterIndex = p.argNumber(argNum, format, i, len(a))
		}

		if i >= end {
			p.buf.writeString(noVerbString)
			break
		}

		verb, size := rune(format[i]), 1
		if verb >= utf8.RuneSelf {
			verb, size = utf8.DecodeRuneInString(format[i:])
		}
		i += size

		switch {
		case verb == '%': // Percent does not absorb operands and ignores f.wid and f.prec.
			p.buf.writeByte('%')
		case !p.goodArgNum:
			p.badArgNum(verb)
		case argNum >= len(a): // No argument left over to print for the current verb.
			p.missingArg(verb)
		case verb == 'v':
			// Go syntax
			p.fmt.sharpV = p.fmt.sharp
			p.fmt.sharp = false
			// Struct-field syntax
			p.fmt.plusV = p.fmt.plus
			p.fmt.plus = false
			fallthrough
		default:
			p.printArg(a[argNum], verb)
			argNum++
		}
	}

	// Check for extra arguments unless the call accessed the arguments
	// out of order, in which case it's too expensive to detect if they've all
	// been used and arguably OK if they're not.
	if !p.reordered && argNum < len(a) {
		p.fmt.clearflags()
		p.buf.writeString(extraString)
		for i, arg := range a[argNum:] {
			if i > 0 {
				p.buf.writeString(commaSpaceString)
			}
			if arg == nil {
				p.buf.writeString(nilAngleString)
			} else {
				p.buf.writeString(reflect.TypeOf(arg).String())
				p.buf.writeByte('=')
				p.printArg(arg, 'v')
			}
		}
		p.buf.writeByte(')')
	}
}
```





























