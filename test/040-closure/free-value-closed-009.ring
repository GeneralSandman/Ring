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

	fmt::printf("------------------ [main] ------------------\n");
	func_var = return_closure();
	func_var();
}

function return_closure() -> (FuncType) {

	var int local_int_value_0 = 100;

	return function() {
		local_int_value_0 ++;
		fmt::printf("return_closure::[closure]::1 local_int_value_0 = {}\n", local_int_value_0);
	};

}


