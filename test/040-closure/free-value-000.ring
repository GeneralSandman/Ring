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


// TestDetail: 测试见的FreeValue , 不支持逃逸
@main
function main() {
	var FuncType func_var;

	func_var = return_closure();
}

function return_closure() -> (FuncType) {

	var bool local_bool_value_0;
	var int local_int_value_0 = 1;
	var FuncType tmp;

	fmt::printf("return_closure::out:1 local_int_value_0 = {}\n", local_int_value_0);

	local_int_value_0 ++;
	fmt::printf("return_closure::out:2 local_int_value_0 = {}\n", local_int_value_0);



	tmp = function() {
		local_int_value_0 ++;
		fmt::printf("return_closure::[closure]::1 local_int_value_0 = {}\n", local_int_value_0);
	};

	tmp();
	fmt::printf("return_closure::out:3 local_int_value_0 = {}\n", local_int_value_0);

	local_int_value_0++;
	fmt::printf("return_closure::out:4 local_int_value_0 = {}\n", local_int_value_0);

	tmp();
	fmt::printf("return_closure::out:5 local_int_value_0 = {}\n", local_int_value_0);

	return tmp;
}


