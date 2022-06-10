# Ring 2022 todo/bug list

2022-06-06
2022-06-08
2022-06-09

括号实现运算优先级

double常量/变量比较大小

强制类型转换

<int>1.12;
<double>1;
<bool>1;
<bool>0;

<string>123;
<string>1.23;



支持数组


int 应该 类似  c语言 longlong 
-9,223,372,036,854,775,807 - 1
9,223,372,036,854,775,807


优化虚拟机调试函数调用的功能。
step into
step over
step out

优化LineNumber 功能，类似于luac -l 查看字节码


语法错误提示

完成语义报错提示


字节码的生成与加载
 

可变参数 print println printf printfln

print 应该类似于  rust print 和c++ 20 format

print(1, 1.2, "afsdf");

println(1, 1.2, "asdfa");

printf("{} is {}", "zhenhuli", "male");

printfln("{} is {}", "zhenhuli", "male");
printfln("{0} {2} is {0} {3}", "zhenhuli", "male", "lise", "famale");

可变参数列表转化为数组






学习 lua-4.0.1


lua 函数 return的设计
https://blog.csdn.net/weixin_43652106/article/details/107684621




补足自动化测试


lua c函数 要编译成 so dll 放到对应的目录，这里应该抛弃这种用法，只需要下发 一个 ringc 即可。


lua 的 Instruction 是 unsinged long