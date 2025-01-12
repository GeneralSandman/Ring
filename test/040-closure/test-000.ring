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
	reflect;
}


typedef fn() FuncType;


fn main() {
	var FuncType local_func_var;

	fmt::println(local_func_var);
	fmt::println(reflect::typeof(local_func_var));


	local_func_var = fn() {
	};
	// fmt::println(local_func_var); // 输出：CLOSURE(0x7fb598006920) 闭包地址
	fmt::println(reflect::typeof(local_func_var));



}