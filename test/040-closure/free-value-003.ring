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

typedef FuncType = fn();


// TestDetail: 测试见的FreeValue , 不支持逃逸
fn main() {

	var FuncType func_var;

	func_var = use_closure();

	func_var();
	func_var();
}

fn use_closure() -> (FuncType) {

	var int level0_local_int_value_0;
	var int level0_local_int_value_1;
	var int level0_local_int_value_2;
	var int level0_local_int_value_3;

	level0_local_int_value_0 = 0;
	level0_local_int_value_1 = 1;
	level0_local_int_value_2 = 2;
	level0_local_int_value_3 = 3;


	fmt::printf("[user_closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
	fmt::printf("[user_closure] level0_local_int_value_1={}\n", level0_local_int_value_1);
	fmt::printf("[user_closure] level0_local_int_value_2={}\n", level0_local_int_value_2);
	fmt::printf("[user_closure] level0_local_int_value_3={}\n", level0_local_int_value_3);


	var FuncType func_var;
	func_var = fn() {
		level0_local_int_value_0 ++;
		level0_local_int_value_1 ++;

		fn() {
			level0_local_int_value_2 ++;
			level0_local_int_value_3 ++;

		}();
		fmt::printf("[+closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
		fmt::printf("[+closure] level0_local_int_value_1={}\n", level0_local_int_value_1);
		fmt::printf("[+closure] level0_local_int_value_2={}\n", level0_local_int_value_2);
		fmt::printf("[+closure] level0_local_int_value_3={}\n", level0_local_int_value_3);
	};
	
	func_var();
	func_var();

	fmt::printf("[user_closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
	fmt::printf("[user_closure] level0_local_int_value_1={}\n", level0_local_int_value_1);
	fmt::printf("[user_closure] level0_local_int_value_2={}\n", level0_local_int_value_2);
	fmt::printf("[user_closure] level0_local_int_value_3={}\n", level0_local_int_value_3);

	return func_var;


}


