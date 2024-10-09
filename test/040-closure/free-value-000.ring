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


// @main
// function main() {
// 	var FuncType func_var;

// 	func_var = return_closure();

// 	func_var();

// 	func_var();
// }

function return_closure() -> (FuncType) {

	var int local_int_value_0;
	var FuncType tmp;

	fmt::printf("return_closure::out:1 local_int_value_0 = {}\n", local_int_value_0);


	tmp = function() {
		local_int_value_0 ++;
		// fmt::printf("return_closure::closure::1 local_int_value_0 = {}\n", local_int_value_0);
	};

	// fmt::printf("return_closure::out:2 local_int_value_0 = {}\n", local_int_value_0);

	return tmp;
}


