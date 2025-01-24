
package main

import {
    fmt;
    debug;
    reflect;
}


typedef Job = class {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;
}


fn func_return_0(var bool bool_value, var int int_value, var double double_value, var string string_value) {
}

fn test1(var string format, var any... any_value) {

}


// TestDetail: 函数调用 返回参数的强制校验
// TestDetail: 不能编译通过, 函数数量和类型不匹配
// TestDetail: 

fn main() {
    var Job   local_job_value_0;

    func_return_01(true, 1, 1.1, "1.1");

    // var string local_string_value_0 = "参数不一致";
    // fmt::println(len(local_string_value_0));
}
