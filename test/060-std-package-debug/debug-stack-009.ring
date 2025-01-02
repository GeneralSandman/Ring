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

typedef class Job {
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
		global_tool_value.test1();
    }
}


typedef class Tool {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;

    fn test1() {
		fmt::println("Tool::test1()::0");
		fmt::println("Tool::test1()::1");
		self.test2();
		fmt::println("Tool::test1()::2");
		fmt::println("Tool::test1()::3");
    }

	fn test2() {
		fmt::println("Tool::test2()::0");
		fmt::println("Tool::test2()::1");
		self.test3();
		fmt::println("Tool::test2()::2");
		fmt::println("Tool::test2()::3");
    }

	fn test3() {
		fmt::println("Tool::test3()::0");
		fmt::println("Tool::test3()::1");
		fmt::println("Tool::test3()::2");
		fmt::println("Tool::test3()::3");
		test3();
    }
}


global {
	var bool   global_bool_value;
	var int    global_int_value;
	var double global_double_value;
	var string global_string_value;
	var Job    global_job_value;
	var Tool   global_tool_value;
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
	global_job_value.test1();
	fmt::println("test2()::2");
	fmt::println("test2()::3");
}


fn test3() {
	test4();
}

fn test4() {
	debug::print_call_stack();
}