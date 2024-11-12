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

	test();
	
	fmt::printf("main end\n");
}

function test() {

	var bool local_bool_value;
	var int local_int_value;
	var int64 local_int64_value;
	var string local_string_value;


	defer function() {
		fmt::printf("---------- defer 1 ----------\n");
		fmt::printf("defer bool_value={}\n", local_bool_value);
		fmt::printf("defer int_value={}\n", local_int_value);
		fmt::printf("defer int64_value={}\n", local_int64_value);
		fmt::printf("defer string_value={}\n", local_string_value);
		fmt::printf("-----------------------------\n");
	}();



	local_bool_value = true;
	local_int_value = 123;
	local_int64_value = 456L;
	local_string_value = "hello world";

	defer function() {
		fmt::printf("---------- defer 2 ----------\n");
		fmt::printf("defer bool_value={}\n", local_bool_value);
		fmt::printf("defer int_value={}\n", local_int_value);
		fmt::printf("defer int64_value={}\n", local_int64_value);
		fmt::printf("defer string_value={}\n", local_string_value);
		fmt::printf("-----------------------------\n");
	}();


	fmt::printf("test begin\n");
	fmt::printf("test end\n");
}
