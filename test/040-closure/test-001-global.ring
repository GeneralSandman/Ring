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


typedef function() FuncType;

global {
	var bool   global_bool_value_1;
	var int    global_int_value_1;
	var int64  global_int64_value_1;
	var double global_double_value_1;
	var string global_string_value_1;
}


@main
function main() {
	var FuncType local_func_var;

	local_func_var = function() {
		fmt::println("invoke a closure 1:begin");
		global_bool_value_1   = true;
		global_int_value_1    = 1;
		global_int64_value_1  = 2L;
		global_double_value_1 = 3.1415926;
		global_string_value_1 = "hello-world";
		fmt::println("invoke a closure 1:end");
		};
	local_func_var();

	fmt::println("main=======");
	fmt::println("global_bool_value_1: ", global_bool_value_1);
	fmt::println("global_int_value_1: ", global_int_value_1);
	fmt::println("global_int64_value_1: ", global_int64_value_1);
	fmt::println("global_double_value_1: ", global_double_value_1);
	fmt::println("global_string_value_1: ", global_string_value_1);
}