//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
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

fn main() {

	
	fmt::println("\ntest 1-------------");
	fmt::println("main()::0");
	fmt::println("main()::1");
	test1();
	fmt::println("main()::2");


	fmt::printf(""); // 空指令，无意义，用于占行
	fmt::printf(""); // 空指令，无意义，用于占行

	fmt::println("main()::3");

}

fn test1() {
	fmt::println("test1()::0");
	fmt::println("test1()::1");
	fmt::printf(""); // 空指令，无意义，用于占行
	fmt::printf(""); // 空指令，无意义，用于占行
	fmt::printf(""); // 空指令，无意义，用于占行
	fmt::printf(""); // 空指令，无意义，用于占行
	test2();
	fmt::printf(""); // 空指令，无意义，用于占行
	fmt::println("test1()::2");
	fmt::println("test1()::3");
}

fn test2() {





	fmt::printf(""); // 空指令，无意义，用于占行
	fmt::println("test2()::0");
	fmt::println("test2()::1");
	test3();
	fmt::println("test2()::2");
	fmt::println("test2()::3");
}

fn test3() {
	fmt::println("test3()::0");
	fmt::println("test3()::1");
	fmt::println("test3()::2");
	fmt::println("test3()::3");
	debug::print_call_stack();




	fmt::printf(""); // 空指令，无意义，用于占行
	fmt::printf(""); // 空指令，无意义，用于占行
}