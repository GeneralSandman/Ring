//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
}


typedef class Job {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;

    method test1() {
		fmt::println("Job::test1()::0");
		fmt::println("Job::test1()::1");
		self.test2();
		fmt::println("Job::test1()::2");
		fmt::println("Job::test1()::3");
    }

	method test2() {
		fmt::println("Job::test2()::0");
		fmt::println("Job::test2()::1");
		self.test3();
		fmt::println("Job::test2()::2");
		fmt::println("Job::test2()::3");
    }

	method test3() {
		fmt::println("Job::test3()::0");
		fmt::println("Job::test3()::1");
		fmt::println("Job::test3()::2");
		fmt::println("Job::test3()::3");
		debug::print_call_stack();
    }
}


global {
	var bool   global_bool_value;
	var int    global_int_value;
	var double global_double_value;
	var string global_string_value;
}

// TestDetail: 测试 debug::print_call_stack()
// TestDetail: method多次调用
@main
function main() {
	var Job    local_job_value;

	
	fmt::println("\ntest 1-------------");
	fmt::println("main()::0");
	fmt::println("main()::1");
	local_job_value.test1();
	fmt::println("main()::2");
	fmt::println("main()::3");
}
