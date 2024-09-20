//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	os;
	debug;
	fmt;
}


typedef function() functype_0;
typedef function() -> (string) functype_1;

// TestDetail: 匿名函数
// TestDetail: 不需要定义匿名函数变量, 可以直接通过函数参数传递
@main
function main() {

	pass_closure(function() {
		fmt::println("main:: closure block 1");
	}, function() -> (string) {
		fmt::println("main:: closure block 2");
		return "main:: closure return value";
	});
	
}

function pass_closure(var functype_0 func_0, var functype_1 func_1) {
	fmt::println("pass_closure::begin");
	func_0();

	var string tmp;
	tmp = func_1();
	fmt::printf("return from func_1:\"{}\"\n", tmp);

	
	fmt::println("pass_closure::end");
}


