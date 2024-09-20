
# Proposal: 匿名函数&闭包

Author(s): GeneralSandman

First created: 2024-07-29

Last updated: 2024-09-12

Status: Draft/Design/Release

Discussion at https://github.com/GeneralSandman/Ring/issue/NNNNN.

## Abstract

Ring语言提案002，主要讨论 匿名函数&闭包

## Background

### A. Golang中是如何定义匿名函数的

```go
func test() (bool, int) {
    return true, 1;
}


// 匿名函数
// golang 闭包是按照引用捕获

tmp := func() (bool, int) {
    return true, 1;
}
```

### B. Rust中是如何定义匿名函数的

```rust
fn add(a: i32, b: i32) -> i32 {
    a + b
}

fn main() {
    let result = add(2, 3);
    println!("Result: {}", result);
}

```

```rust
fn main() {
    let add = |a: i32, b: i32| a + b;
    let result = add(2, 3);
    println!("Result: {}", result);
}
```



## Proposal


### 匿名函数v0.1


#### Support

```ring

function main() {

    // 定义函数变量 
    var FuncType local_func_var;

    // 将一个匿名函数赋值给一个函数变量
    local_func_var = function() {

    };

    // 像调用函数一样调用一个匿名函数
    local_func_var();
}

```



1. 支持 匿名函数支持参数传递和局部变量的定义
2. 支持 匿名函数 的返回值逻辑
3. 废弃 FuncType类型, 支持typedef区定义一个函数类型
4. 在调用匿名函数的时候, 能够做函数调用的强制校验: 函数参数+函数返回值




1. 支持 定义 变量，变量的类型是 一个函数类型
2. 支持 通过匿名函数 赋值给一个匿名函数类型变量
3. 支持跟 函数调用一样，调用一个匿名函数
4. 语义上要对 匿名函数 做类型强制性检查

##### 匿名函数的内存存在哪里

匿名函数所占用的内存可以分为

这两个应该 存储在 函数的
1. 匿名函数相关的定义
2. 代码块

1. 局部变量
2. 闭包变量


#### 匿名函数 block 也要生成对应的字节码


generate block code for closure 



#### 关于调用匿名函数对应的字节码


- push/pop stack_closure
- push/pop static_closure
- push/pop array_closure
- array append/pop closure
- push/pop field_closure
- new_array_closure
- new_array_literal_closure
- range_array_closure


像函数调用一样使用closure，对应的字节码该如何设计

```ring
    func(false, 1);
```


对应函数调用的字节码

```
    push_false
    push_int
    argument_num
    push_func
    invoke_func_derive
```

push_func/push_method

invoke_func_native/invoke_func/invoke_method

是否应该引入 push_closure/invoke_closure 指令，用于调用closure


对应closure 调用的字节码

```
    push_false
    push_int
    argument_num
    push_closure
    invoke_closure
```

这样有个好处就是前期方便处理


closure 放在一个 constant-pool



#### 限制的使用场景

1. 不支持闭包的用法，也就是匿名函数内使用的变量，不是局部变量就是全局变量，不支持捕获外部函数的局部变量
2. 匿名函数支持参数传递和局部变量的定义, 但是不支持一个匿名函数有返回值.



2. 通过typedef 定义一个函数类型
3. 通过函数类型去定义一个函数变量
4. 函数变量进行赋值
5. 像调用函数一样调用一个匿名函数
6. 函数支持通过 参数传递匿名函数、返回值支持返回匿名函数







### 下个版本的匿名函数

closure function method 都需要函数语义分析

closuer function method 都需要生成对应的字节码

function/method 可以赋值给 closure


### lua 闭包实现的参考资料

https://manistein.github.io/blog/post/program/let-us-build-a-lua-interpreter/%E6%9E%84%E5%BB%BAlua%E8%A7%A3%E9%87%8A%E5%99%A8part11/

https://yuerer.com/Lua5.3-%E8%AE%BE%E8%AE%A1%E5%AE%9E%E7%8E%B0(%E5%9B%9B)-Closure%E4%B8%8EUpvalues/


lua 扁平闭包

https://juejin.cn/post/7121555416420450317



## Rationale

[A discussion of alternate approaches and the trade offs, advantages, and disadvantages of the specified approach.]

## Compatibility

[A discussion of the change with regard to the
[compatibility guidelines](https://go.dev/doc/go1compat).]

## Implementation

[A description of the steps in the implementation, who will do them, and when.
This should include a discussion of how the work fits into [Go's release cycle](https://go.dev/wiki/Go-Release-Cycle).]

## Open issues (if applicable)

[A discussion of issues relating to this proposal for which the author does not
know the solution. This section may be omitted if there are none.]