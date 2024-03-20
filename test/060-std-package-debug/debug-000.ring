//
// File:    std-debug-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
}

global {
	var bool   global_bool_value;
	var int    global_int_value;
	var double global_double_value;
	var string global_string_value;
}

@main
function main() {
	var bool   local_bool_value;
	var int    local_int_value;
	var double local_double_value;
	var string local_string_value;

	test();
	
	fmt::println("main::1");
	fmt::println("main::2");
	fmt::println("main::3");
	fmt::println("main::4");

	local_bool_value = true;
	local_int_value = 12;
	local_double_value = 34.56;
	local_string_value = "hello world";
}

function test() {
	fmt::println("main::5");
	fmt::println("main::6");
	fmt::println("main::7");
	fmt::println("main::8");

}