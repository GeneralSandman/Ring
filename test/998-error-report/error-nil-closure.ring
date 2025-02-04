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

//TestDetail: 匿名函数变量为nil的时候怎么办
fn main() {
    var FuncType func_var;

    fmt::println(reflect::typeof(func_var));
    
    fmt::println(func_var);

    func_var();
}