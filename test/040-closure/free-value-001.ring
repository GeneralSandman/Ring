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


// TestDetail: 测试见的FreeValue , 不支持逃逸
@main
fn main() {

	fmt::printf("-------------\n");
	use_closure();

	fmt::printf("-------------\n");
	use_closure();

}

fn use_closure() {

	var bool local_bool_value_0;
	var int local_int_value_0 = 1;
	var FuncType tmp;
	var FuncType tmp1;

	fmt::printf("return_closure::out:1 local_int_value_0 = {}\n", local_int_value_0);

	local_int_value_0 ++;
	fmt::printf("return_closure::out:2 local_int_value_0 = {}\n", local_int_value_0);



	fn() {
		local_int_value_0 ++;
		fmt::printf("return_closure::[closure]::1 local_int_value_0 = {}\n", local_int_value_0);
	}();

	fn() {
		local_int_value_0 ++;
		fmt::printf("return_closure::[closure]::2 local_int_value_0 = {}\n", local_int_value_0);
	}();


	local_int_value_0 ++;
	fmt::printf("return_closure::out:3 local_int_value_0 = {}\n", local_int_value_0);


}


