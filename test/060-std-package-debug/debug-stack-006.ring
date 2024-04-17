//
// File:    std-debug-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	fmt;
	debug;
}



global {
	var bool   global_bool_value;
	var int    global_int_value;
	var double global_double_value;
	var string global_string_value;
}

// TestDetail: 测试 debug::print_call_stack()
// TestDetail: 函数多次调用
@main
function main() {

	
	fmt::println("\ntest 1-------------");
	fmt::println("main()::0");
	fmt::println("main()::1");
	test1();
	fmt::println("main()::2");
	fmt::println("main()::3");

}

function test1() {
	fmt::println("test1()::0");
	fmt::println("test1()::1");
	test2();
	fmt::println("test1()::2");
	fmt::println("test1()::3");
}

function test2() {
	fmt::println("test2()::0");
	fmt::println("test2()::1");
	test3();
	fmt::println("test2()::2");
	fmt::println("test2()::3");
}

function test3() {
	fmt::println("test3()::0");
	fmt::println("test3()::1");
	fmt::println("test3()::2");
	fmt::println("test3()::3");
	debug::print_call_stack();
}