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


typedef function(var string string_var) FuncType;


@main
function main() {
	test();
}


function test() {
	var FuncType local_func_var;

	var int local_int_value_0;

	function(var string string_var) {
		fmt::printf("invoke a closure local_int_value_0={}\n", local_int_value_0);
		fmt::printf("invoke a closure string_var={}\n", string_var);
	}("hello world");


	local_int_value_0 = 100;

	function(var string string_var) {
		fmt::printf("invoke a closure local_int_value_0={}\n", local_int_value_0);
		fmt::printf("invoke a closure string_var={}\n", string_var);
	}("hello world");
	
}