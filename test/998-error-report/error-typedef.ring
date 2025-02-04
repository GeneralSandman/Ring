//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
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

//TestDetail: typedef 定义的类型名称必须大写开头
fn main() {
}