//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	fmt;
	runtime;
}

typedef Job = class {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;

    fn test1() {
		fmt::println("Job::test1()::0");
		fmt::println("Job::test1()::1");
		self.test2();
		fmt::println("Job::test1()::2");
		fmt::println("Job::test1()::3");
    }

	fn test2() {
		fmt::println("Job::test2()::0");
		fmt::println("Job::test2()::1");
		self.test3();
		fmt::println("Job::test2()::2");
		fmt::println("Job::test2()::3");
    }

	fn test3() {
		fmt::println("Job::test3()::0");
		fmt::println("Job::test3()::1");
		fmt::println("Job::test3()::2");
		fmt::println("Job::test3()::3");
		runtime::print_call_stack();
    }
}


global {
	var bool   global_bool_value;
	var int    global_int_value;
	var double global_double_value;
	var string global_string_value;
	var Job    global_job_value;
}

// TestDetail: 测试 debug::print_call_stack()
// TestDetail: 函数/method 多次调用

fn main() {

	
	fmt::println("\ntest 1-------------");
	fmt::println("main()::0");
	fmt::println("main()::1");
	test1();
	fmt::println("main()::2");
	fmt::println("main()::3");

}

fn test1() {
	fmt::println("test1()::0");
	fmt::println("test1()::1");
	test2();
	fmt::println("test1()::2");
	fmt::println("test1()::3");
}

fn test2() {
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
	global_job_value.test1();
}