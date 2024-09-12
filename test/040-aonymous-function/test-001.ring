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



@main
function main() {
	var FuncType local_func_var;

	local_func_var = function(var bool bool_value, var int int_value) -> (string) {
		fmt::println("invoke a aonymous_function");
	};


	local_func_var(false, 0);
}