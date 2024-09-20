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


@main
function main() {
	var FuncType local_func_var;

	local_func_var = function() {
		fmt::println("invoke a closure 1");
	};
	local_func_var();

	local_func_var = function() {
		fmt::println("invoke a closure 2");
	};
	local_func_var();


	// FIXME: 这里不应该编译通过
	local_func_var = function(var bool bool_value, var int int_value, var int64 int64_value, var double double_value, var string string_value) {
		var bool   local_bool_value_0 = true;
		var int    local_int_value_0 = 1;
		var int64  local_int64_value_0 = 2L;
		var double local_double_value_0 = 3.1415926;
        var string local_string_value_0 = "hello-world";

		fmt::println("invoke a closure 3");
		fmt::println("-bool_value:",   bool_value);
        fmt::println("-int_value:",    int_value);
		fmt::println("-int64_value:",  int64_value);
        fmt::println("-double_value:", double_value);
		fmt::println("-string_value:", string_value);
		fmt::println("-local_bool_value_0:",   local_bool_value_0);
		fmt::println("-local_int_value_0:",    local_int_value_0);
		fmt::println("-local_int64_value_0:",  local_int64_value_0);
		fmt::println("-local_double_value_0:", local_double_value_0);
        fmt::println("-local_string_value_0:", local_string_value_0);
	};
	local_func_var(true, 123, 65536L, 3.1415926, "ring-closure");
}