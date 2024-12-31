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


typedef fn() FuncType;


@main
fn main() {
	var FuncType local_func_var;

	local_func_var = fn() {
		fmt::println("invoke a closure 1");
	};
	local_func_var();

	local_func_var = fn() {
		fmt::println("invoke a closure 2");
	};
	local_func_var();


}