//
// File:    std-debug-000.ring
// Author:  zhenhuli - generalsandman@163.com
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
    }
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
	var Job    local_job_value;

	
	fmt::println("\n-------------");
	fmt::println("main()::0");
	fmt::println("main()::1");
	test1();
	fmt::println("main()::2");
	fmt::println("main()::3");

	local_bool_value = true;
	local_int_value = 12;
	local_double_value = 34.56;
	local_string_value = "hello world";


	fmt::println("\n-------------");
	fmt::println("main()::0");
	fmt::println("main()::1");
	test1();
	fmt::println("main()::2");
	fmt::println("main()::3");


	fmt::println("\n-------------");
	fmt::println("main()::0");
	fmt::println("main()::1");
	local_job_value.test1();
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
}