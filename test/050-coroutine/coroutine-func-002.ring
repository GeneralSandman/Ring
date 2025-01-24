//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
	fmt;
	self;
}

typedef Job1 = class {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}


fn job_action_0(var bool bool_arg, var int int_arg, var int64 int64_arg, var double double_arg, var string string_arg, var Job1 job1_arg) {
	fmt::printf("            job_action_0::begin\n");
	fmt::printf("            job_action_0::bool_arg:   {}\n", bool_arg);
	fmt::printf("            job_action_0::int_arg:    {}\n", int_arg);
	fmt::printf("            job_action_0::int64_arg:  {}\n", int64_arg);
	fmt::printf("            job_action_0::double_arg: {}\n", double_arg);
	yield();
	fmt::printf("            job_action_0::string_arg: {}\n", string_arg);
	fmt::printf("            job_action_0::job1_arg:   {}\n", job1_arg);
	fmt::printf("            job_action_0::end\n");
}


// TestDetail: 测试 launch 一个函数，函数有参数，没有返回值
fn main() {
	var int64 co_id;

	fmt::println("main::1");

	co_id = launch job_action_0(true, 23, 44L, 3.1415, "ring-lang", Job1{
		Bool:   true,
		Int:    23,
		Int64:  44L,
		Double: 3.1415,
		String: "ring-lang",
	});
	fmt::printf("co_id: {}\n", co_id);

	fmt::println("main::2");

	resume(co_id);

	fmt::println("main::3");

	resume(co_id);

	fmt::println("main::4");

	resume(co_id); // 无效果

	fmt::println("main::5");
}