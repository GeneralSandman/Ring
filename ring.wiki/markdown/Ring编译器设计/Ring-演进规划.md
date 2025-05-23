# Ring 演进规划


> [!TIP|label:tip]
>
> 致开发者：
>
> 不要觉得自己做的编译器没有气候，编译器是工业软件，需耐住寂寞，长时间积累。
> 


## Ring编译器开发内容流程细分

工作细化Tag：

- Background: 调研相关工作
- Proposal: 提案相关工作
- Feature:  新特性
- Fix:  修正
- Update: 逻辑更新
- Refactor: 重构
- Optimize: 优化
- Test: 测试
- Doc: 文档
- Other: 其他



-----------------------------



## 关于测试

### 测试集  ring run

```
2024-12-27


[TestInfo]:
TEST_LOOP_NUM     = 1
TEST_RING_BIN     = ./bin/ring
TEST_RING_OPTION  = -O1
TEST_RING_COMMAND = run
TEST_COMMAND      = ./bin/ring -O1 run
TEST_PATH         = ./test


[Result]:
Pass/All = 487/487
NotTest  = 5
Fail     = 0
Usetime  = 23S     

```




### 测试集 ring dump ✅

```
2024-05-30

[Result]:
Pass/All = 23/23
NotTest  = 0
Fail     = 0
Usetime  = 1S
```


### 要完善的测试用例

