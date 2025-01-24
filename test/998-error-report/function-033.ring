
package main

import {
    fmt;
    debug;
    reflect;
}

typedef Job1 = class {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;

    fn func_return_0() -> (bool, int) {
        // 编译不过, 数量不匹配
        return true;
    }
    
    fn func_return_1() -> (bool, int) {
        // 编译不过, 数量不匹配
        return true;
    }

    fn func_return_2() -> (bool, int) {
        // 编译不过, 类型不匹配
        return true, true;
    }
}

fn func_return_0() -> (bool, int) {
    return true, 1;
}

fn func_return_1() -> (bool, int) {
    // 编译不过, 数量不匹配
    return true;
}

fn func_return_2() -> (bool, int) {
    // 编译不过, 类型不匹配
    return true, true;
}

fn func_return_3() -> (bool, int) {
    // 编译通过
    return func_return_0();
}

fn func_return_4() -> (bool, int, string) {
    // 编译不过, 类似于多项赋值中, right不能存在 多返回值的函数调用
    return func_return_0(), "a";
}


// TestDetail: 语义检查 return语句 与 function定义的返回值 不匹配
fn main() {
    var bool   local_bool_value_0;
    var int    local_int_value_0;
    var double local_double_value_0;
    var string local_string_value_0;
    var Job1   local_job1_value_0;


    local_bool_value_0, local_int_value_0 = func_return_0();

    fmt::printf("local_bool_value_0:{}, local_int_value_0:{}\n", local_bool_value_0, local_int_value_0);
}
