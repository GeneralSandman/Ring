//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
    reflect;
}

typedef Job = class {
	var bool     Bool;
    var int      Int;
    var int64    Int64;
    var double   Double;
    var string   String;
	var FuncType FuncField;
}

typedef FuncType = fn() -> (string);

//TestDetail: typeof 获取 多维数组的类型
fn main() {
    test0();
}

fn test0() {
    var int[!2] local_value_array_0;
    var int[,] local_value_array_1;
    var int[!2] local_value_array_2 = int[!2]{};

    fmt::println(reflect::typeof(local_value_array_0));
    fmt::println(reflect::typeof(local_value_array_1));
    fmt::println(reflect::typeof(local_value_array_2));

    fmt::println(local_value_array_0);
    fmt::println(local_value_array_1);
    fmt::println(local_value_array_2);
}