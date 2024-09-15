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


function test1() -> (FuncType, FuncType) {

	var FuncType local_func_var_0, local_func_var_1;

	local_func_var_0 = function() {
		var bool   local_bool_value_0 = false;
		var int    local_int_value_0 = 0;
		var int64  local_int64_value_0 = 0L;
		var double local_double_value_0 = 0.0;
        var string local_string_value_0 = "";

		fmt::println("\ninvoke a test1::closure 0");
		fmt::println("-local_bool_value_0:",   local_bool_value_0);
		fmt::println("-local_int_value_0:",    local_int_value_0);
		fmt::println("-local_int64_value_0:",  local_int64_value_0);
		fmt::println("-local_double_value_0:", local_double_value_0);
        fmt::println("-local_string_value_0:", local_string_value_0);
	};
	local_func_var_1 = function() {
		var bool   local_bool_value_0 = true;
		var int    local_int_value_0 = 1;
		var int64  local_int64_value_0 = 2L;
		var double local_double_value_0 = 3.1415926;
        var string local_string_value_0 = "hello-world";

		fmt::println("\ninvoke a test1::closure 1");
		fmt::println("-local_bool_value_0:",   local_bool_value_0);
		fmt::println("-local_int_value_0:",    local_int_value_0);
		fmt::println("-local_int64_value_0:",  local_int64_value_0);
		fmt::println("-local_double_value_0:", local_double_value_0);
        fmt::println("-local_string_value_0:", local_string_value_0);
	};
	
	
	return local_func_var_0, local_func_var_1;
}


@main
function main() {
	var FuncType local_func_var_0, local_func_var_1;
	
	
	local_func_var_0, local_func_var_1 = test1();
	local_func_var_0();
	local_func_var_1();



	var FuncType tmp;

	tmp = local_func_var_0;
	tmp();

	tmp = local_func_var_1;
	tmp();
}


