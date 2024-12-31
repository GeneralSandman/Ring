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


fn job_action_0(var bool bool_arg) {
	fmt::printf("            job_action_0::begin\n");
	fmt::printf("            job_action_0::bool_arg: {}\n", bool_arg);
	yield();
	fmt::printf("            job_action_0::end\n");
}


// TestDetail: 测试 launch 一个函数，函数有参数，没有返回值
@main
fn main() {
	var int64 co_id;

	fmt::println("main::1");

	co_id = launch job_action_0(true);
	fmt::printf("co_id: {}\n", co_id);

	fmt::println("main::2");

	resume(co_id);

	fmt::println("main::3");

	resume(co_id);

	fmt::println("main::4");

	resume(co_id); // 无效果

	fmt::println("main::5");
}