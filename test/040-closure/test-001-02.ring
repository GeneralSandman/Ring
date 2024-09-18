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

typedef function(var bool a, var int b) -> (string) FuncType;



@main
function main() {
	var FuncType local_func_var;

	local_func_var = function(var bool a, var int b) -> (string) {
		fmt::println("invoke a closure 1");
		return fmt::sprintf("ring {} {}", a, b);
	};

	// local_func_var();

	var string string_value;
	string_value = local_func_var(true, 223);
	fmt::println("return from closure string_value:", string_value);

}