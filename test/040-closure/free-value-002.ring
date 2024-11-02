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

	fmt::printf("-----------\n");
	func_var = use_closure();
	// func_var();
    // func_var();

	// fmt::printf("-----------\n");
	// func_var = use_closure();
	// func_var();
    // func_var();

}

function use_closure() -> (FuncType) {

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
	debug::debug_assert(level0_local_int_value_0 == 0);
	debug::debug_assert(level0_local_int_value_1 == 1);
	debug::debug_assert(level0_local_int_value_2 == 2);
	debug::debug_assert(level0_local_int_value_3 == 3);


	var FuncType func_var;
	func_var = function() {
		level0_local_int_value_0 ++;
		level0_local_int_value_1 ++;
		
		
		

		var int level1_local_int_value_0 = 10;
		var int level1_local_int_value_1 = 11;
		fmt::printf("[+closure] level1_local_int_value_0={}\n", level1_local_int_value_0);
		fmt::printf("[+closure] level1_local_int_value_1={}\n", level1_local_int_value_1);
		debug::debug_assert(level0_local_int_value_0 == 1);
		debug::debug_assert(level0_local_int_value_1 == 2);
		debug::debug_assert(level0_local_int_value_2 == 2);
		debug::debug_assert(level0_local_int_value_3 == 3);
		debug::debug_assert(level1_local_int_value_0 == 10);
		debug::debug_assert(level1_local_int_value_1 == 11);
		
		function() {
			level0_local_int_value_2 ++;
			level0_local_int_value_3 ++;

			level1_local_int_value_0 += 2;
			level1_local_int_value_1 += 2;
			fmt::printf("[++closure] level1_local_int_value_0={}\n", level1_local_int_value_0);
			fmt::printf("[++closure] level1_local_int_value_1={}\n", level1_local_int_value_1);
			debug::debug_assert(level0_local_int_value_0 == 1);
			debug::debug_assert(level0_local_int_value_1 == 2);
			debug::debug_assert(level0_local_int_value_2 == 3);
			debug::debug_assert(level0_local_int_value_3 == 4);
			debug::debug_assert(level1_local_int_value_0 == 12);
			debug::debug_assert(level1_local_int_value_1 == 13);
		}();
		fmt::printf("[+closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
		fmt::printf("[+closure] level0_local_int_value_1={}\n", level0_local_int_value_1);
		fmt::printf("[+closure] level0_local_int_value_2={}\n", level0_local_int_value_2);
		fmt::printf("[+closure] level0_local_int_value_3={}\n", level0_local_int_value_3);
		fmt::printf("[+closure] level1_local_int_value_0={}\n", level1_local_int_value_0);
		fmt::printf("[+closure] level1_local_int_value_1={}\n", level1_local_int_value_1);
		debug::debug_assert(level0_local_int_value_0 == 1);
		debug::debug_assert(level0_local_int_value_1 == 2);
		debug::debug_assert(level0_local_int_value_2 == 3);
		debug::debug_assert(level0_local_int_value_3 == 4);
		debug::debug_assert(level1_local_int_value_0 == 12);
		debug::debug_assert(level1_local_int_value_1 == 13);
	};
	
	func_var();

	fmt::printf("[user_closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
	fmt::printf("[user_closure] level0_local_int_value_1={}\n", level0_local_int_value_1);
	fmt::printf("[user_closure] level0_local_int_value_2={}\n", level0_local_int_value_2);
	fmt::printf("[user_closure] level0_local_int_value_3={}\n", level0_local_int_value_3);
	debug::debug_assert(level0_local_int_value_0 == 1);
	debug::debug_assert(level0_local_int_value_1 == 2);
	debug::debug_assert(level0_local_int_value_2 == 3);
	debug::debug_assert(level0_local_int_value_3 == 4);

	return func_var;

}


