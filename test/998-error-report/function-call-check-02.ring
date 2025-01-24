//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	os;
	debug;
}


typedef FuncType = fn(bool, bool) -> (string);

fn main() {
	var FuncType local_func_var;

	local_func_var = fn(var bool a, var int b) -> (string) {
		fmt::println("invoke a closure 1");
		return fmt::sprintf("ring {} {}", a, b);
	};
}