1. 函数参数的传递    (Path: ./test/004-derive-function/pass-argument/*)
   1. 参数的类型是基础类型  bool/int/int64/double/string
   2. 参数的类型是类       class
   3. 参数的类型是数组     bool[]/int[]/int64[]/double[]/string[]
   4. 参数的类型是类数组   class[]
   5. 多维数组（基础类型+类）
2. 函数返回          (Path: ./test/004-derive-function/return-value/*)
   1. 返回值的类型是基础类型 bool/int/int64/double/string
   2. 返回值的类型是类      class
   3. 返回值的类型是数组    bool[]/int[]/int64[]/double[]/string[]
   4. 返回值的类型是数组    class[]
   5. 多维数组（基础类型+类）
3. 全局变量
   1. 变量的定义+初始化 (Path: ./test/011-global-variable/def-and-init-*)
   2. 全局变量的类型是基础类型 bool/int/int64/double/string
   3. 全局变量的类型是类      class
   4. 支持多个变量在一行内定义+初始化
   5. 多维数组（基础类型+类） (Path: ./test/011-global-variable/def-and-init-array-*) ✅
4. 局部变量
   1. 变量的定义+初始化 (Path: ./test/012-local-variable/def-and-init-*)
   2. 全局变量的类型是基础类型 bool/int/int64/double/string
   3. 全局变量的类型是类      class
   4. 支持多个变量在一行内定义+初始化
   5. 多维数组（基础类型+类）  (Path: ./test/012-local-variable/def-and-init-array-*) ✅
5. 数组的 new
   1. 数组常量 作为函数参数
   2. 数组常量 作为函数返回值
   3. 数组常量 赋值给 全局变量
   4. 数组常量 赋值给 局部变量
   5. 需要覆盖基础类型： bool[]/int[]/int64[]/double[]/string[]
   6. 需要覆盖类：      class[]
   7. 多维数组（基础类型+类）





-----------------------------


## 开发专项

### 开发专项-语义报错

第一轮分析主要构建语法树
第二轮分析主要对相关的标识符号进行解析
第三轮主要进行进一步分析
第四轮主要进行 ast的剪枝优化
第五轮主要进行代码的生成

1. 局部变量名称重复 ✅
   1. block中定义的 局部变量重复(函数没有参数)  ✅
   2. block中定义的 局部变量和 函数参数中的变量 名称重复  ✅
   3. 函数参数中的变量 他们之间重复  ✅

2. 函数名重复 ✅
   1. 一个package中函数名称重复  ✅
   
3. 全局变量重复 ✅
   1. 全局变量 在 一个package中重复  ✅

4. function/method 返回值  ✅
   1. 返回值数量不对  ✅
   2. 返回值类型不对   ✅
   3. 调用函数 接受返回值的数量不对  ✅
   4. 调用函数 接受返回值的类型不对  ✅

5. 函数调用 进行参数校验
   1. build func
   2. std lib func
   3. derive func ✅
   4. method  ✅
   5. 匿名函数  ✅
   6. 函数变量  ✅
6. launch 调用 进行参数校验
   1. build func
   2. std lib func
   3. derive func ✅
   4. method  ✅
   5. 匿名函数  ✅
   6. 函数变量  ✅

7. class field/method
   1. field 重复  ✅
   2. method 重复  ✅
   3. field method 不能重复, 得是唯一id  ✅
   4. field 只能是 bool int double string 


6. import std package
   1. 没有找到标准包
   2. import重复

7. 变量
   1. 全局变量的数量
   2. 局部变量的数量
8. 函数定义
   1. 返回值的数量不能超过 255
9. package
   1.  一个package中的数量不能超过 255



10. 函数定义有返回值，但是没有返回的话，会直接core dump

```
fn test() -> (bool, int) {
}

a, b = test();
```





### 开发专项-类

1. field类型
   1. bool ✅ 
   2. int ✅ 
   3. double ✅ 
   4. string ✅ 
   5. class (class的嵌套定义与引用)




### 开发专项-数组

1. 数组 new 支持动态，e.g.  `array = new int[a,b,c];`

bool  ✅ 
int  ✅ 
double  ✅ 
string  ✅ 
class-object  ✅ 

2. 多维数组的语法糖 var int[!8]; 表示八维数组 ✅ 
   1. 创建多维数组的时候，不允许 !8
   2. !8 这个位置只能是个int常量，不能是变量


3. jobs[0].Running = false;  ✅ 
   这里有一个隐喻，就是jobs[0] 取出来应该得是个指针，
   不能是深度copy
   不然继续访问 jobs[0].Running 还是老的Value。




### 开发专项-关于编译速度

 348444 行代码的ring, 都放在一个main函数中, 编译+运行 总共耗时 2346.94s.  但是编译没有报错.




### 开发专项-丰富标准库


-----------------------------


## 2025-01-06周


### A. Proposal: 设计并实现增量式垃圾回收机制


-----------------------------


## 2024下半年发展大规划

完善Ring的基本功能, 争取在2024-12-31之前发布第一个release版本.


1. 匿名函数 ✅
2. 闭包 ✅
3. 协程 ✅
4. 增量式垃圾回收机制
5. 规范限定符号
6. 完善标准库 ✅


-----------------------------

## 2024-11月/12月 周

不进行新功能的开发，聚焦于：
1. 现有功能的完善，包括各种高级功能的相互叠加
2. 系统性测试，单简单测试用例，复杂测试用例
3. 扫清自v0.2.0版本以来的所有TODO项
4. 完善一下打包、安装 ring的自动化脚本
   1. 打包目标二进制
   2. 安装ring二进制
   3. 和make install的冲突，这里如何处理
5. 有可能的话，尽量完善一下相关文档

对与多维数据的语义检查要尽可能的详细


### 完善 打包二进制、安装 ring的自动化脚本

1. 打包目标二进制

通过 github action 来打包二进制，需要对以下环境进行支持
- macos
- linux


brew install act
act -W .github/workflows/build.yml

os: [ubuntu-latest, macOS-latest, windows-latest]


2. 获取 GitHub 个人访问令牌 (Personal Access Token)
登录到你的 GitHub 账户。
打开 Settings（设置）。
选择 Developer settings（开发者设置）。
点击 Personal access tokens（个人访问令牌）。
生成一个新令牌，确保勾选必要的权限（例如 repo 权限）。



act -W .github/workflows/build.yml -e .github/build.event.json

curl -H "Authorization: token xx" https://api.github.com/rate_limit


上传到一个 cos 的 bucket桶中，桶中的数据


### E. Fix: 这个会语法错误 ✅

```
return bool[]{};
```

### F. Optimize: debug::debug_assert() 改成 debug::assert()  ✅


### G. 关于匿名函数赋值进行强语义检查+typedef的强检查优化


1. typedef 定义函数变量类型别名的时候，需要简化  ✅

目前

```
typedef fn(var int a, var int b) -> (int) FuncType;
```

应该简化成更舒服的写法：

```
typedef fn(int, int) -> (int) FuncType;
```


2. 对于 匿名函数变量赋值，要细致的比对类型是否一致  ✅


e.g. 该测试用例不应该通过

```
typedef fn(bool, bool) -> (string) FuncType;

fn main() {
	var FuncType local_func_var;

	local_func_var = fn(var bool a, var int b) -> (string) {
		fmt::println("invoke a closure 1");
		return fmt::sprintf("ring {} {}", a, b);
	};
}
```

报错提示：

```
./test/040-closure/test-006-02.ring:24:2: 
|       };
|  ^......
|
|Err: assignment mismatch: expect (fn(bool,bool)->(string)) but provided (fn(bool,int)->(string)); E:200018.
|RingDebug: fix_ast.cpp:1013
```



### H. Proposal: 提供 strings::join 标准库


### I. Fix: 局部变量不进行初始化会 panic


```
fn join(var string[] a, var string sep) -> (string) {
	var string result;

	var int i = 0;

	for(i = 0; i < len(a); i++) {
		result = result .. a[i];
		if (i != len(a) - 1) {
			result = result .. sep;
		}
	}
	
	return result;
}
```


### J. Proposal: 关于整个工程的链接问题

1. 在多个package链接在一起的时候，bug：访问常量会直接访问到main-package的常量区，这里需要进行优化



### M. Fix: 编译报错，变量定义重复 ✅

```
fn (var int a) {
    var int a;
}
```


### N. Fix: 报错提示时，能够更精确的提示出 array的维度和元素的类型 ✅

```

fn test(var int[] array) {

}


test();

```

编译器报错：

```
./test/004-derive-function/return-value/int-multi-array-000.ring:14:0: 
|       fmt::println(return_1_int_array_1());
| ^......
|
|Err: function return_1_int_array_1() requires (array) arguments, but () was provided; E:300002
```


 
应该 `array` 的报错更加详细

改进之后：

```
./test/998-error-report/function-call-check-02.ring:28:0: 
|       test();
| ^......
|
|Err: function test() requires (int[!1]) arguments, but () was provided; E:300002
```


### Q. Optimize: 如何统一的进行 function-call method-call 的函数参数检查 ✅

将 函数/method/匿名函数变量，构建出一个TypeSpecifier, 通过比较 Func_TypeSpecifier 和 argument_list 是否可以统一判断

1. TypeSpecifier 中 ，能方式 variadic 么
2. 要深度比对，比如说某个函数的参数是个函数变量，需要继续深度比对



### H. Proposal:

对于 

a.func()

func 不一定是method，还又可能是 匿名函数field。

这里看看后续如何兼容


### U. Proposal: launch 入口函数为函数变量 ✅

需要支持 launch 函数变量

var FuncType func_var;

launch func_var();

### P. Proposal: ring 语法重构

1. 关键字 function -> fn  ✅
2. 关键字 method -> fn     ✅
3. 关键字 field -> var   ✅


### Y. Proposal: push pop 支持更多的类型

1. 支持多维数组
2. 支持多维类
3. 支持 匿名函数数组


### T. BUG: coredump

```
typedef class Job {
	var int a;
	var int b;
}

fn test3(var Job[] a) {

}
```


ring dump 会 coredump 



### K. Proposal: array_pop_bool pop_array_bool 字节码 两个字节码应该区分一下



### Q. Proposal: 字节码的顺序重新排列一下


### S. Proposal: @main 是否有点多次一举 ✅

fn main() {

}

main 函数就是函数的唯一入口

-----------------------------



## 2024-10-31周


### A. Proposal: 如何更好的调试显示 closure free-value的引用情况

1. 在运行过程中开启 trace_closure_free_value=1 输出 closure 的 trace
2. 将closure 的 trace生成一个 d2源码文件
3. 通过 d2 工具将 d2源码文件翻译成图片, 可以更直观的展示 closure的情况


### B. Test: 覆盖闭包相关的测试用例

1. 闭包中定于局部变量
2. 使用外部的局部变量
3. 变量的类型为 bool/int/int64/double/string
4. 嵌套闭包


### C. Proposal: defer机制 ✅

目前 Ring稍微有点成熟了，支持了匿名函数，支持了协程，有必要可以开始考虑defer机制了

```
fn main() {
    defer fn() {
    }()
}
```

1. 作为闭包可以捕获自由变量 （引用传递）
2. 可以传递参数 （值传递）




### D. 闭包在循环中定义会怎么办 ✅

for(i=0; i<10; i++) {
    fn() {
    }();
}

应该会运行10次 defer函数

### E. Test: 系统测试一下defer相关的功能

1. defer 通过闭包捕获引用
   - bool
   - int
   - int64
   - double
   - string

2. defer 通过参数捕获值
   - bool
   - int
   - int64
   - double
   - string

3. defer 参数捕获时，为可变参数



### F. Proposal: 调研 ring在windows上支持，需要什么工作


### G. Proposal: 协程关键字支持函数变量 ✅

```
var functype funcvar;
funcvar = fn() {

};
co_id = launch funcvar();
```


### H. Proposal: 协程关键字支持匿名函数 ✅

```
co_id = launch fn() {

}();
```


### I. Proposal: launch 即立即运行,不需要 resume



### J. Proposal: 不支持在 if for 代码块中定义局部变量


-----------------------------



## 2024-09-23周

### A. Proposal: 闭包变量

Ring已经支持了匿名函数，如果在匿名函数中支持闭包，
闭包的精髓是 捕获外层的局部变量，并且可以在匿名函数中修改外层的局部变量。

在闭包块中，可以使用三类变量：
- 全局变量
- 局部变量
- 闭包捕获的变量，我们称之为 FreeValue

那么一个Value，可能存在那个区域
- static
- constant pool
- heap
- free value pool


1. dump 的时候，需要dump出 匿名函数的详情&字节码





-----------------------------


## 2024-09-16周


### A. 支持简单的匿名函数 ✅


### B. 匿名函数要支持传递函数参数 支持返回值


### C. 调用闭包的时候，要支持像函数调用一样的参数校验


### D. Proposal: check匿名函数是否可以被调试 ✅

### E. Proposal: 不需要将匿名函数复制给一个函数变量 ✅


1. 可以直接返回  ✅

```
return fn() {

};
```

2. 不用命名变量, 直接通过函数传递参数  ✅

```
pass_closure(fn() {
		fmt::println("main:: closure block 1");
	}, fn() -> (string) {
		fmt::println("main:: closure block 2");
		return "main:: closure return value";
	});
```

3. 支持 Immediately invoked function expression ✅

```
fn() {

}();
```

对应的字节码

```
argument_num
push_closure
invoke_closures
```




### E. reflect::typeof() 支持获取匿名函数变量的类型 ✅

如果一个匿名函数变量没有被初始化，会得到 `nil-closure`

```
typedef fn() FuncType0;


var FuncType0  local_func_var0;
fmt::println(reflect::typeof(local_func_var0)); // nil-closure

```


### F. Proposal: reflect::typeof() 应该进行优化 ✅

1. 如果一个 变量没有分配内存，array/closure，typeof 也能获取到对应的值

-----------------------------


## 2024-09-02周

### A. Proposal: 添加 fmt::sprintf() 函数，用于格式化生成字符串 ✅

usage:

```
    var string str;

    str = fmt::sprintf("{} {} {}", false, 1, "ring");

```


### B. Proposal: 关于函数的可见行 TODO:

closure function build-function 他们名字相同时，允许覆盖么，

比如说 build-function append, 如果用户自定义了一个 append函数，他们是如何影响的





### F. Proposal: 在编译阶段，产生了很多 的 TypeSpecifier，如何节省内存空间。 TODO:


-----------------------------


## 2024-08-19周


### A. Feature: launch 调用的第一个函数，函数block 中支持 定义&初始化 局部变量  ✅ 

能否调用 Method

launch(a.method_);


那 static method，支持么：

launch(Job::create);



### B. Feature: launch 调用一个函数，支持传递函数参数  ✅ 

c语言 pthread_create() 支持通过 void* 来传递函数参数，函数原型是：

```
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
```


#### Ring launch 对函数该如何设计


1. `launch` 是个内置函数，使用方法如下：

```
    launch(func_, arg1, arg2);
```

2. 采用golang的方式，形式像调用函数，只不过前面多个一个 `launch` 关键字

```
    launch func_(arg1, arg2);
```




方式2有个好处，launch是个关键字，能够在语义检查的时候，方便对参数对合法性进行检查；同时，协程的入口函数可以是普通函数/类方法/类静态方法

```
    launch func_(arg1, arg2);

    var Job job;
    launch job.method_(arg1, arg2);


    launch Job::method_(arg1, arg2);
```


如果入口函数支持可变参数，也能很好的支持：

```
fn func_(var int... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
}

fn main() {
    launch func_(1, 2, 3);
}
```



当然，launch后续也可以扩展成一个代码块/匿名函数，这里需要后边统一设置匿名函数/闭包

```
    launch fn() {
        // action
        
        func_(arg1, arg2);
    }();
```






### C. Feature: 完善函数调用/方法调用 的语义检查  ✅ 


1. `func_();` 函数调用/方法调用：需要强制检查func_函数的参数类型是否一致
2. `launch func_();` 需要遵循 函数调用/方法调用 相同的语义检查




### C. Test: 系统化测试 Coroutine相关  ✅ 



### D. Fix: 当变量的定义和初始化过程中，如果初始化表达式为函数调用，行为不符合预期 ✅ 

e.g.

```
    var int a, b = func_();
```

经排查，是因为 `Declaration::next` 指针混乱，导致在使用的过程中混淆

解决方法：
1. 将变量的定义+初始化分成两个语句，Declaration + Assignment
2. 在Declaration阶段，不生成对应的字节码
3. 在Assignment阶段，生成对应的assign字节码，同时这个阶段方便的对 赋值语句的左值和右值进行语义检查，检查类型是否匹配。


### E. Proposal: 关于ring的保留字

#### 1. class 中的 field/method 是否应该改为 var/fn

直观的优点是：这样可以少两个关键字

但是我还有几个理由不这样做：

1. var 可以定义
   - 函数中的局部变量
   - package中的全局变量
   - 类中的静态变量（参考cpp）
2. function 可以定义
   - 用来声明函数
   - 类静态方法
3. field 只能用来定义 类中的非静态成员变量
4. method 只能用来定义 类中的非静态成员方法

e.g.

```
typedef class Job {
    var int count;

    field int Name;


    fn init() -> (Job) {

    }

    method printInfo() {

    }
}

global {
    var int global_int;
}

fn main() {
    var int a;
}
```


Job::init() 为静态方法
Job::printInfo() 为非静态方法

```
    Job::init(); // 调用镜头方法


    var Job job_value;

    job_value.printInfo();

```



当起Ring还不是 类中的静态field/method，可以后续扩展


#### 2. 定义函数 function 关键字精简 为fn  ✅ 

这样的优点是，在定义匿名函数的时候比较迅速：

```
func_ = fn() {

}
```



### F. 关于多项赋值


这一行是编译不通过的，需要放开限制

```
var int global_int_value_1, global_int_value_2 = get_next_global_count(), get_next_global_count();
```





### L. Proposal: ring dump  ✅ 

在dump 某些字节码时，如果字节码的类型是 OPCODE_OPERAND_TYPE_2BYTE_AB/OPCODE_OPERAND_TYPE_2BYTE_ABs，应该分开展示，便于理解

例如， duplicate应该这样展示：

```
 ├──66      duplicate                     1, 1                               
```


同时还要支持一下 详细模式和精简模式
- 详细模式下，对于 invoke_func , 能够展示函数名称，这样能提高调试效率




-----------------------------


## 2024-08-12周

### A. Feature: ring执行的时候，支持 `RING_DEBUG` 环境变量  ✅ 


为更好的开发调试Ring，有的时候需要展示虚拟机内部运行状态，如：
- 在函数调用时，能够展示`CallInfo`的切换
- 在协程切换时，能够展示 协程切换详情


目前有两种方式可以实现：
1. 在编译Ring编译器的时候，指定编译参数宏，如果 `g++ -DEBUG_XX`
   - 缺点：需要重复编译 Ring编译器源码，浪费时间
2. 提供一个命令行参数，e.g. `ring -print_call_info=true run test.ring`
   - 缺点：后续如果有很多需要打印的信息，参数会很多，不方便使用，ring命令参数会变复杂
3. 提供 环境变量，如Golang：`GODEBUG=inittrace=1 go run test.go`

最终所以决定采用 环境变量的方式：

1. 展示函数调用栈的变化：`RING_DEBUG=trace_func_backtrace=1`
2. 展示协程切换详情：`RING_DEBUG=trace_coroutine_sched=1`
3. 可以同时指定多个：`RING_DEBUG=trace_func_backtrace=1,trace_coroutine_sched=1`


e.g. 

```shell
RING_DEBUG=trace_func_backtrace=1,trace_coroutine_sched=1 ring run test.ring
```




### G. Optimize: invoke/finish derive-function in VM execution ✅ 

#### 现状：

`ring_execute_vm_code()` 函数中 通过局部变量 `code_list/code_size/pc` 来表明当前的指令和PC
1. 在调用函数/函数返回 & resume/yield 的时候 都需要更新 `code_list/code_size/pc`
   - 问题：所以在实现的时候，`code_list/code_size/pc` 都是把指针左右函数参数的
2. 在`CallInfo` 和 `RingCoroutine` 中也维护了 `code_list/code_size/pc`
   - 问题：信息冗余，不能很好的确定什么时候更新

问题：引入协程之后，debug::print_call_stack() 显示的代码所在的行数不正确

#### 改进：

1. `ring_execute_vm_code()` 函数 不在维护局部变量 `code_list/code_size/pc`
2. 统一直接访问 当前线程+当前CallInfo 的 `code_list/code_size/pc`


### H. Test: `debug::print_call_stack()` ✅ 


完善一下测试用例，看看展示的 函数和行数 是否正确

1. 函数中 应该有一些空行
2. 函数中 应该多一下不相关的空语句



### I. Feature: RVM-Cmd-Interactive-Tool

1. 协程相关：
   - 能够展示当前的协程ID
2. 函数调用相关：
   - 调用derive函数的时候，能够实时展示当前CallInfo List，更直观的展示当前Opcode所在的位置;有点类似于 `debug::print_call_stack()` 函数的功能
3. 展现 当前Opcode 对应Ring源码的所在行和源码内容
4. 如果能够设置断点就更好了





### M. 测试在 在 runtime_stack 中不 pop, 会影响当前的栈空间么 TODO:


### N. Update: debug::print_call_stack() 

1. 这个函数应该直接返回一个string，而不是直接打印
2. 应该还有更强的函数，能够以列表的形式展返回当前的 CallInfo List
   - std pacakge 定义 这个类型
   - 用户可以更加方便的通过 index 获取



-----------------------------


## 2024-07-29周

### A. 关于Ring的限定符号

1. 限定符号`::` 用于限定访问空间，主要侧重的是命名空间/层级/访问可见性

1.1 访问 package中的函数：访问 `fmt` package  中的函数 `println`

```ring
import {
    fmt;
}

fn main() {
    fmt::println("hello world");
}
```


1.2 访问package中的类：使用 `job` package  中的类 `Job`

```ring
import {
    job;
}

fn main() {
    var job::Job tmp;
}
```

1.3 访问enum中的类型：

```ring
enum string Region {
    Test = "test";
    Prod = "prod";
}


fn main() {
    var string tmp = Region::Test;
}
```

1.4 当然，也可以多级作用域指示：访问 `job` package 内的 枚举 `Region`, 枚举`Region` 中的枚举常量为 `Test`

```ring
import {
    job;
}

fn main() {
    var string tmp = job::Region::Test;
}
```

2. `.` 限定符号，主要用户访问类对象中的 成员/方法

```ring
typedef class Job {
    field string Name;

    method PrintInfo() {

    }
}
fn main() {
    var Job tmp;

    tmp.Name;
    tmp.PrintInfo();
}
```


3. `->` 用于函数返回值

```ring
fn test() -> (int) {
    return 0;
}
```



### B. 关于Rust的限定符号

Rust 中使用 `::` 符号来访问包和类型成员的主要原因如下:

1. **命名空间和作用域**: Rust 使用 `::` 符号来明确指定命名空间和作用域。这样可以避免名称冲突,并帮助编译器确定正确的符号解析路径。

   例如, `std::io::stdin()` 中的 `std` 和 `io` 就是命名空间,`stdin()` 是 `io` 模块中的一个函数。使用 `::` 可以清楚地表示这种嵌套的作用域关系。

2. **区分变量和类型/模块**: Rust 中变量和类型/模块是区分的。变量使用 `.` 访问它们的方法和属性,而类型/模块使用 `::` 访问它们的关联函数和常量。

   例如, `String::from("hello")` 中的 `String` 是一个类型,而 `"hello".to_string()` 中的 `to_string()` 是 `String` 类型的方法。使用 `::` 可以清楚地区分这两种情况。

3. **全局访问**: `::` 符号也可以用于全局访问,即从根作用域开始访问。这在某些情况下很有用,比如访问标准库中的类型或函数。

   例如, `::std::env::args()` 可以直接从根作用域访问标准库的 `env` 模块中的 `args()` 函数。

4. **一致性和习惯**: 在 Rust 生态系统中,使用 `::` 符号访问包和类型成员已经成为一种惯例和标准。这种使用方式也与其他语言(如 C++、Java 等)的习惯保持一致,有利于开发者的学习和理解。

总之,Rust 中使用 `::` 符号的主要目的是为了明确表达命名空间、作用域和类型/模块的关系,从而提高代码的可读性和可维护性。这种使用习惯也有助于Rust开发者快速上手并与其他语言开发者进行交流。



```
struct Circle {
    radius: f64,
}

impl Circle {
    fn new(radius: f64) -> Circle {
        Circle { radius }
    }

    fn area(&self) -> f64 {
        std::f64::consts::PI * self.radius * self.radius
    }
}

let circle = Circle::new(5.0);
println!("Area: {}", circle.area());
```

Circle::new() 是一个关联函数,用于创建新的 Circle 实例。circle.area() 则是一个成员函数,用于计算圆的面积




### C. 如何优化 ConstPool

1. 想string能够去重
2. 对于 false/0/0L/"" 都够处理，他们不在占着一个 常量，
   1. 在实现的时候应该特例化字节码
   2. 如 应该提供 push_bool_false push_int_0 push_int64_0 push_string_empty 等字节码, 这样单独处理有助于优化字节码的执行流程
3. 对于 ConstPool来说，他应该是全局的，不是一个 package中内的



### F. 一个package中 import-package的名称/enum的名称/class的名称/函数的名称  均不能相同，不然语义分析会产生错误，后续可以考虑优化



### I. 实现 std io/os/time/math package ✅

分几步走：

1. 只通过文件描述符（int）实现文件的打开，读写
2. 抽象出 io::File 类，通过类进行读写，目前类缺失的功能有：
   1. std-package 中 import 别的 std-package
   2. 在main package中使用 std-package 中的类
   3. 需要实现 Enum


io package 需要实现的功能:
1. exist
2. open
3. create
4. seek
5. read_all
6. read
7. write
8. close
9. remove (这里需要移到os-package中)

os package 需要实现的功能:
1. exit
2. remove
3. rename
4. getenv
5. setenv


runtime package 需要实现的功能:
1. getlocal()  // 通过变量名称获取值，值可能是 bool/int/int64/double/string
2. getglobal() // 通过变量名称获取值，值可能是 bool/int/int64/double/string

vm package:
1. heap_size() // 返回值应该为 int64


debug package:
1. debug_assert() // 后续已经改为 assert


time package
1. sleep()
2. time()
3. time formate

fmt package
1. sprintf

math package
1. sqrt
2. abs
3. log



Fix: 需要在语义分析的时候检查，std package lib
1. 如果 std/os/*.ring 定义了，但是 std_lib.cpp 中没有定义，这里会报错
2. 如果 std/os/*.ring 没有报错，报错：找不到函数定义
3. 需要精确的匹配函数调用的参数是否一致

### K. RVM_String 便利的API

1. 创建一个string, 指定capacity
2. 创建一个string, 通过std::string 指定
3. memcpy 函数 copy到 string中. 需要自动append内存
4. strcpy 函数 copy到 string中. 需要自动append内存
5. 需要自动append内存


### M. 在调用 标准库中的函数时候, 需要根据 标准库中的函数定义做一个详细的 语义检查, 跟derive函数一样

1. 函数参数的数量是否正确
2. 函数参数的类型是否正确
3. 包括可变参数
4. 函数的返回值






var string content 初始化会调用两次, 需要修正.
初始化的时机不对


### U. 关于 rdb（ring debugger）不成熟的想法

1. rdb断点停止的时候，可以通过  `printf a` 命令打印变量的名称
   1. 当然printf 后边的表达式也可以复杂一点， `printf a+1+2*3`，功能有点类似于 repl
   2. 基于目前ring的编译方式，如果要实现这个功能的话，实现会比较复杂：编译，生成字节码，运行字节码
   3. 而且，字节码还比较重：需要有 func，调用func
2. 为了实现这个功能：
   1. 思路1: 能够提供一个解释执行的方式，在 repl/rdb （包括交互式调试RVM行为） 中，能够调用解释执行的能力，能够更简单的实现。
   2. 思路2: 
3. 但是解析执行，有很多行为应该不太容易支持


### Y. Doc: 整理Ring历史版本相关文档  ✅

1. v0.2.15
2. v0.2.16



### Q. Test: make testall 支持指定 module

1. 脚本支持 

2. make testall 支持传递参数


### L. Fix: int64 算术运算bug

5L*1000000000L 存在bug


### P. Feature: 重新考虑一下 ring链接过程

1. 全局变量的分配
2. 每个package中函数的分布
3. enum的分布

### Z. 一个不成熟的想法



应该有一个比较好的生态工具链

1. 函数调用图
2. 性能分析
3. 代码格式化工具
4. 调试器
5. IDE
6. LSP
7. Playground
8. 在线Playground能够看对应的虚拟机字节码

还有一些调试工具
1. 能够展示 global_init 函数调用顺序
2. 展示gc的流程
3. 动态展示当前所有协程图


#### ring 支持原生的函数调用图/调用性能

目前golang有这几种实现方式

1. pprof
2. go-callvis
3. Graphviz

关于调用图，我有这两种想法：
1. 静态生成，
2. 通过调用链动态生成，比如说我执行一个函数，然后展示运行的调用链


流程
1. 拉启一个进行
2. 运行过程中记录函数的调用记录
3. 把函数调用记录生成 dot语言
4. 通过 Graphviz 生成调用图






#### ring支持原生的代码格式化工具

-----------------------------


## 2024-07-15周


### A. 检查一下 GC分配的字节数量是否一致

在应用了 var string[] args 之后，字节数校验不太好


### B. 一步步调试虚拟机的时候，能够显示某个字节码的功能/公式/全局变量/局部变量

1. 这是一个 jvm 交互式调试工具
   
![alt text](image.png)

2. 支持简单的命令
   - q 退出调试
   - help 获得帮助信息
   - stack 获取 RuntimeStack 的RVM_Value值详情
  
![命令获取RuntimeStack详情](image-4.png)


3. 显示下一个字节码/功能/公式

![](image-6.png)

4. 每运行一步，在log中都打印 所有 全局/局部变量 的值

所以 在运行过程中，还要捕获 frame

5. 能够设置端点


6. 实时显示对应的当前的源代码函数和内容

7. 通过环境变量 运行 交互式调试工具

RING_DEBUG=debug_vm_iter=1 ./bin/ring run ./test.ring


### C. 关于 字符串常量在 vm中的优化

1. formate rvm constant pool 的时候，转义字符要反转义

![alt text](image-1.png)


2. 如果字符串是空的话，constant pool 应该为空

![alt text](image-2.png)


3. string 常量，应该去重

![alt text](image-3.png)





### D. 关于多个package中的 全局变量/函数/类 虚拟机的空间布局如何组织


在 Java 中,当一个函数被调用时,对应的字节码指令如下:

1. **方法调用指令**:
   - `invokevirtual`: 用于调用对象的虚方法。
   - `invokespecial`: 用于调用构造方法、私有方法以及父类的方法。
   - `invokestatic`: 用于调用静态方法。
   - `invokeinterface`: 用于调用接口方法。

2. **参数传递**:
   - 在方法调用指令之前,会先将参数压入操作数栈中。
   - 参数的顺序是从左到右,最后一个参数先压栈。

3. **返回值处理**:
   - 方法执行完毕后,返回值会被压入操作数栈顶。
   - 调用者可以从操作数栈中取出返回值。

下面是一个简单的 Java 代码示例及其对应的字节码指令:

```java
public class Example {
    public static int add(int a, int b) {
        return a + b;
    }

    public static void main(String[] args) {
        int result = add(3, 5);
        System.out.println(result);
    }
}
```

对应的字节码指令如下:

```
// add 方法调用
0: bipush        3
2: bipush        5
4: invokestatic  #2                  // Method add:(II)I
7: istore_1

// 打印结果
8: getstatic     #3                  // Field java/lang/System.out:Ljava/io/PrintStream;
11: iload_1
12: invokevirtual #4                  // Method java/io/PrintStream.println:(I)V
15: return
```

解释如下:

1. `bipush 3` 和 `bipush 5` 将参数 `a` 和 `b` 压入操作数栈。
2. `invokestatic #2` 调用静态方法 `add`。
3. `istore_1` 将返回值存储到局部变量 `result`。
4. `getstatic #3` 获取 `System.out` 对象。
5. `iload_1` 将 `result` 从局部变量加载到操作数栈。
6. `invokevirtual #4` 调用 `println` 方法打印结果。
7. `return` 方法返回。

总之,Java 的方法调用对应的字节码指令主要包括参数传递、方法调用和返回值处理等步骤。理解这些字节码指令有助于深入理解 Java 的运行机制。





### E. invokevirtual 本质上是调用了一个函数, 函数是通过索引在函数表中查找到的; 如果import 了多个 package, 那么函数的索引是如何保证不冲突的; 也就是java如何实现的链接


Java 中的 `invokevirtual` 指令确实是通过调用函数表(Virtual Method Table, VMT)来实现动态派发的。但是当存在多个导入的 package 时,Java 是如何确保函数索引不会冲突的呢?

这涉及到 Java 的链接(Linking)机制:

1. **类加载器(Class Loader)**:
   - 每个类都由一个特定的类加载器加载。
   - 类加载器负责从文件系统或网络等位置加载类文件,并定义该类在 JVM 中的名称空间。

2. **名称空间**:
   - 类加载器为每个加载的类创建一个唯一的名称空间。
   - 这个名称空间包括类的名称、方法名称、字段名称等。

3. **方法解析**:
   - 当调用 `invokevirtual` 指令时,JVM 会首先在当前类的 VMT 中查找方法。
   - 如果没找到,则会沿继承层次向上查找,直到找到为止。
   - 查找过程中会考虑方法的名称、参数类型等信息来确定要调用的具体方法。

4. **类文件结构**:
   - 每个类文件都有一个常量池,用于存储类、方法、字段等的符号引用。
   - 在链接阶段,JVM 会解析这些符号引用,并转换为直接引用(内存地址)。

通过上述机制,即使 Java 项目中导入了多个 package,也能够确保方法调用的正确性:

1. 每个类都有自己的名称空间,不会与其他类产生冲突。
2. 方法调用时,JVM 会根据方法的完整签名(包括名称和参数类型)来查找正确的方法实现。
3. 类文件的常量池存储了符号引用,在链接阶段会被解析为直接引用,保证了调用的正确性。

总之,Java 的链接机制通过类加载器、名称空间、方法解析等机制,确保了即使导入了多个 package,也能够正确地调用目标方法,避免了索引冲突的问题。这是 Java 设计的一个重要特性,有助于提高代码的可扩展性和可维护性。



### F. java 相关的书籍

关于 Java 的链接机制和虚拟方法调用的实现,有几本比较优秀的书籍可以作为参考:

1. **《Java 虚拟机规范》(The Java® Virtual Machine Specification)**
   - https://docs.oracle.com/javase/specs/jvms/se8/html/jvms-5.html
   - 这是由 Oracle 官方发布的 Java 虚拟机规范,详细介绍了 JVM 的各种指令、数据结构和运行机制。
   - 其中第 5 章"Loading, Linking, and Initializing"专门讨论了类的加载、链接和初始化过程,对虚拟方法调用有详细的描述。

2. **《深入理解 Java 虚拟机》(Inside the Java Virtual Machine)**
   - 这是一本非常经典的 Java 虚拟机实现原理方面的著作,由 Bill Venners 编写。
   - 第 6 章"类加载和链接"深入探讨了 Java 类的加载过程、符号引用解析以及动态链接的实现细节。
   - 第 7 章"对象创建与方法执行"则介绍了虚拟方法调用的具体机制。

3. **《Java 程序员修炼之道》(The Complete Software Developer's Career Guide)**
   - 这是一本专注于 Java 程序员职业发展的书籍,作者为 John Sonmez。
   - 其中第 11 章"理解 Java 虚拟机"就包含了对 Java 虚拟机运行原理的详细解读,包括类加载、方法调用等内容。

这些书籍都对 Java 虚拟机的底层实现机制进行了深入的分析和讨论,对于理解 Java 语言的运行原理以及优化 Java 程序的性能都有很大帮助。如果你对 Java 虚拟机的实现细节感兴趣,这些书籍是非常值得一读的。



-----------------------------


## 2024-07-08周


### A. Feature: 在Ring main()函数中 获取命令行参数 ✅ 


1. golang 获取命令行参数方式，通过 os.Args 全局变量

```go
package main

import (
	"fmt"
	"os"
)

func main()  {
    fmt.Println(os.Args)
}
```

2. c/cpp 获取命令行参数方式

```cpp
int main(int argc, char** argv) {
}
```

3. ring 获取命令行方式


用户调用方式：

```bash
./bin/ring run ./test.ring a b c
```

ring main 的函数原型

```ring
fn main(var string[] args) -> (int) {
    return 0;
}
```

如果不打算收集 args，这样的main函数也是可以的
```ring
fn main() -> (int) {
    return 0;
}
```



### B. Fix: main 函数中使用 var string[] args, 导致某些GC测试用例不通过 ✅ 


### C. Feature: string支持 substr


### D. Feature: 数组支持 sub-array


### E. Feature: 强制检查 main函数的签名 ✅ 


1. main 函数 没有返回值
2. main 函数 如果有参数的话，参数只有有 一个，`var string[] args`
3. main 函数的参数可以省略
4. 合法的main函数定义

```
fn main(var string[] args) {
}
```

```
fn main() {
    // main 函数 无需关注 命令行参数
}
```

5. 如果main函数需要自定义返回值的话，请使用 `os::exit()` 函数
   
```
fn main() {
    os::exit(-1);
}
```


### F. Feature: std reflect package 函数 typeof 支持 获取多维数组/多维数组 中间状态数据的类型 ✅ 

1. 详细的测试用例可参见 ./test/062-std-package-reflect/reflect-001.ring 

### G. Fix: for range 多维数组 rvm 会崩溃 ✅ 

1. for range 多维数组是，其实 stack中的参数数是个多维数组的中间态
2. 增加了一个 字节码 `range_array_a`
3. 如果是多维数组是， for-range 对应的字节码 应该是 `range_array_a`
4. rvm 执行 `range_array_a`

-----------------------------


## 2024-07-01周

### A. 函数定义中，参数的名字和局部变量的名字不能一样，需要报错提示


### B. 隐式类型和显式类型转化

因为 存在 int/int64/double ，如何不及早的考虑这个问题，Ring还是不太易用。



### C. 对于 function-call method-call 没有做详细语义检查，尤其是参数匹配

### D. function/method 的参数/返回值 最大不能超过 8, 除了可变参数

1. 如果后边有初始化表达式，连续命名变量也不成超过八个

```
var bool a0,a1,a2,a3,a4,a5,a6,a7,a8 = false,false,false,false,false,false,false,false,false;
// 编译错误
```


### E. BUG: 类 local变量命名+初始化 运行报错， ✅ 

./test/999-bug-list/class.ring    

```
var Job1 local_job1_value_0 = Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
```


这样不会报错：
```
var Job1 local_job1_value_0;
	
	local_job1_value_0 = Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
```



在 fix_ast 中 未对 initializer 进行修正


### F. 测试所有类型的 定义并初始化

1. bool/int/int64/double/string  通过常量初始化，通过变量初始化
2. class 通过常量初始化，通过变量初始化
3. 数组 通过常量初始化，通过变量初始化



### G. 测试所有类型的 赋值

1. bool/int/int64/double/string  通过常量赋值，通过变量赋值
2. class 通过常量赋值，通过变量赋值
3. 数组 通过常量赋值，通过变量赋值



### H. 编译需要提示

```
var int a,b = 1;
```

这种情况下需要报错提示。

### I. 现在全局变量不能进行初始化，需要用户手动调用init函数进行初始化

当初为什么这么设计：

1. 首先考虑局部变量的初始化流程：

```
fn test() {
    var int local_int = 1;
}
```

那么他在生成test() 对应的字节码入下：
```
$test()    <./test/998-error-report/test.ring:18,20>
+Parameter:   0
+Local:       1
 ├──var int              local_int           
+Instructions:
 ├──*Num    *Instruction                  *Operand            *SourceLineNum    
 ├──0       push_int_1byte                1                   19                
 ├──1       pop_stack_int                 0                                     
 ├──2       function_finish                                   20                
```

也就是说，他实现了两个行为，初始化local变量所需要的空间+执行assignment语句字节码
如果函数被调用的时候，正好在函数中执行 assignment语句字节码。


2. 考虑全局变量

```
global {
	var int global_int = 1;
}

fn main() {
}

```

他生成的字节码是这样的：
```
#Constants:       0

#Globals:       1
 ├──var int              global_int          

$main()    <./test/998-error-report/test.ring:19,20>
+Parameter:   0
+Local:       0
+Instructions:
 ├──*Num    *Instruction                  *Operand            *SourceLineNum    
 ├──0       function_finish                                   20        
```


也就是说，他没有跟局部变量 对应的assignment字节码，没有调用时机。
除非手动 写一个 init() 函数，ring 需要在进程启动的时候，按照package的引用顺序，依次调用 init() 函数中
或者说，这个 init() 函数应该是 隐式的，不需要用户手动书写。


3. golang中全局变量初始化时机

```
在 Go 语言中,全局变量的初始化时机有以下几种情况:

1. **包级别变量初始化**:
   - 包级别的变量会在程序启动时被自动初始化。
   - 初始化顺序是先初始化包级别的常量,然后再初始化包级别的变量。
   - 包级别变量的初始化是按照它们在代码中出现的顺序进行的。

2. **init() 函数初始化**:
   - 每个 Go 包都可以包含一个或多个 `init()` 函数,这些函数会在包级别变量初始化完成后被自动调用。
   - `init()` 函数可以用于执行一些复杂的初始化逻辑,比如读取配置文件、连接数据库等。
   - 多个 `init()` 函数的调用顺序遵循包的依赖关系,被依赖的包的 `init()` 函数先被调用。

3. **main 函数初始化**:
   - 在 `main` 包中,所有的包级别变量和 `init()` 函数的初始化都会在 `main()` 函数执行之前完成。
   - 在 `main()` 函数中,可以访问和使用已经初始化好的全局变量。

总的来说,Go 语言中全局变量的初始化顺序是:包级别常量 -> 包级别变量 -> `init()` 函数 -> `main()` 函数。开发者需要注意这种初始化顺序,以确保全局变量能够正确地初始化和使用。
```

敲定Ring global变量 当前实现方式：

1. 用户不能定义 init() 函数
2. 虚拟机内部实现 __init() 函数
3. __init() 函数中 只进行全局变量的初始化
4. 还要考虑 __init()函数的 调用顺序
5. 在 初始化虚拟机的时候，依次调用 __init() 函数
6. 添加一个环境变量 RING_DEBUG=trace_init_func=1 可以看见 init函数的执行顺序
   1. RING_DEBUG=trace_init_func=1 ./bin/ring run ./test.ring



### M. main-package 引用了 b-package

如果 b-packag 含有 main() 函数，那么这个函数是不会被调用的，
被调用的只有 main-package 中的main函数

不然会产生逻辑错误

ring 需要做一下限制

1. 只能在main-package中实现的main() 函数才能被调用
2. main-package在最top，别的包不能 import 它，也就是说这样是不合法的
   ```
   import "main"

   main::func_test();
   ```
3. 不能通过 main包名访问 main包中的函数/全局变量
   ```
   main::func_test();
   ```



### N. 调研/涉及 switch/match 语法


### Z. 调用 rust 元组tuple的语法逻辑

```rust
fn main() {
    // 创建一个元组
    let my_tuple = (42, 3.14, "hello");

    // 访问元组中的元素
    println!("Integer: {}", my_tuple.0);
    println!("Float: {}", my_tuple.1);
    println!("String: {}", my_tuple.2);

    // 解构赋值
    let (a, b, c) = my_tuple;
    println!("a = {}, b = {}, c = {}", a, b, c);
}
```

tuple也可以match：
```rust
fn main() {
    let point = (3.0, 4.0);

    match point {
        (0.0, 0.0) => println!("Origin"),
        (x, 0.0) => println!("X axis: {}", x),
        (0.0, y) => println!("Y axis: {}", y),
        (x, y) => println!("({{}, {}})", x, y),
    }
}
```


其他各个语言的tuple语法，https://llever.com/rust-ffi-omnibus/tuples/

2. cpp 的 tuple，还是一如既往的复杂

https://en.cppreference.com/w/cpp/utility/tuple

```cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
 
std::tuple<double, char, std::string> get_student(int id)
{
    switch (id)
    {
        case 0: return {3.8, 'A', "Lisa Simpson"};
        case 1: return {2.9, 'C', "Milhouse Van Houten"};
        case 2: return {1.7, 'D', "Ralph Wiggum"};
        case 3: return {0.6, 'F', "Bart Simpson"};
    }
 
    throw std::invalid_argument("id");
}
 
int main()
{
    const auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';
 
    const auto student1 = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << std::get<double>(student1) << ", "
              << "grade: " << std::get<char>(student1) << ", "
              << "name: " << std::get<std::string>(student1) << '\n';
 
    double gpa2;
    char grade2;
    std::string name2;
    std::tie(gpa2, grade2, name2) = get_student(2);
    std::cout << "ID: 2, "
              << "GPA: " << gpa2 << ", "
              << "grade: " << grade2 << ", "
              << "name: " << name2 << '\n';
 
    // C++17 structured binding:
    const auto [gpa3, grade3, name3] = get_student(3);
    std::cout << "ID: 3, "
              << "GPA: " << gpa3 << ", "
              << "grade: " << grade3 << ", "
              << "name: " << name3 << '\n';
}
```

### X. 设计Ring tuple 语法

```ring

var int a = 1;
var b = (false, 0, 1L, 1.1, "a");

b.0;
b.1;
b.2; // 访问 tuple中的元素


typedef tuple Student = (bool,int,int64,double,string);


fn test0(var (bool,int,int64,double,string) a) -> ((bool,int,int64,double,string)) {

}

fn test1(var Student a) -> (Student) {

}



```


体外话：

```ring
typedef class Job1 = {
    field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;
}

这样设计的话：是不是可以跟var 对齐

var     int   int_value = 1;
typedef class Job1      = {};

typedef tuple Student   = (bool,int);

```


tuple 没有method，每个field没有名字

### U. golang switch 和 rust match 功能比对



Golang 的 `switch` 语句和 Rust 的 `match` 语句在功能上有一些相似之处,但也存在一些重要的区别。下面是它们的比较:

1. **语法和结构**:
   - Golang 的 `switch` 语句使用 `case` 关键字来匹配值,而 Rust 的 `match` 语句使用模式匹配。
   - Golang 的 `switch` 语句默认会在匹配到第一个 `case` 后直接退出,而 Rust 的 `match` 语句会继续检查其他分支,除非使用 `break` 语句。

2. **匹配表达式**:
   - Golang 的 `switch` 语句可以匹配任意类型的表达式,包括整数、浮点数、字符串等。
   - Rust 的 `match` 语句可以匹配任意类型的表达式,包括枚举、元组、结构体等复杂类型。

3. **穿透(Fallthrough)**:
   - Golang 的 `switch` 语句支持 `fallthrough` 关键字,允许执行下一个 `case` 分支,除非使用 `break` 语句。
   - Rust 的 `match` 语句没有类似的 `fallthrough` 机制,每个分支都是独立的。

4. **默认分支**:
   - Golang 的 `switch` 语句支持 `default` 关键字来定义默认分支。
   - Rust 的 `match` 语句使用 `_` 作为通配符来定义默认分支。

5. **返回值**:
   - Golang 的 `switch` 语句可以返回值,与其分支的返回值相关。
   - Rust 的 `match` 语句必须在每个分支上都有返回值,以确保整个表达式有返回值。

总的来说,Golang 的 `switch` 语句更加灵活和简单,适合处理单一值的匹配。而 Rust 的 `match` 语句更加强大和安全,能够处理复杂的模式匹配。Rust 的 `match` 语句也更加鼓励完整性和穷尽性检查,提高了代码的可读性和可维护性。


### R. 调研 java match 字节码的实现逻辑

### Y. 还要检查 main-package中是否含有main函数


### T. 废弃bison中老的 attribute 相关的语法。 ✅ 

-----------------------------


## 2024-06-24周


### A. 一个 Package中如何支持多个 源码文件

测试历程：test/997-feature

需要改进一下编译架构/流程，并发编译，提高编译速度

需要确认几点：
1. bison 如何支持并发编译
2. 多个文件，语义分析的过程如何进行
3. ./bin/ring run <file1> <file2>
4. ./bin/ring run ./   找到当前文件下的所有 ring文件进行编译链接


这个优化当前看来还有有点困难，是不是为时尚早？？？



### B. 如何支持项目组织

一个项目中含有多个Package，Package可以嵌套。


### C. 实现类rust 的模式匹配 match


### D. 定一个比较大的计划，调研 golang rust swift moonbit php python lua 等语法规范


### E. 调研 Lua JIT


-----------------------------


## 2024-06-11周

### A. 中间代码优化-实现简单的常量折叠




### B. 中间代码优化-实现简单的死代码删除


### C. 为了比较好实现在编译过程中解析 int64常量，需要在数字常量的后边手动添加一个 L ✅ 

这样实现可以让编译器比较方便的认为他是一个 int64常量，但是后续这个肯定是要进行优化的。

如：
```
0L;
-1L;

var int64 int64_value;

int64_value = 288L; 
int64_value = 288; // 编译错误
```


### D. int64 数据类型的测试用例要覆盖的全一点


### F. 针对fix_ast中的 要优化的编译报错，进行统一处理

1. 数学运算 + - * / %
2. 逻辑运算 and or
3. 非运算 not
4. 负号 -
5. 三目条件运算： ? :
6. 比较运算 < > <= >= == !=
7. 字符串拼接运算 ..


1. left right 操作数 的类型要一致
2. 不同的运算符 支持不同的操作数类型


### G. dlv的调试命令参考一下 dlv gdb, 


### H. 当前 int/int64/double/string 才能进行 大小比较运算

如果 有一个class，class的两个对象，如何运用到 大小比较运算
这里初步想到了两个解决办法：
1. 类似于cpp，通过method重载运算符
2. 类似于python，使用 重写以下方法：__gt__ __lt__ __ge__ __le__ __eq__ __ne__


### M. int/int64/double 支持 ++ -- ✅ 

TODO: 这里对应了 六个字节码，后续需要进行简化。

### N. self increase/decrease 实现的存在问题 ✅ 

只能对  int 自增，需要扩展到 int64/double

做一个全面的测试
1. int/int64/double ✅ 
2. 全局变量/局部变量   ✅ 
3. 类中的元素         ✅ 
4. 数组中的元素       ✅ 


### K. 对 ring -O2 dump 进行自动化测试


-O2 会开启编译优化，精简字节码，所以需要有一个专门的测试用例脚本用来测试。

### Q. 关于 unitary 表达式的语义检查，操作数的类型

unitary 有 - not ++ --

他的操作数可以是：
1. 常量
2. 局部变量
3. 全局变量
4. 类中的成员
5. 数组中的元素
6. 函数调用返回值 （++ -- 不行，他们不是左值）
7. method调用返回值（++ -- 不行，他们不是左值）


但是这种情况是可以的, 所以又成了左值和右值的问题：
```
func main() {
	return_job().ID++         // 编译错误
	return_job_pointer().ID++ // 可以
}


func return_job() Job {
	job := Job{ID: 1, Name: "Job1"}
	return job
}

func return_job_pointer() *Job {
	job := Job{ID: 1, Name: "Job1"}
	return &job
}
```

-----------------------------


## 2024-06-03周

### B. break point 信息优化


### C. 如何判断 class 递归定义


### D. 一个package中含有多个ring源代码文件


### E. 当前只能在main package中定义全局变量, 

如何在非main package中定义全局变量, 并能够在别的包中使用其他包的全局变量.
涉及到一个问题: 
1. 全局变量如何排布. 
2. 全局变量的初始化顺序


### F. 当前只能在main package中定义 class


### G. string 支持 utf-8编码


### H. ring 关于 relational-comp 相关字节码的行为优化 ✅ 

```
case RVM_CODE_RELATIONAL_LE_INT:
    STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) <= STACK_GET_INT_OFFSET(rvm, -1));
    runtime_stack->top_index--;
    rvm->pc++;
    break;
```

这里的流程设计的稍微不太好, 
```
STACK_GET_INT_OFFSET(rvm, -2) = (STACK_GET_INT_OFFSET(rvm, -2) <= STACK_GET_INT_OFFSET(rvm, -1));
```

应该是 
```
bool_value =  (STACK_GET_INT_OFFSET(rvm, -2) <= STACK_GET_INT_OFFSET(rvm, -1));
STACK_SET_BOOL_OFFSET(rvm, -2, bool_value);
```


### B. 有个重大bug

就是 int常量 给 int64 赋值的时候 会存在问题.


./test/002-int/int-000.ring: 这个编译会报错
2147483648 在编译器认为是个 int64, 直接赋值给 int32 编译器会报错

```
	var int int_value_1 = 0;
    int_value_1 = -2147483648;
```


2. bug
```
	// TODO: 2147483648 在编译器认为是个 int64, 直接赋值给 int32 编译器会报错
	// int_value = 2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == 2147483648);

	// TODO: 2147483648 在编译器认为是个 int64, 直接赋值给 int32 编译器会报错
	// int_value = -2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == -2147483648);

	// TODO: 2147483648 在编译器认为是个 int64, 0 认为是 int32 , 编译器报错
	// int_value = 0-2147483648;
	// fmt::println_int(int_value);
	// debug::debug_assert(int_value == -2147483648);
```


3. 报错优化

应该报错， 因为 1不是左值
```
1++;
```


### C. test/061-std-package-fmt/fmt-007.ring 这个测试用例需要再完善一下

完善一下 fmt::printf fmt::println 对于 类和数组的支持，需要验证 多层class的嵌套定义，包含数组类型等等。


### D. std package vm heap_size()  返回值统一改成 int64


### E. 支持 命名 any类型的 局部变量/全局变量

任何值都可以赋值给它，以此来实现范型。


### F. 检测 binary-expression 两边的表达式要保持一致

基本完成  ✅ 


### G. 这里有个bug

这里应该报错
```
var int64 sum = 0;
```


### H. 语义检查

这个语句是不允许的
```
sum = sum++;
```

不能将 自增/自减 运用到复杂表达式中。

-----------------------------


## 2024-05-27周

### A. 添加一个新的基础数据类型 int64 ✅ 

int 的数据范围有限, 为了扩大数据范围, 引入int64, 如其名, 64位数据. 在c语言中使用 long long 表示

1. 原先所有的 int 操作不便
2. 在 语法分析 运行虚拟机的过程中 添加 int64
3. 要系统性的分析 int 和 int64 在使用过程中的过中 显式转换&隐式转换
4. 能够跑通当前所有的测试用例

### B. 系统的规划 int64所需要的测试用例

1. fmt package
2. math operator
3. logical operator
4. relational operator
5. self incr/desc operator
6. 三目表达式

1. int64 数组
2. int64 类
3. int64 转string
4. int 转 int64
5. int64 转 double







### A. 实现新一代垃圾回收算法

#### 1. 重新规划一下 vm-execute 过程中 动态分配类型的流程逻辑

1.  heap_size() 返回值正确性
    1.  派生数据类型 类型分配计算的是否正确
2.  

string[] 数组的占用的内存是 capaity(array)* 8 这个需要再考究一下

#### 2. 关于RVM_Value 占用的内存优化

RVM_Value 中的字段 RVM_Value_Type 其实是个int, 占用了4字节, 这其实是一个很大的内存浪费,

需要调研一下, golang 中 interface的实现逻辑, python的实现逻辑

Golang 中 interface是如何实现的 https://halfrost.com/go_interface/


关于lua中, 如何用一个 struct 存放所有的数据类型, 也是 struct+(type&union)

```
/*
** Union of all Lua values
*/
typedef union Value {
    struct GCObject* gc; /* collectable objects */
    void*            p;  /* light userdata */
    lua_CFunction    f;  /* light C functions */
    lua_Integer      i;  /* integer numbers */
    lua_Number       n;  /* float numbers */
    /* not used, but may avoid warnings for uninitialized value */
    lu_byte ub;
} Value;


/*
** Tagged Values. This is the basic representation of values in Lua:
** an actual value plus a tag with its type.
*/

#define TValuefields \
    Value   value_;  \
    lu_byte tt_

typedef struct TValue {
    TValuefields;
} TValue;
```


#### 3. ring int 类型其实是 long long , 这样数据表达的范围更大


1. 将 RVM_Value 中的 int 不做更改, 还是32位
3. 在 RVM_Value 中 新添加一个 基础数据类型, int64, 然后对应的相应的虚拟机字节码都要 添加

然后还有一个棘手的问题就是 各种数据类型之间的转换, 隐式类型转换/显式类型转换, 还有各种地方的兼容性处理

3. array/class 中也要 支持 int64, 问题的复杂度一下就上升了 


这里还有一个关键的问题, 就是关于 len() capacity() 中 返回值是什么类型:
1. int
2. uint
3. int64

在这里, 不如比对一下golang是如何处理的: 
1. 使用 int 而不是 uint 的好处是这样无心智负担的写出这样的代码, 而不用担心程序崩溃
   
```
    // 倒序遍历数组
    for i := lenUInt(nums) - 1; i >= 0; i-- {
        fmt.Printf("i:%d -> num:%d\n", i, nums[i])
    }
```

2. 为什么使用 int, 而不是 int64

```

Go 语言的设计者 Rob Pike 在 Go 的邮件列表中曾经解释过这个问题。

len() 函数返回 int 而不是 int64 的原因主要有两个：

历史原因：Go 语言的前身是 Plan 9 的编程语言，Plan 9 中的 len() 函数也返回 int。在设计 Go 语言时，作者们决定保持这个惯例，以便更好地与 Plan 9 相兼容。
实际需求：在大多数情况下，int 类型足以表示容器的长度。即使在 32 位系统上，int 也可以表示非常大的数组或 slice。只有在非常特殊的情况下，例如处理非常大的数组或 slice 时，才需要使用 int64。
此外，使用 int 还有一个好处，那就是可以与其他语言更好地交互。例如，在 C 语言中，数组的索引通常是 int 类型的，而不是 int64。因此，如果 Go 语言的 len() 函数返回 int64，那么在与 C 语言交互时可能会出现问题。

总之，Go 语言的 len() 函数返回 int 是出于历史原因、实际需求和与其他语言的兼容性考虑的结果。
```





#### jvm 中的基本数据类型和对应的相关的字节码

```
Java 中有以下八种基础数据类型：

byte：8 位有符号整数，取值范围为 -128 到 127。
short：16 位有符号整数，取值范围为 -32768 到 32767。
int：32 位有符号整数，取值范围为 -2147483648 到 2147483647。
long：64 位有符号整数，取值范围为 -9223372036854775808 到 9223372036854775807 
float：32 位浮点数，取值范围为 -3.4e38 到 3.4e38。
double：64 位浮点数，取值范围为 -1.8e308 到 1.8e308。
boolean：布尔值，取值为 true 或 false。
char：16 位无符号整数，表示 Unicode 字符，取值范围为 0 到 65535。
这些基础数据类型是 Java 语言的基本组成部分，其他数据类型都是基于这些类型派生出来的。
```


```
Java 中的基础数据类型对应的 JVM 字节码如下：

byte：
加载：bload、baload
存储：bastore
操作：iinc、iadd、isub、imul、idiv、irem 等（使用 int 操作码，因为 byte 会被隐式转换为 int）


short：
加载：sload、saload
存储：sastore
操作：iinc、iadd、isub、imul、idiv、irem 等（使用 int 操作码，因为 short 会被隐式转换为 int）


int：
加载：iload、iaload
存储：iastore
操作：iinc、iadd、isub、imul、idiv、irem 等


long：
加载：lload、laload
存储：lastore
操作：linc、ladd、lsub、lmul、ldiv、lrem 等


float：
加载：fload、faload
存储：fastore
操作：finc、fadd、fsub、fmul、fdiv、frem 等


double：
加载：dload、daload
存储：dastore
操作：dinc、dadd、dsub、dmul、ddiv、drem 等


boolean：
加载：无特殊字节码，使用 iload 或 aload 加载 boolean 值
存储：无特殊字节码，使用 iastore 或 astore 存储 boolean 值
操作：使用 int 操作码，例如 iconst_0、iconst_1 等


char：
加载：aload、caload
存储：astore、castore
操作：使用 int 操作码，例如 iinc、iadd、isub 等（因为 char 会被隐式转换为 int）
需要注意的是，JVM 字节码并不是一一对应的，例如 int 操作码可以用于 byte、short 和 char 等类型的操作。


```


-----------------------------


## 2024-05-13周

### A. ring.hpp 中 Function 和 MethodMember 两个 struct融合为一个  ✅ 

Function MethodMember 派生自 FunctionTuple;

```cpp
#define FUNCTION_TUPLE_HEADER                                                    \
    std::string         source_file;       /*ring source file*/                  \
    unsigned int        start_line_number; /*start line no in ring source file*/ \
    unsigned int        end_line_number;   /*end   line no in ring source file*/ \
    Package*            package;           /*function's package*/                \
    RingFileStat*       ring_file_stat;    /*ring source file stat*/             \
    char*               identifier;                                              \
    unsigned int        parameter_list_size;                                     \
    Parameter*          parameter_list;                                          \
    unsigned int        return_list_size;                                        \
    FunctionReturnList* return_list;                                             \
    Block*              block;                                                   \
    FunctionTuple*      next;


struct FunctionTuple {
    FUNCTION_TUPLE_HEADER;
};

struct Function {
    FUNCTION_TUPLE_HEADER;

    unsigned int func_index;
    FunctionType type;
};

struct MethodMember {
    FUNCTION_TUPLE_HEADER;

    unsigned int index_of_class; // UPDATED_BY_FIX_AST
};
```



### B. return 语句 语义检查的 ✅ 

这个函数检查不过去, 需要优化

```
function pass_to_string(var string string_value) -> (string) {
    fmt::printf("string_value={}\n", string_value);
    return "#" + string_value;
}
```


-----------------------------


## 2024-05-06周

### A. variadic parameter 复杂测试用例 ✅ 

test/020-array-bool/func-variadic-parm-001.ring

test/020-array-bool/func-variadic-parm-002.ring


### B. 三目条件表达式 优化表达式的类型 ✅ 


a ? b : c; 
b 和 c 的表达式类型必须一致, 然后这个三元表达式的最终类型 就是 b c 表达式的类型.

./bin/ring run ./test/002-operator/condition-oper-001.ring

### C. ring rdb breakpoint 操作优化

1. break set 的时候, 行号如果是个空行, 怎么办

- 确定是最后一行
- 向后查找 第一个非空行 设置断点


2. break list 信息优化, 需要有以下信息

- 文件名
- 函数名
- 包名
- 行号
- 数量


### D. 完成 ./test/automated-testing-dump.sh 用于 测试 ring dump 命令 ✅ 


### E. CentOS Ubuntu 环境 coredump ✅ 

经定位, 是 linux g++ 有点问题 

```
char *dir;

std::string tmp = std::string(dir);

```

std::string(dir); 实现方式有问题.

应该直接这样即可:

```
char *dir;

std::string tmp = dir;
```


### F. 函数中 return 语句的合法性检查, 检查和函数定义中的函数返回值是否一致 TODO:


1. return 的语句中, 也不能 func()返回多个返回值 与单个返回值并存.
2. return 语句中, 支持 func()返回多个返回值, `递归调用场景`

method 中还不能进行强制检查 return 语句

这里基本实现了, 但是代码结构得重构一下.



-----------------------------


## 2024-04-22周



### A. BUG:ring package_unit 记录文件内容, 最后一行记录不了,  ✅ 


### B. CentOS Ubuntu 环境coredump ✅ 


### C. 可变参数类型 应用到 @derive函数中, 也就是如何访问可变参数类型 ✅ 

1. 语义检查: 将变量的类型变成数组, 如果变量的类型已经是数组了, 那就加一个维度
2. vm execute: 需要把参数转化成数组, 然后压入栈中, 然后后续通过数组的形式去访问可变参数
   - 可以对可变参数列表进行 for-range len() capacity() 操作


实现方式: 额外生成一个opcode, new_array_int. (当 var any... any_values, 需要对应那种字节码)

new_array_literal_bool 这个操作码 应该是在函数内部, 还是在函数外部

1. 如果要是放在函数外部, 实现起来不太优雅, 还要区分 @native @derive function, 因为 @native funciton 的便利性, 可以直接进行访问
2. 如果要是放在函数内部实现, 可能会破坏函数的字节码展示, 让user感觉多了好几个字节码
3. 如何去访问这个 临时的数组, 这个数组变量的identifier就是 parameter 的identifier


这里还有一个抉择, 就是关于 可变参数列表 转化成 数组,
这个操作 是单独用一个专门的字节码表示, 还是通过 在 init_derive_function_local_variable 中 实现(这样实现的话, 没有单独的字节码, 会在内部将列表转化为数组, 然后压入栈中, 这样需要在RVM_Function中需要详细记录参数的类型, 是不是可变参数, 根据可变参数进行详细的操作.)


### D. ring dump 中, 格式化 可变参数类型不正确 ✅ 




-----------------------------


## 2024-04-15周

### A. ring debugger 完善一下 help 提示信息  ✅ 

对标 https://ring.wiki 中doc


### B. ring debugger bt 展示的行数不太对,  ✅ 

当前行数正确, 
上一层栈的行数不正确


### C. 修正bug ✅ 

fmt::println() 参数为string的时候,行为不太正确, 需要通过 length来控制


### D. 语义分析, 函数调用, 参数数量不对

### E. 语义分析, 函数调用, 参数类型不对

需要区分 any 类型 和可变参数类型

例如 

```
@native
fn println(var any... any_value);

@native
fn printf(var string format, var any... any_value);
```



### F. 关于函数多返回值的使用方式 ✅ 

函数定义:

```
fn func_return_2_value() (bool, int) {

}
```


#### a. 应用到多项赋值的情况下

这样是可允许的, 因为 func_return_2_value() 的返回值是作为一个 整体 (bool, int), 函数调用表达式后边还有别的表达式, 所以 能够展开为 bool, int:

```
a, b = func_return_2_value();
```


但是这样是不被允许的, 因为 func_return_2_value() 的返回值是作为一个 整体 (bool, int), 函数调用表达式后边还有别的表达式, 所以不能够展开

```
a, b, c = func_return_2_value(), "str";
```


当然常规情况下, 这样是可以允许的:

```
a, b, c = true, 1, "aa";
```



#### b. 函数多返回值的 作为 下一个函数传递


这样是可允许的, 也是因为 func_return_2_value() 返回值作为一个整体, 可以继续展开:
```
    fn func_pass_2_value(var bool bool_value, var int int_value) {
    
    }

    func_pass_2_value(func_return_2_value());
```


这样是不可允许的, 因为 func_return_2_value() 后边还有别的表达式, 不能继续展开:
```
    fn func_pass_3_value(var bool bool_value, var int int_value, var string string_value) {
    
    }

    func_pass_3_value(func_return_2_value(), "str");
```



TODO: 关于展开
在这里, 多次取到一个名字叫做展开, 就是指 函数调用表达式后边还有别的表达式, 不能继续展开. 如何只是一个单独的表达式, 他自己是可以自己展开的
如何使用一种通用的方法去描述这种 能够展开的情况






-----------------------------


## 2024-04-08周


### A. ring debugger 实现 step-over step-into step-out ✅ 


### 命令: step over (命令缩写 n) ✅ 

- 执行被调用的函数或方法，而不进入其中。
- 当需要快速了解函数或方法的调用结果时使用。

### 命令: step into (命令缩写 i) ✅ 

- 进入被调用的函数或方法中，逐行执行代码。
- 当需要深入了解函数或方法的内部实现时使用。

### 命令: step out (命令缩写 o) ✅ 

- 退出当前执行的函数或方法，返回到调用它的位置。
- 当需要跳出嵌套的函数调用并继续执行主函数时使用。



### B. ring debugger 如何显示源代码文件的内容, 方便调试 ✅ 

命令: ```code list```

1. 显示当前位置 所在的 文件  ✅ 
2. 显示当前位置 所在的 行数  ✅ 
3. 显示当前位置 所在的 内容  ✅ 
4. 显示当前位置 前七行 后七行 总共15行内容.  ✅ 

实现: RingFileStat 记录源代码的元信息方便后续访问加载 ✅ 


### C. break points 可以保存到本地文件中, 可以方便下次加载

类似于 gdb 的 save breakpoints <file-name>

文件的格式可以参考一下 gdb是如何生成的

```
<breakpoint-type> <breakpoint-address> <breakpoint-enabled> <breakpoint-function> <breakpoint-line>
```


- <breakpoint-type> 是断点的类型，例如 breakpoint 或 watchpoint。
- <breakpoint-address> 是断点的地址。
- <breakpoint-enabled> 是一个布尔值，指示断点是否已启用。
- <breakpoint-function> 是断点设置处的函数名称（如果已知）。
- <breakpoint-line> 是断点设置处的行号（如果已知）。

breakpoint 0x100000f40 y main 10
watchpoint 0x100001000 y my_function 20




### D. ring程序终止之后, 不退出 rdb, 可以重新 run 当前的程序


这里可能比较难设计, 需要把当前运行的进程kill掉, 重新捕获命令后输入, 然后重新拉起任务(语法分析, 生成Opcode, 执行)


### D. ring debugger 设置断点的时候可以通过函数, 函数名字可以自动补全

break list 可以展示函数名字

break set function_name:line


### E. ring 中多个命令支持通过 && 一次输入, 方便快捷

-----------------------------


## 2024-04-01周


### A. 函数中 return了之后, 没有对返回值进行接收, 

或者一个 语句 `"bool"`; 栈空间会不太正确.


### B. 测试链式调用 ✅ 

1. 主要是要修正 function method 的 return_list  ✅ 
2. 测试 function method field各种相互组合的场景 ✅ 


例如:  ./test/008-class/class-052.ring:208


```
    job_1.printInfo();
    job_1.Job2.printInfo();
    job_1.Job2.Job3.printInfo();
    job_1.Job2.Job3.Job4.printInfo();
```


```
    job_1.returnSelf().Job2.Job3.returnSelf().Job4.printInfo();
```


```
copyJob4(
        copyJob3(
            copyJob2(
                copyJob1(job_1).Job2
                ).Job3
            ).Job4
        ).printInfo();
```



### C. duplicate字节码修改一下名字 ✅ 

duplicate 修改成 shallow_copy 更好理解,
与 deep_copy相对应


### D. class-object literal 中, 最后一个元素后边有没有逗号都可以 ✅ 



### E. 命令行交互式调试虚拟机工具


#### a. Stack详情 和 字节码详情 信息的展示做一个简单的重构 ✅ 

1. Stack详情: 可以详细展示数据的类型和数值
2. 字节码详情: 可以显示当前位置的前后20行字节码, 同时显示当前的所在的函数名称


#### b. printf标准输出 和 交互式的命令行展示信息 冲突 ✅ 

1. DEBUG_RVM_INTERACTIVE情况下: printf标准输出会重定向到文件 /tmp/ring-debug-vm.stdout.log
2. 交互式的命令行展示信息(Stack详情、字节码详情) 通过 stderr 的形式输出.



#### c. 目前只能一步一步的运行, 需要支持进入函数和不进入函数

Enter 一步一步
step:
next:
until:



### F. 针对函数调用专门优化语义报错 提示

1. 赋值操作 left 和 right 数量类型的是否正确一致 ✅ 
2. 参数的数量不一致
3. 参数的类型不一致
4. 返回值的数量不一致
5. 返回值的类型不一致

#### a.多项赋值和函数调用应该做一个限制

函数:
```
func test_0() {
}

func test_1() (bool) {
	return false
}

func test_2() (bool, int) {
	return false, 0
}

func main() {

    // 这种情况不应该允许
    // test_2() 的返回值是一个整体
	a, b, c := test_1(), test_2()

    // 这种情况不应该允许
    // test_0() 没有返回值
    a, b, c := test_0(), test_1(), test_1(), test_1()

    // 这种情况下应该允许
    // 函数的返回值只有一个
    a, b, c := test_1(), test_1(), test_1()
    a, b, c := test_1(), test_1(), false
	a, b, c := false, test_1(), test_1()

}
```

也就是多返回值不能作为多项赋值的右值

### G. 如果只有单独的表达式(push stack value) 但是没有 pop, 会造成栈空间的增长

```
1;
2;
"asefad";
test(); // 有返回值但是没有接手

```

白白浪费了一个stack空间.



### H. AST 路径的缩减



### I. fix_binary_math_expression()  fix_binary_relational_expression() 要做精细化的划分

把逻辑分开, 每层逻辑可以保持干净

-----------------------------


## 2024-03-25周


### A. 记录源代码 BUG

package_unit->line_offset_map 记录不了文件的最后一行的内容

package_unit 中记录了源代码文件, rdb在获取源代码内容的时候, 不太容易实现,
在这里, 要进行解耦合, 将记录源代码内容的数据结构, 从 PackageUnit中剥离出来, 
这样也能在 rdb 中获取源代码实现.


### B. fmt::sprintf(var string format, var any... any_value) -> string



### C. BUG: 返回值  ✅ 


```
method printInfo() {
    return fmt::printf("Job({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
}
```

这样写是会崩溃的, 因为本来没返回值, 这里却返回了, 需要强制检查返回值.


### D. 多项赋值 的深度 copy, 通过 RVM_CODE_DEEP_COPY 解决这个问题 ✅ 

#### a. 在这种情况下, 实际上是 对 数组元素class-object的deep-copy

```
for(i = 0; i<5; i++) {
    // TODO: 这样写是有bug, 
    global_job_array_0[i], global_job_array_0[9-i] = global_job_array_0[9-i], global_job_array_0[i];
}
```


#### b. 在这种情况下, 实际上是 对 数组元素class-object的shallow-copy

```
global_job_array_0[9-i].Int = 1;
```




### E. 添加一个新的字节码: RVM_CODE_DEEP_COPY  ✅ 

RVM_CODE_DEEP_COPY 是对栈上的数据做深度copy.
RVM_CODE_SHALLOW_COPY 是对栈上的数据做浅copy.


以后需要这样规划:
默认字节码是对栈上的数据做shallow-copy
但是对于 deep-copy的场景(赋值、函数传递), 需要显式生成一个字节码: RVM_CODE_DEEP_COPY , 专门处理数据的deep-copy





### F. 完善测试用例 ✅ 

#### a.  ✅ 

数组元素为 class-obect
通过索引访问数组元素并直接调用method
`global_job_array_0[i].printInfo();`


#### b. ✅ 

数组元素为 class-obect
通过for-range访问数组元素并直接调用method
```
for(local_job_value in range global_job_array_0) {
    local_job_value.printInfo();
}
```



#### c. ✅ 

数组的元素为 class-obect
Usage: 将数组内的所有的对象顺序反转
Code:
```
global_job_array_0[i], global_job_array_0[9-i] = global_job_array_0[9-i], global_job_array_0[i];
for(i = 0; i<5; i++) {
    global_job_array_0[i], global_job_array_0[9-i] = global_job_array_0[9-i], global_job_array_0[i];
}
```


#### d. ✅ 


数组的元素为 class-obect, 数组为二维数组
直接通过索引交换元素, 只不过是一次交换一整列
```
global_job_array_0 = new Job[2,2];
global_job_array_0[0], global_job_array_0[1] = global_job_array_0[1], global_job_array_0[0];
```


#### e. ✅ 

class有4级嵌套
测试对象嵌套的初始化
测试嵌套访问method
```
    job_1.printInfo();
    job_1.Job2.printInfo();
    job_1.Job2.Job3.printInfo();
    job_1.Job2.Job3.Job4.printInfo();
```


-----------------------------



## 2024-03-18周


### A. 设计Ring命令行交互式编程


设计: 
1. `ring rdb <filename>` 使用交互式调试功能
2. 在交互式中, 使用 clipp 解析命令行参数, 以后 ring命令行也是用 clipp解析
3. 进入交互式debugger之后, 会在main函数的入口处停止, 等待输入和调试

rdb命令:

1. global: 打印全局变量
2. local: 打印局部变量
1. cont/c: 继续执行, 直到遇到一个break-points
2. bt: 打印堆栈
3. clear: 清屏
4. quit/q: 退出 ctrl-c
5. code list: 打印当前行代码, 当前位置前后12行代码
6.  step-over step-into step-out

断点命令相关:
1. break set   <line-number>  放置断点, 会获得一个breakpointID
2. break clear <line-number>  清除断点
3. break list                 列出断点
4. break clear               清除所有断点


最后显示: 
```
The program '/Users/lizhenhu/Desktop/Ring/bin/ring' has exited with code 0 (0x00000000).
```



```
treminal> ./bin/ring rdb ./test/test.ring
ring-v0.2.14-beta Copyright (C) 2021-2023 ring.wiki, ZhenhuLi
Start Ring Debugger...

Input file: ./test/test.ring

rdb> break 8
Breakpoint 1 at: file test.ring:8

rdb> break 9
Breakpoint 1 at: file test.ring:9

rdb> break 10
Breakpoint 1 at: file test.ring:10

rdb> info break
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00005555555551b1 in main() at test.ring:8
2       breakpoint     keep y   0x00005555555551dc in main() at test.ring:9
3       breakpoint     keep y   0x0000555555555207 in main() at test.ring:10


rdb> cont
Continuing.
Breakpoint 1, main () at test.cpp:8
8           std::cout << "1" << std::endl;


rdb> cont
Continuing.
1

Breakpoint 2, main () at test.cpp:9
9           std::cout << "2" << std::endl;

rdb> c
Continuing.
2

Breakpoint 3, main () at test.cpp:10
10          std::cout << "3" << std::endl;







rdb> bt
#0  test4 () at test.cpp:9
#1  0x00005555555551da in test3 () at test.cpp:13
#2  0x00005555555551ea in test2 () at test.cpp:17
#3  0x00005555555551fa in test1 () at test.cpp:22
#4  0x00005555555552e1 in main () at test.cpp:31
```



-----------------------------




## 2024-03-11周

### A. 调研交互式编程

1. 类似于 python lua的交互式编程, 通过每一行的输入, 并执行, 同时得出执行结果, 这个相对复杂
2. ringc的交互式编程, 没输入一行内容, 就实时翻译编译后的字节码, 这个相对简单一点


调研 lua的交互式编程的实现.

repl: real-eval-print loop  https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop


使用 linenoise读入一行, 编译, 执行, 然后输出结果


设计:
1. ring repl
2. 进入之后, 打印 ring的版本号, 提示开始交互式编程
3. 前缀为 > 
4. 能够根据输入的关键字自动提示
5. 能够记录历史
6. 能够存储到本地目录
7. 定义默认导入的package
6. 快捷键: ctrl+c 退出, enter 下一行, shift+enter 开启新的block, 并自动开始运行



### B. 调研交互式调试工具

调研一下 python-debugger 和 lua-debugger

1. lua

debug.debug()    进入交互式的debug
debug.getlocal() 获取局部变量
debug.setlocal() 设置局部变量

test1.lua
```

function foo()
    print("function foo\n")
    local a = 10
    local b = 20
    local c = a + b
    local d = "hello world"
    local e
    printLocalVariables()
    initLocalVariables()
    printLocalVariables()
end

function printLocalVariables()
    local level = 2
    local localVarIndex = 1
    local name, value

    print("printLocalVariables--------------------")
    while true do
        name, value = debug.getlocal(level, localVarIndex)
        if not name then break end
        print("identifier:", name, "value:", value)
        localVarIndex = localVarIndex + 1
    end
end

function initLocalVariables()
    local level = 2
    local localVarIndex = 1
    local name, value

    print("initLocalVariables--------------------")
    while true do
        name = debug.setlocal(level, localVarIndex,
                              "local variable " .. tostring(localVarIndex))
        if not name then break end
        localVarIndex = localVarIndex + 1
    end
end

-- 通过 debug.getlocal() 获取局部变量, debug.setlocal() 设置局部变量
foo()


```


2. python的 python -m pdb test.py, 调用一个交互式的debugger




-----------------------------

## 2024-03-04周 


### A. BUG: ring dump  ✅ 

如何变量是 class Job, dump的时候显示`Job`, 而不是显示`class`


### B. TEST: 类 通过函数传递, 通过函数返回

bool array
int array
double array
string array
class-object array  ✅ 


### C. TEST: 类数组 通过函数传递, 通过函数返回

bool array
int array
double array
string array
class-object array  ✅ 


### D. TEST: for-range 测试多维数组

bool array
int array
double array
string array
class-object array  ✅ 


### E. 局部变量初始化 ✅ 


### F. 多维数组的 push pop


### G. 重新设计并验证gc

1. gc 对于 String
    string 全局变量, 局部变量, 变量返回值, 变量函数的传递
    to_string() 操作
    string_literal
    
2. gc 对于 class-object
3. gc 对于 array 


heap_size 的算法
gc的正确性



### H. 重新 设计 fmt::printf函数 ✅ 


rust的格式化输出 https://course.rs/basic/formatted-output.html

看这个测试用例:
test/061-std-package-fmt/fmt-005.ring

通过 {} 作为占位符，来格式化输出


### I. 设计 fmt::println 函数 ✅ 



-----------------------------

## 2024-02-26周 

### A. 转义字符的支持 ✅ 


### B. 多行字符串的支持 ✅ 

python 多行字符串的支持

```python
str1 = '''Le vent se lève, il faut tenter de vivre. 
起风了，唯有努力生存。
（纵有疾风起，人生不言弃。）'''
```



ring 采用和golang一样的逻辑

```ring
str1 = `multi string 
literal`
```

1. 在多行字符串中不支持转义,
2. 唯一支持的转义是 \` 用于和 多行字符串的边界区分



### C. 测试4层 class的嵌套定义 ✅



### D. 支持 对象递归的初始化 ✅


测试  ✅ 
```ring
job_1 = Job1{
        Bool:   false,
        Int:    1,
        Double: 1.1,
        String: "1.1",
        Job2:   Job2{
            Bool:   true,
            Int:    2,
            Double: 2.2,
            String: "2.2"
        }
    };
```

也可以这样:
测试  ✅ 
```ring

job_2 = Job2{
        Bool:   true,
        Int:    2,
        Double: 2.2,
        String: "2.2"
    };

job_1 = Job1{
        Bool:   false,
        Int:    1,
        Double: 1.1,
        String: "1.1",
        Job2:   job_2
    };
```




### F. 测试 字符串比较的时候, 要转化成 ne_string ✅ 


```ring

var string[,] global_string_array_0;

if(global_string_array_0[i,j] != to_string(num)){
    fmt::println_string("test failed");
} 

```


### G. 引入多行字符串之后, 源代码的函数可能不太正确 ✅ 


测试源代码中包含:
1. block comment
2. block string

源代码的行数是否正确.


### H. 测试字符串常量的长度 超过 1024 ✅ 

-----------------------------

## 2024-02-20周 

### A. class method

测试
method 调用 method , 
method 调用 function



### C. 支持括号运算符

通过括号运算符可以明确运算的优先级



-----------------------------




## 2024-02-05周 


### A. 类中field为class的情况下要初始化默认值   ✅ 

### B. 函数调用中，局部变量的数量写死为20，如何处理一下

1. function 测试通过   ✅ 
2. method 测试通过 ✅ 


### C. 数组常量

目前已经支持了 一维数组常量 

```
int[]{1,2,3};
```


1. 需要支持二维数组常量  测试 ✅ 

```
int[,]{
    int[]{1,2,3},
    int[]{1,2,3},
    int[]{1,2,3}
};
```


2. 三维数组常量  测试 ✅ 

```
int[,,]{
    int[,]{
        int[]{1,2,3},
        int[]{1,2,3},
        int[]{1,2,3}
    },
    int[,]{
        int[]{1,2,3},
        int[]{1,2,3},
        int[]{1,2,3}
    },
    int[,]{
        int[]{1,2,3},
        int[]{1,2,3},
        int[]{1,2,3}
    }
}
```



3. 多维数组常量  ✅ 


4. 当然这个也可以是个嵌套的，所以说通过单纯的语法分析是远远不够的，还需要语义分析

```
array_0 = int[]{1,2,3}

int[,]{
    array_0,
    array_0,
}
```


### D. 关于多维数组通过 composite literal 赋值, 数组中的元素为 class object

1. 已经支持了 class-object 的 composite literal

```ring
Job {
    Bool: true,
    Int:  1,
    Double: 1.1
}
```


1. 需要支持 一维数组通过 class-object 的 composite literal 进行赋值  ✅ 

```ring
Job[] {
    Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
    Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
    Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
}
```



2. 需要支持 二维数组通过 class-object 的 composite literal 进行赋值  ✅ 

```
Job[,] {
    Job[] {
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
    },
    Job[] {
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
        Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
    }
}
```

3. 需要支持 三维数组通过 class-object 的 composite literal 进行赋值  ✅ 

```
Job[,,]{
    Job[,] {
        Job[] {
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
        },
        Job[] {
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
        }
    },
    Job[,] {
        Job[] {
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
        },
        Job[] {
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"},
            Job{Bool: true,  Int: 0, Double: 0.0, String: "0.0"}
        }
    }
}

```

4. 当然，这个也可以是个嵌套的，也可以这样，所以说通过单纯的语法分析是远远不够的，还需要语义分析

```ring

Job[,] {
    Job[]{job_value, job_value},
    Job[]{job_value, job_value}
}
```





### E. 在定义数组常量和class-object常量时，最后一个元素后边有没有逗号都可以  ✅



## 2024-01-29周 


### *A. Makefile检测 flex bison 的版本是否符合要求*  ✅ 

make echo  ✅ 
make help  ✅ 
make check: 检查源代码编译依赖  ✅ 

### *B. 重新设计并验证gc*


### *C. 测试 ring dump*


### *D. 完善 class-object literal*  ✅ 


1. new class-object literal的时候，Field的初始化顺序无需跟Class中定义的顺序一致
   
```
job_0 = Job{
        Runner: global_runner_value_0,
        Name: "1.1",
        Score: 1.1,
        JobID: 1, 
        Running: false
    };
```

### *E. 支持  class-object 多维数组*  ✅ 



### *F. 测试: 传递 string class-object array 到底是 值传递还是传递指针*


#### 多赋值 支持 array 或者是 member.field  ✅ 

./test/021-array-int/sort.ring 编译不过去, 
```
    for(i=0; i+1 < len(global_int_array_0); i+=2) {
        global_int_array_0[i], global_int_array_0[i+1] = global_int_array_0[i+1], global_int_array_0[i];
    }
```


#### 通过index访问array, index可以是个复杂表达式  ✅ 

更新 bison语法, 测试通过  ✅ 
 ./test/021-array-int/sort-2.ring 


#### 数组元素的自增运算 ✅ 

自增  ✅ 
自减  未测试 ⭕️ 

./test/021-array-int/sort-3.ring:23:36: 

global_int_array_0[j]++;

这个是编译不过去的


支持  job_value.ID++;



### *G. 区分左值和右值*  ✅ 


```
左值（L-value）是指可以放在赋值运算符左边的表达式，它代表一个具体的内存位置。左值可以被取地址、被修改、被引用，可以作为函数的参数或返回值。例如，变量、数组元素、对象成员、表达式的结果等都是左值。

右值（R-value）是指不能放在赋值运算符左边的表达式，它代表一个临时的值或表达式的结果。右值不能被取地址、不能被修改，可以被移动（move）或复制（copy）。例如，常量、字面量、临时变量、表达式的结果等都是右值。

```

这是不合法的：
```
func return_array() TreeNode {
	return TreeNode{}
}

func main() {
	return_array().Val++
}
```

这是合法的：

```
func return_array() *TreeNode {
	return &TreeNode{}
}

func main() {
	return_array().Val++
}
```


这是合法的：

```
func return_array() []TreeNode {
	return []TreeNode{}
}

func main() {
	return_array()[0].Val++
}
```


说白了，左值和右值，还得通过语义分析来判断


### *H. 自增自减运算符*

1. 没有支持前缀自增自减的运算语句，也就是不允许 ++a。
2. 运算符 ++ 和 -- 只能作为一个语句来使用，不可以作为表达式被赋值给其它的变量使用。

可以删除 generate中的 need_duplicate ✅ 


1. 自增自减运算符 运用到array上 ✅ 

2. 自增自减运算符 运用到class-field上 ✅ 


-----------------------------

## 2024-01-22周


### *A. 重构vm 中 string class-object array* ✅ 




### B. class 中支持存放array ✅ 

class中的field支持：
bool
int
double
string
class[]
bool[]
int[]
double[]
string[]
class[]



### C. 所有的没有处理的错误报错，都要添加上 ring_error_report ✅ 


### D. 如果一个数组是三维，可以访问第二维，第二维其实是个数组 ✅ 

```
    global_bool_array_0 = new bool[a,b,c,d,e,f,g,h];

    fmt::println_int(len(global_bool_array_0));
    fmt::println_int(len(global_bool_array_0[0]));
    fmt::println_int(len(global_bool_array_0[0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0,0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0,0,0,0]));
	fmt::println_int(len(global_bool_array_0[0,0,0,0,0,0,0]));
```


### E. 要在语义检查中强制检查变量的类型

变量的定义
变量的赋值
变量的使用

函数参数的定义
函数参数的传递

函数返回值的定义
函数返回值的return
函数返回值的接收
函数返回值的数量



如何比对两个变量是否一致， TypeSpecifier, 递归比对。涉及到
- 递归比对
- field的比对
- array中value的比对
- 函数形参/实参的比对


### F. 多维数组 的 typeof 和 ring dump

1. typeof(多维数组)

多维数组 为 bool/int/double/string的时候，没有问题 ✅ 



2. ring dump 多维数组


### G. class的嵌套定义与引用

在语法上要支持 job_0.Runner.Valid 多个member的调用

1. 支持递归访问field `job_0.Runner.Valid` ✅
2. 支持递归访问method `job_0.Runner.Doit()`  代测试⭕️
3. 如何检测class的递归定义（所以得引入指针的概念）


-----------------------------

## 2024-01-08周


### A. 设计支持多维数组


1. 语法层面的设计  ✅ 
2. 用户如何命名多维数组  ✅ 
3. 用户如何创建多维数组  ✅ 
4. 用户如何访问多维数组  ✅ 


1. TypeSpecifier如何组织多维数组
2. deep copy TypeSpecifier 如何copy多维数组
3. generate的时候需要支持多维数组

4. execute的时候需要支持多维数组

测试通过:
1. 多维数组 bool/int/double/string
   1. 创建 ✅ 
   2. 赋值 ✅ 
   3. 访问 ✅ 
   4. 通过 for 访问 ✅ 
2. 多维数组 支持 class-object


需要支持

1. for-range引用到多维数组
2. 多维数组 literal 初始化
3. 对多维数组直接进行 fmt::printf()
4. ring dump 展示是否为多维数组


```
    global_int_array_0 = new int[2,4];

    fmt::println_int(len(global_int_array_0));
    fmt::println_int(len(global_int_array_0[1]));
```




如果对于一个二维数组 a[][], a[1] 其实是个一维数组, 还需要完善一下语义检查.

var int[] a; // 一维数组
var int[,] a; // 二维数组
var int[,,] a; // 三维数组

new int[10];    // 创建一维数组
new int[10,20]; // 创建二维数组 10*20
new int[10,20,30]; // 创建三维数组 10\*20\*30

a[1,2,3]; // 访问数组


如何 printf一个一维数组.

dimension: 纬度
size: 数组的大小

a[1,2,4] 纬度为3, 大小分别为 1, 2, 4 


new 多维数组的时候, size只能放int常量, 也就是还不能完全动态分配
a[1,2,4] 访问的时候, 可以放非int常量



### 应该把 RVM_String 放在基础类型里边

-----------------------------

## 2024-01-01周

### *A. 优化: ring dump*

ring dump 支持 dump class的详情

class:
1. class 名称 ✅ 
2. class 对应的源代码文件,行数  ✅ 
3. field 数量/详情 ✅ 
4. method数量/详情 ✅ 
5. method局部变量的数量/详情 ✅ 
6. method返回值的数量  ✅ 


function/method:
1. 函数参数的数量/详情 ✅
2. 局部变量的数量/详情 ✅
3. 返回值的数量/详情


global 全局变量 ✅ 

constant 常量 ✅

数组变量 ✅ 




### *B. 类 method*


1. 定义 method的时候支持 传递参数 ✅ 
2. 调用 method的时候支持 传递参数 ✅ 
3. method中支持自定义 local variable ✅ 
4. method支持返回值 ✅ 
5. method 参数 + 局部变量的数量 不能超过 254. (self 占用一个)
6. function 参数 + 局部变量的数量 不能超过 255.
7. return list 也得有数量限制, 不能超过 255.
8. class 中 method 的数量不能超过 255 ✅ 
9. class 中 field 的数量不能超过 255 ✅ 



### *C. error-report的时候添加 location* ✅

bison  在报语法错误的时候, 需要将 TOKEN_XXX  转化成对应的字符, 方便用户查看.


ring 编译报错的时候添加一个 debug 控制 报错所在的位置,  __FILE__ __LINE__ 方便调试



### *E. print_call_stack 支持 打印 调用method的时栈信息* ✅


```

test case 1
0000$ring!Job.PrintInfo(var bool, var int, var double)
    ./test/060-std-package-debug/debug-stack-005.ring:16
0001$ring!main()
    ./test/060-std-package-debug/debug-stack-005.ring:31

test case 2
0000$ring!PrintInfo(var bool, var int, var double)
    ./test/060-std-package-debug/debug-stack-005.ring:25
0001$ring!main()
    ./test/060-std-package-debug/debug-stack-005.ring:31
```

Job.PrintInfo: 表示调用 method
PrintInfo: 表示调用 function


### *F. 需要写一个自动化工具, 编写测试用例一览图, 说明每个测试用例覆盖的场景* ✅

1. 在 测试用例的文件中, 需要用注释写明测试用途, `// TestDetail:` 前缀表示,
2. 在 `make testall` 的时候, 可以导出:
   1. 测试时间
   2. 测试数量
   3. 测试模块
   4. 测试文件
   5. 测试内容
   6. 是否通过


3. 参见 `test/automated-testing.sh`:

```
# 输出ring-测试用例表
# 是否输出测试用例表: 0/1
IS_EXPORT_TEST_DETAIL_SUMMARY=0 
# 输出测试用例表文件
TEST_DETAIL_SUMMARY="./test/ring-测试用例表.md"
```


### *G. 研究一下 bison的安装方法*

```
./configure

make && make install
```


bison 安装到指定位置之后, 需要动态设置 src/Makefile $(Bison) $(Flex)




### *H. class 中存放string* ✅




-----------------------------

## 2023-12-15周


### *A. 设计: 报错, 指示的列数不太对*


1. import package 重复 ✅



### *B. 设计: 编译错误如何自动化提示*

要继续好好研究一下 bison, bison的很多特性自己还不是特别熟悉.


1. 遇到错误如何定位到下一行, 进行错误恢复, 能够一次报出多个编译错误.
2. 编译报错的错误文案需要重新定义一下.




### *C. 设计: 类*

1. 调用 class method
2. support `self` variable in class-method.

self 不是个关键字, self可以是任何变量名, 但是在 method中比较特殊.

需要在 method 的中 添加一个隐藏的变量, self

在 method中, 只能通过 self.<field> 去访问成员变量

对象调用方法 ✅


目前method: (后续统一处理)
- 只能使用 self关键字
- 函数参数 只能为 void
- 函数返回值 只能为 void
- 不能定义局部变量
  
当前只能在 main-package 中定义



### *D. 重构: 调整相关API* ✅

所有copy函数的 dst src 都要调整成 std-api的那种形式


所有的 melloc 都调整一下格式, sizeof() 在前面, count在后面, 要注意多行折叠.



-----------------------------

## 2023-12-18周

### *A. 设计: native function 打印当前的函数调用栈*


debug::print_call_stack() 

展示当前的函数调用栈:
- 调用函数 ✅
- 调用函数所在的行数 ✅
- 调用函数对应的源码文件, 源文件行数 ✅



### *B. 如何一个源代码文件中超过10w行代码, 报错, 需要调整目录结构*

### *C. 调整 Script 脚本 用于 build, test*

-----------------------------

## 2023-12-11周

### *A. 设计: 函数调用 RVM_CallInfo 使用链表组织起来* ✅


### *B. 设计: 规划Ring 前端&后端的解耦*

目前在 RVM 执行字节码的过程中, 引用到了 AST 相关的数据, 耦合严重, 不利于后续的开发.

所以将 AST 中所有的数据结构都要进行销毁, 推进前端和后端的解耦, 为后续导出字节码奠定基础.

主要销毁的包括: 语句, 表达式, 函数, 类, 变量, 包

需要copy的:
- TypeSpecifier: 在rvm中, 根据变量的类型进行初始化 ✅
- RVM_Class:   rvm中, class-object 的初始化 ✅


### *C. 设计: 函数调用重新设计一下*


aragument_num
push_func
invoke_func 

这几个设计的有点过于繁琐了 ⭕️



CALL_INFO_SIZE_V2 需要删除掉 ⭕️


### *C. 设计: native function 打印当前的函数调用栈*


debug::print_call_stack() 

展示当前的函数调用栈:
- 调用函数 ✅



给 Function  RVM_Function 加一个字段, 就是所在的源文件名称, 和源码对应的行数

展示字节码的时候:
- 字节码 ✅
- 操作数: 分开区别 1BYTE 2BYTE 3BYTE ✅


### *D. 如何设计一个 native函数去 检测 ring当前的编译错误*

检验错误码 ⭕️
检验错误信息 ⭕️
检验错误的数量 ⭕️


### *E. ring dump 输出编译的字节码详情* 

ring dump <input-file>

1. 只输出 main package的编译情况  ✅
2. 输出 package, function, bytecode, 操作数, 对应的源代码, 函数参数的数量, 函数局部变量的数量  ✅
3. 输出 class-definition  ✅
4. ring dump 自动化测试如何设计 ✅



### *F. 将ring.wiki相关前端依赖存在cos, 统一使用cos提供服务*


### *G. MacOS/Ubuntu/Centos 都要编译运行测试* ✅

1. MacOS ✅
2. Ubuntu ✅
3. CentOS ✅



-----------------------------

## 2023-11-27周

### *A. 设计: 类的数组*

1. `类-数组` 类的成员支持 更新value

```
        global_job_array_0[index].Running = true;

```

这里其实有一个隐喻, 是取出 global_job_array_0[index] 的指针, 然后进行更新值


-----------------------------

## 2023-11-20周

### *A. 设计: vmcode 需要记录源代码的行数* ✅

#### 1. 要保证记录的准确性

#### 2. 能够输出源代码和字节码的映射


### *B. 设计: 类中放string*

### *C. 设计: 类的数组*

1. 声明`类` & 声明`类-数组` ✅

```
    typedef class Job {
        field bool    Running;
        field int     JobID;
        field double  Score;
    }

    var Job[] global_job_array_0;
```

2. `new`操作符为`类-数组`分配空间 ✅

```
    global_job_array_0 = new Job[200];
```


3. 通过整数索引访问数组内的元素 ✅

```
    fmt::println_bool(global_job_array_0[0].Running);
    fmt::println_int(global_job_array_0[0].JobID);
    fmt::println_double(global_job_array_0[0].Score);
```

4. for 循环访问数组内的类成员变量 ✅

```
    var int index = 0;
    for(index = 0; index < 200; index = index + 1) {
        fmt::println_bool(global_job_array_0[index].Running);
        fmt::println_int(global_job_array_0[index].JobID);
        fmt::println_double(global_job_array_0[index].Score);
    }
```


5. for-range 支持`类-数组`   ✅ 

```
    var Job job_value;

    for(job_value in range global_job_array_0) {
        fmt::println_bool(job_value.Running);
        fmt::println_int(job_value.JobID);
        fmt::println_double(job_value.Score);
    }
```

6. push 支持`类-数组`    ✅ 

```
    var Job global_job_value_0;
    global_job_value_0 = Job{
       Running: true,
       JobID: 200, 
       Score: 200.1
    };

    // push 一个 Job 变量
    push(global_job_array_0, global_job_value_0);

    // push 一个 Job 常量
    push(global_job_array_0, Job{
        Running: false,
        JobID: 201, 
        Score: 201.14
    });
```

7. pop 支持`类-数组`   ✅ 

```
    var Job global_job_value_0;

    // 从 global_job_array_0 的尾部 pop, 并获取尾部值
    global_job_value_0 = pop(global_job_array_0);

    fmt::println_bool(global_job_value_0.Running);
    fmt::println_int(global_job_value_0.JobID);
    fmt::println_double(global_job_value_0.Score);

```

8. 通过 索引为 数组内的类元素赋值  ✅ 

```
    // 通过 Job 常量 直接赋值
    global_job_array_0[0]  = Job{
        Running:  false,
        JobID:    0,
        Score:    0.0
    };

    // 通过 Job 变量 进行赋值
    global_job_value_0  = Job{
        Running:  true,
        JobID:    3,
        Score:    33.33
    };
    global_job_array_0[3] = global_job_value_0;
```

9. 函数参数/返回值 为类数组 ✅ 

函数参数变量传递

函数返回值传递





### *D. 优化: fix_ast*

fix AST 的过程中需要对每个 expression 的 conver_type 依次进行修正

convert_type 在 generate完成之后, 可以统一销毁

1. 要解决多级嵌套的问题

```
global_class_array_0[0].Running
```


### *E. 设计: 内存池* ✅

是否有必要要考虑设计内存池, 这样在分配动态内存的时候, 直接从内存池中去取, 
能够减少内存碎片, 减少分配的速度, 同时还能检查 RVM 垃圾回收是否正常, 是否有内存泄漏

现在没有内存池的设计就是: 分配内存比较随意, 没有统一在一起, 而且查看内存分配的空间不方便, 比较粗放.

但是内存池会不会拖慢内存的分配、释放速度, 得好好测试一下, 开启内存池/未开始内存池.

所以这个功能还是急需的.

大三的时候设计过一款内存池, 所以要看看是否能够复用一下.



-----------------------------


## 2023-11-13周

### *A. 设计: import时, 各种异常情况都需要check, 人性化的报错*

#### 1. 用户导入包的顺序是可以任意的
#### 2. 用户导入的包不存在
#### 3. 用户导入的包不合法
#### 4. 用户导入的包重复



### *B. 设计: 数组/字符串的动态增长* ✅

#### 1. 如何往数组中添加元素, push 用来动态增长

```
push(array_value, 1);

value = pop(array_value);
```


注意: 
push的时候, 必须要保证 array_value 已经被new过了,  

`array_value = new int[100];`

这里看看后续是不是需要优化


#### 2. pop 用来删除最后一个元素, 删除元素之后获得最后一个元素

```
value = pop(array_value);
```

### *C. 调研: JVM switch 语句* 

### *D. 设计: 数组按照2倍增长*  ✅

bug:

```
global_bool_array_0 = new bool[0];

push(global_bool_array_0, true);

```

这样动态增长的时候, capacity 算的有问题, 因为*2, 所以一直是0


### *E. 设计: VM, 往vm中push value的时候, 没有pop的时候, 函数返回会报错, 需要对栈上的空间进行回收, call_info 的问题*

### *F. 设计: 数组+对象* ✅

### *G. 设计: to_string* ✅

```
string_value = to_string(bool_value);
string_value = to_string(int_value);
string_value = to_string(double_value);
```

添加新的字节码:
RVM_CODE_BOOL_2_STRING
RVM_CODE_INT_2_STRING
RVM_CODE_DOUBLE_2_STRING


### *H. 设计 fmt::println() fmt::printf()*

### *G. 009-package 测试用例继续拆分一下* ✅


-----------------------------



## 2023-11-06周




### *B. 设计: 数组/字符串 如何获得数组的长度&容量*  ✅


添加四个专用的字节码，分别用于获取数组/字符串的length&capacity：

```
RVM_CODE_PUSH_ARRAY_LEN
RVM_CODE_PUSH_ARRAY_CAPACITY
RVM_CODE_PUSH_STRING_LEN
RVM_CODE_PUSH_STRING_CAPACITY
```

Usage:    
```ring
len(string_variable)
capacity(string_variable)
len(array_variable)
capacity(array_variable)
```

e.g.

```ring
var string local_string_value_0;

fmt::println_int(len(local_string_value_0));
fmt::println_int(capacity(local_string_value_0));


var bool[] local_bool_array_0;

fmt::println_int(len(local_bool_array_0));
fmt::println_int(capacity(local_bool_array_0));
```


### *C. 设计: 数组/字符串的越界访问*  ✅

1. 以下这几个函数在vm调用的时候，如果超过数组的边界，应该抛出异常，在这里返回一个错误码：RUNTIME_ERR_OUT_OF_ARRAY_RANGE

- rvm_array_get_bool
- rvm_array_get_int
- rvm_array_get_double
- rvm_array_get_string

- rvm_array_set_bool
- rvm_array_set_int
- rvm_array_set_double
- rvm_array_set_string

2. 需要在访问数组的时候做一下处理，报错要人性化，能够打印出当时的调用栈信息


### *D. 设计: 数组/字符串的 for range 访问*  ✅

1. 支持了 bool[], int[], double[], string[]  的range操作

2. 语法示例:


Usage:
```
var bool[] bool_array_0 = bool[]{false, true, false};

var int index;
var bool value;
for(value = range bool_array_0) {
    fmt::println_bool(value);
}
```

Output:
```
false
true
false
```

3. VM层面添加几个专用的字节码

```
RVM_CODE_FOR_RANGE_ARRAY_BOOL
RVM_CODE_FOR_RANGE_ARRAY_INT
RVM_CODE_FOR_RANGE_ARRAY_DOUBLE
RVM_CODE_FOR_RANGE_ARRAY_STRING
RVM_CODE_FOR_RANGE_ARRAY_OBJECT
RVM_CODE_FOR_RANGE_STRING
RVM_CODE_FOR_RANGE
RVM_CODE_FOR_RANGE_FINISH
```

### *E. 支持给数组中的元素赋值*  ✅

1. 支持对 bool[], int[], double[], string[] 中的元素进行复制

2. 语法示例:


Usage:
```
var bool[] global_bool_array_0  = new bool[20];

global_bool_array_0[0] = true;
```

---------------------


## 2023-10-30周

   

1. 修正一下 class object 相关的gc  ✅
2. 通过函数传递 class object
   1. 可以通过函数传递 但是是 浅copy,  ✅
   2. 需要优化成 深度 copy
3. array & class object
4. array & string
   1. 命名array-string: var string[] string_array; ✅
   2. 分配空间: string_array = new string[10]; ✅
   3. 分配空间初始化: string_array = string[]{"a"}; ✅
   4. 访问array-string: fmt::println_string(string_array[0]); ✅
   5. gc heap_size 计算的不对
   6. 还没有 check gc是否正常
   7. 内存分布还得好好重构一下
5. 数组访问 要panic报错 index越界
6. 支持 for range
7. 优化语义检查
8. string的动态增长
9. array的动态增长
10. 有了 var 之后, 是不是让 匿名函数变得复杂了
11. ast 中 每个 expression 都要 fix conver_type (TypeSpecifier*)
12. 修正 vm execute 过程中 写死的 local_variable_count = 20;

13. class-object 的初始化 暂时不用 constructor函数, 使用类似于Golang的 列表初始化

    ```
    var Job job_0 = Job{
       Running: false,
       JobID: 0,
       Score: 0.0
    };
    ```


遗留问题:
    0. 简单测试没有问题  ✅
    1. 初始化列表的数量 必须要跟 class成员变量的数量 一致
    2. 初始化列表的顺序 必须要跟 class成员变量的顺序 一致

class 内部的 constructor 函数是不是要废弃
constructor 应该作为默认的初始化函数

```
var Job job_0(); // 这里就是去调用 constructor函数
```


---------------------


## 2023-10-23周

1. 如何判断rvm上object是否发生了深度copy, 同时尽量不要通过在rvm中debug print的方式  ✅
> 通过 fmt::println_pointer 来打印实际存储数据的地址
> 
2. 重构 heap 内存分配 ✅
3. 通过工具 可以将 Ring 虚拟机指令集生成一个 markdown表格 ✅
> make tool_gen_vmcode_doc && ./bin/tool_gen_vmcode_doc
4. 函数 返回 array string object 去完成深度copy ✅
5. 函数可以返回 数组  ✅
6. 可以传递数组 给 函数  ✅
7. bug 数组不能赋值
8.  使用 bool 数组 (new bool[10], bool[]{})  ✅
> Usage:
> 
> var bool[] bool_array_0 = new bool[10];
> 
> var bool[] bool_array_1 = bool[]{false, true};
9.  bug  ✅
    - string 的初始化, 默认值, 都要重新审视一下
    - fmt::println_string 有bug 如果数据很多会有bug
10. 实现一个简单的垃圾回收机制 mark&swap  ✅
11. native 函数 添加 vm::grbage_collect  ✅
12. Add native function vm::heap_size  ✅
13. 计算 heap_size 的方式需要重新计算  ✅ 
14. 要区分 length size capacity ✅


-----------------------------


## 2023-10-16周

1. 编译阶段和运行阶段某些工作要拆分开来
    某些结构体要及时释放, 不要相互依赖
2. 重新组织一下 std package 测试集
3. 每行后边的; 是不是可以去掉
4. 完善文档 Ring编译器开发规范 ✅
5. 重构一些代码和注释  ✅
6. 完善优化一下 vm_debug ✅
7. 完善一下 debug summary info  ✅
8.  完成一个简单的垃圾回收机制 mark&swap ✅


-----------------------------


## 2023-10-07周

1. 构想、实现 一下 reflect package ✅
2. 构想、实现 一下 any 类型 ✅
3. 把一键安装完善一下 https://cloud.tencent.com/developer/article/1884133
4. reflect 需要反射 bool int double string class array ✅
5. any 类型需要在语义分析的时候进行检查
6. 语法上还要支持可变参数 function println(var any... any_value_list); ✅
7. 函数内 读取可变参数列表，得需要某种方式，e.g.  for value := range any_value_list {}
8. golang 这个 example这个网站可以好好学习一下 ✅
    https://gobyexample.com/
    https://github.com/mmcgrana/gobyexample
    生成ring的example website    https://example.ring.wiki
9. 构想、实现一下 os io std-package


### bug 1

```
    fn test(var any any_value) {
        fmt::println_string(reflect::typeof(any_value));
    }

    error: generate opcode error
```

### bug 2
    
```
fn test(var int... int_value) {
}


fn main() {
    var int int_value_0;
    var int int_value_1;

    test(int_value_0, int_value_1);
}
```
执行的时候会挂掉

### reflect 构想 通过函数名字获取函数类型 

```
fn test(var bool bool_value, var int int_value)->(string) {

}

reflect::typeof(test);  // function(bool, int)->(string)
```

### 构想一下 for range

```

var int[] int_array;
for (key, value = range int_array) {
    fmt::println(key);
    fmt::println(value);
}
```

-----------------------------


## 2023-09-25周

## 2023-09-18周

1. 完善类数组
2. 函数传递数组、类、类数组
3. 把一键安装完善一下
4. 再完善一下语义分析
5. 想着把 import 关键字 改成 using  评估一下


## 2023-09-11周

## 2023-09-04周

## 2023-08-28周


1. 完成一个简单的垃圾回收机制 mark&swap
2. 通过RVM_RuntimeHeap 去分配内存
3. 自动化测试automated-testing.sh展示有点简陋，看看是否可以用 GoTest来搞定自动化测试
4. 优化语义分析
5. 优化 break continue return goto
6. 修复一下测试用例中的bug ✅
    6.1 minus运算符 操作 double literal的时候失败  ✅
    6.2 var string string_value; 定义之后不使用，不赋值，就进行访问，会内存错误  ✅
7. 好好完善一下 Makefile 各种debug宏 ✅
8. 添加完善一键安装的功能
   1. curl -sSL https://ring.wiki/install.sh | sh  ✅
   2. 在每发布一个 release版本的时候，需要在cos上自动创建对应版本的源码，install安装脚本。通过 github action
9. 实现 jump 跳转指令 重新评估一下 ✅
10. std/vm 标准库获取heap_size native函数需要支持返回值 ✅
11. 要把 invoke_native_function 和 invoke_derive_function 的逻辑合起来
12. bug , 如果一个函数有返回值，但是没有收集返回值，会报错， vm::heap_size() 就会报错 ✅
13. 优化 std lib vm ✅


-----------------------------


## 2023-08-21周

1. 完成一个简单的垃圾回收机制 mark&swap
2. 通过RVM_RuntimeHeap 去分配内存
3. 自动化测试automated-testing.sh展示有点简陋，看看是否可以用 GoTest来搞定自动化测试
4. github action workflow 自动构建release 预编译版本 ✅
5. 调研：以下几种编译方式 ✅
    - 源代码安装
    - 预编译安装
    - apt yum brew 软件源安装

6. sizeof() typeof()
7. flex bison 记录的行号不是太准确，比如说，对于function的定义，他会跑到最后一行，应该定位到function 定义的第一行
8. function variable package 的名字不可以一样
clang：报错
 redefinition of 'a' as different kind of symbol
1. ring man <keyword> 快速提示语法结构 ✅


-----------------------------


## 2023-08-14周

1. 优化string
    - 动态内存分配 size capacity append 增长
    - 通过索引访问
    - 优化字符串的拼接
    - fmt::to_string 函数，这样的话，是需要反射的，因为传入的变量可以是 int double string
    - size() 获取string的长度
    - fmt::printf("string_value_1 value:{}, size:{}\n", string_value_1, size(string_value_1)); 这也是需要反射
2. 优化完成string之后，优化 fmt 函数， fmt::println() -> io::write(var string str)
3. 优化报错信息 ✅
4. 完成一下测试用例
    函数变量传递 array string class变量
5. 完善 array class
6. 完善 array string
7. 完善多维数组


-----------------------------


## 2023-08-07周

1. 优化 runtime_stack 空间，要通过局部变量的数量来动态增长 空间
2. 想清楚全局变量、局部变量 初始化的时机 ✅
2.1 用户在使用ring的时候，不能在 global{} 块中进行全局变量的初始化 ✅
    必须要通过 function init(){} 对全局变量进行初始化
    如果main包import 了 fmt:
        函数的调用顺序为：fmt::init() -> main::init() -> main::main()

测试：在global中 定义全局变量时，初始全局变量。

3. 优化报错信息  将所有的printf 改成 compile_error runtime_error
4. 报错脚本的自动化测试✅

```
通过 ErrorReportContext 来实现
ErrorReportContext context = {

};
ring_compile_error(&context); // 每次ring_compile_error 都要添加一下错误次数，错误次数多了才要退出
```

错误信息:

```
./test/998-error-report/error-000.ring:10:0:
|       a;
|       ^......use undeclared variable identifier `a`; E:ERROR_UNDECLARED_IDENTIFIER
Advice: definite variable `a` like: `var bool|int|double|string a;`

./test/998-error-report/error-000.ring:10:0:
|       a;
|       ^......use undeclared variable identifier `a`; E:ERROR_UNDECLARED_IDENTIFIER
Advice: definite variable `a` like: `var bool|int|double|string a;`


1 error generated.

```

compile
synx_
fix_ast

应该细分一下，首先进行语义分析，将错误尽可能的报出来，同时还要积攒数量。
不然的话，fix_ast 可能会出错。
语义分析的时机，编译完成之后，fix_ast 之前。
语义分析的对象是 Package

但是目前一个Package 里边只能有一个PackageUnit 也就是一个包只能有一个文件
一个package 中 可以含有多个 global{} 块。
一个package 中 可以含有多个 init() function{} , 需要通过 @init-priority:1 来生命初始化的优先级

5. 还有一个没有搞明白
    ring 的前端是依赖两个工具flex 和 bison
    如果某个输入有语法错误，那么bison将会直接退出，如何更好的做语法检测。这个还真不太好搞。


-----------------------------

## 2023-07-31周

1. 全面重构类型系统 ✅
2. 修复 int[] double[] 的相关bug ✅
3. 支持数组的初始化赋值，var int[] array = int[]{1, 2, 3, 4}; ✅


-----------------------------

## 2023-07-24周

1. global block 可以有多个，e.g.

```
global {
}
global {
}
```

2. 实现 var int[] array ✅
3. 实现 new int[10], 暂时只支持一维数组 ✅
4. 实现 array = new int[10]; ✅
5. 在 vm 中要实现类型map 的查找和匹配

-----------------------------

## 2023-06-05周

1. 通读《自己动手实现Lua：虚拟机、编译器和标准库》 1-13章
2. 对学到的支持 优化Ring 数组
3. make install bug & 标准库路径写死的bug ✅


-----------------------------

## 2023-05-29周

1. 自己建立一个新的项目，目的是对Lua的字节码有一个较深的理解
   1. 深度学习Lua字节码
   2. 参考 《自己动手实现Lua：虚拟机、编译器和标准库》 1-13章
   3. 参考 https://github.com/GeneralSandman/luago-book
   4. 自己的项目 就是通过CPP来解析Lua的字节码
   5. 项目地址：https://github.com/GeneralSandman/GeneralSandman-lua-learn-node


1. lua-learn-node
   1. 完成了第二章的学习，并可以顺利通过CPP完成对第二章要点的完全掌握。
2. 对知乎专栏Lua模块精讲的学习
   1. Lua设计与实现 基于lua源码对其设计与具体实现进行剖析 https://www.zhihu.com/column/c_1097089416010567680


- 调研标准库的方式
- 参考lua 的 linux man 手册的编写
    https://linux.cn/article-10130-1.html
- Lua 二进制 Chunk的形式，写一个解析程序。学习《自己动手实现Lua：虚拟机、编译器和标准库》 1-13章
- https://github.com/GeneralSandman/luago-book
- lua设计与实现 https://www.zhihu.com/column/c_1097089416010567680

- 思考：全局变量初始化的时机


-----------------------------

## 2023-04-23周

- import 导入包
- std 标准包
- 完善所有的测试用例
- 优化函数的 return list
- 优化 基础 类型 string

- 实现：import 的相关功能 通过import 使用package内的函数     操作符使用 ::  方法的定义也使用 ::✅
- 实现：导入std-fmt包，使用fmt相关库函数，同时要设计好native函数要怎样register才能更方便    --有bug  优先fix
- 实现：import 的相关功能 通过import 使用package内的函数     操作符使用 ::  方法的定义也使用 ::
  - package::函数 ✅
- 实现：导入std-fmt包，使用fmt相关库函数，同时要设计好native函数要怎样register才能更方便     ✅
- 实现：import 的相关功能 通过import 使用package内的函数     操作符使用 ::  方法的定义也使用 ::
  - package::全局变量 ✅
  - package::类定义
- 测试：把所有的测试case统一做了更新  ✅
- 实现：解决 std package 路径的问题
- 调研：调试器  ✅
- 优化：记录原始行号的功能  ✅
- 优化：优化全局变量的一些逻辑  ✅
- 重构：重构了一些代码逻辑  ✅


- 实现：函数的返回类型
- 优化：函数的调用栈
- 优化：函数的局部变量
- 实现：method 使用 self关键字


- 实现：类的构造函数
- 修复：全局变量的初始化
- 修复：类的局部变量的初始化
- 优化：统一 execute 的时候 调用 native derive  function 的方式
- 设计：全局变量初始化的时机 

-----------------------------


## 2023-04-17周

1. 关于源代码切分
- 实现：package import 
- 实现：分package编译 生成字节码 链接

包的名称 不能 和类变量的名称一样，不然会有逻辑问题

- 实现：PacageUnit等 static变量的优化 
- 实现：根据import-package名称去访问 package内的function
- 优化：单文件内 对象的访问
- 实现：class method使用self关键字
- 实现：class method参数和返回值
- 实现：class 构造method
- 测试：完善 class 的相关测试
- 实现：好好实现 std-fmt 库，同时优化 native函数
- 实现：实现比较好用printf函数
- 设计：设计可变参数
- 实现：function method 返回值的严格检验 与 返回值处理

- 实现：源代码的切分编译 ✅
- 实现：编译器从C语言全部转为C++ ✅
- 重构：源代码没有变量编译错误 bug  ✅
- 重构：源代码import为空时编译错误 bug  ✅
- 重构：创建AST时，将 class_definition_list 和 function_list 转为 CPP-vector，更好的管理内存 ✅
- 实现：源代码的切分编译、打包 ✅
- 实现：导入使用 package ✅
- 实现：定义package ✅
- 实现：main 函数  ✅
- 优化：一些编译告警  ✅
- 修复：一些全局变量的默认初始值的bug  ✅
- 实现：去除编译warn告警，提高编译速度 ✅
- 实现：全局变量的定义采用一个比较好的 方式 global{}  ✅
- 实现：import 的相关功能 通过import 使用package内的函数     操作符使用 ::  方法的定义也使用 ::


-----------------------------


## 2023-04-10周

1. 实现面向对象的部分逻辑
- 实现：面向对象 field
- 实现：面向对象 method
- 实现：属性@public @private @constructor

2. 关于字节码二进制
- 实现：源代码与字节码的对应关系 更好的debug
- 理解：Lua字节码的定义，如果生成字节码，如何解析字节码


3. 关于源代码切分
- 实现：package import 
- 实现：分package编译 生成字节码 链接

4. 一些想到的问题
- 实现：属性 @format 应用到某个类的成员函数 定义重载打印对象数据结构的
- 虚拟机：当时设计的不足，不如预先分配一个比较大的空间 不能获取局部变量的数量
- 调研：调研现在主流的调试器


- 实现：外部访问成员变量 ✅
- 实现：通过对象访问成员变量：如job_0.Running = false; 如 println_bool(job_0.Running) ✅
- 设计：self 不设计成系统关键字，也就是不再语法分析的时候，不把他当作是一个token ✅
- 实现：通过对象调用成员函数method，只是简单实现了，见 008-class/class-001.ring ✅
- 实现：在method中访问field，涉及到self关键字
- 实现：Class 定义里边重新进行编写   field 一个list  method 一个list
- 实现：构造method
- 实现：实现@public @private
- 理解：Diksam 在生成字节码的时候 同时记录与源代码之间的关系 LineNumber✅
- 实现：Ring实现记录字节码与源代码的映射关系✅
- 重构：简单重构一下代码✅
- 实现：main函数 - 理解：Diksam 是如何实现源代码切分的，也就是require ✅
- 设计：Ring 多源代码输入的编译逻辑 ✅
- 实现：Ring 的package定义 和 import 导包 ✅
- 设计：Ring 多源代码输入的编译逻辑
  - 参考 GO env
- 调研：调试器

----------------------------------

## 2023-04-03周

实现面向对象
- 理解：diksam 面向对象、源代码切分、面向对象内存分配
- 设计：成员变量的场景  成员方法放在下一期
- 设计：面向对象的语法
- 实现：面向对象的语法
- 设计：虚拟机支持 面向对象的 内存分配
- 实现：虚拟机支持 面向对象的 内存分配
- 测试：面向对象的测试用例
- 设计：字节码二进制文件的生成、解析   好好参考一下 Lua


-----------------------------


## 错误提示

1. 使用有意义的错误消息：确保错误消息清晰明了，能够准确地指出问题所在。错误消息应该包含有关错误类型、位置和可能的解决方法的信息。
2. 提供上下文信息：在错误消息中提供尽可能多的上下文信息，以帮助用户理解问题。例如，可以包含相关的语法规则、输入符号和预期的符号等信息。
3. 提供详细的错误位置：在错误消息中指明具体的错误位置，以帮助用户快速定位问题。可以在错误消息中显示行号、列号或具体的代码片段。
4. 提供建议的修复方法：如果可能的话，可以在错误消息中提供一些建议的修复方法。这些建议可以是常见的错误修复方法，或者是根据上下文推断出的可能的解决方案。
5. 支持自定义错误处理：允许用户自定义错误处理函数，以便在发生错误时采取特定的行为。这样用户可以根据自己的需求自定义错误处理逻辑，例如记录错误日志、尝试自动修复等。
6. 提供详细的文档和示例：为bison工具提供详细的文档和示例，以帮助用户更好地理解和使用工具。文档应该包含有关错误处理的详细说明和示例代码，以及常见错误的解决方法。


要实现类似于Clang的智能化错误提示，需要进行更复杂的处理和分析。以下是一些可能的方法和技术：

1. 语法分析：使用更高级的语法分析技术，例如LLVM的Clang，可以检测和报告更复杂的语法错误。这可以包括缺失的分号、括号不匹配、不完整的语句等。
2. 语义分析：通过对代码进行语义分析，可以检测诸如未声明的变量、类型不匹配、函数调用错误等更高级的错误。这可能需要构建符号表、进行类型推断和类型检查等。
3. 数据流分析：通过数据流分析，可以检测和报告一些潜在的问题，例如未使用的变量、未初始化的变量、可能的空指针解引用等。
4. 代码规范检查：可以集成代码规范检查工具，例如Clang的静态分析器（Clang Static Analyzer）或其他工具，来检测代码中的潜在问题和违反规范的情况。
5. 模糊匹配和纠错：在发现错误时，可以使用模糊匹配和纠错技术，尝试推测用户的意图并提供可能的修复建议。例如，当用户在代码中输入了拼写错误时，可以通过推断正确的标识符并给出修复建议。
6. 上下文敏感的错误提示：利用上下文信息，可以更准确地定位错误和提供错误提示。例如，当用户在函数调用中传递错误的参数类型时，可以根据函数声明和调用上下文提供更具体的错误提示。



模糊匹配和纠错是一种常见的技术，用于推测用户的意图并提供可能的修复建议。以下是一些常见的模糊匹配和纠错方法：

1. 编辑距离：编辑距离是衡量两个字符串之间差异的度量，可以用于比较输入的错误单词与正确单词之间的相似程度。常见的编辑距离算法包括Levenshtein距离和Damerau-Levenshtein距离。可以计算输入单词与词典中的单词之间的编辑距离，并推荐与输入单词距离最近的正确单词作为纠错建议。
2. N-gram模型：N-gram模型是一种基于统计的语言模型，用于预测下一个词的可能性。可以使用N-gram模型来预测输入单词的下一个可能的单词，并给出基于上下文的纠错建议。
3. 词向量：词向量是将单词映射到连续向量空间的表示方法。可以使用词向量来计算输入单词与词典中的单词之间的相似度，并推荐与输入单词最相似的正确单词作为纠错建议。
4. 上下文信息：利用上下文信息，可以更准确地推测用户的意图和提供纠错建议。例如，当用户在代码中输入了拼写错误的标识符时，可以根据上下文中的其他标识符和语法规则推断正确的标识符。

以上方法可以结合使用，以提供更准确和智能的模糊匹配和纠错功能。具体的实现可以依赖于机器学习模型、自然语言处理技术和数据集的训练。例如，可以使用大规模的文本语料库进行训练，并构建模型来进行模糊匹配和纠错。同时，还可以根据特定领域的需求进行定制化的模型训练和优化。


上下文敏感的错误提示，这个怎么实现

实现上下文敏感的错误提示需要对代码的语法和语义进行深入分析，并根据上下文信息来判断可能的错误和提供相应的错误提示。以下是一些常见的实现方法：

1. 符号表：构建符号表来跟踪代码中的变量、函数和类型的声明和使用情况。通过分析符号表，可以检测未声明的变量、重复定义的变量、变量类型不匹配等错误，并在错误提示中提供准确的位置和相关信息。
2. 类型推断和类型检查：通过对代码进行类型推断和类型检查，可以检测类型不匹配、错误的函数调用、错误的操作符使用等错误。这需要构建和维护类型信息，并对代码进行静态分析。
3. 控制流分析：通过控制流分析，可以检测潜在的逻辑错误和代码路径不可达的情况。这可以帮助用户发现可能的错误逻辑和错误的条件分支。
4. 数据流分析：通过数据流分析，可以检测未使用的变量、未初始化的变量、可能的空指针解引用等问题。这需要跟踪变量的定义和使用情况，以及对数据流进行分析。
5. 模式匹配和规则检查：根据特定的代码规范和模式，可以检查代码中的潜在问题。例如，检测不安全的函数调用、内存泄漏、未释放的资源等。
6. 上下文窗口：维护一个上下文窗口，根据当前位置周围的代码片段提供错误提示。这可以包括相关的语法规则、变量使用情况、函数调用等信息，以帮助用户理解错误的上下文。
