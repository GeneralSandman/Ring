
package main

import {
    fmt;
    debug;
    reflect;
}


typedef class Job {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;
}


function func_return_0(var bool bool_value, var int int_value, var double double_value, var string string_value) {
}

function test1(var string format, var any... any_value) {

}


// TestDetail: 函数调用 返回参数的强制校验
// TestDetail: 不能编译通过, 函数数量和类型不匹配
// TestDetail: 

@main
function main() {
    var Job   local_job_value_0;

    func_return_01(true, 1, 1.1, "1.1");

    // var string local_string_value_0 = "参数不一致";
    // fmt::println(len(local_string_value_0));
}
