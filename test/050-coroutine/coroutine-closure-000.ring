//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
	fmt;
}


typedef fn() FuncType;

@main
fn main() {

	var FuncType job_action1;
	job_action1 = fn() {
		fmt::println("            job_action1::1");
		yield();
		fmt::println("            job_action1::2");
	};

	var int64 co_id;


    co_id = launch job_action1();
	fmt::printf("co_id: {}\n", co_id);

	fmt::println("main::1");

	resume(co_id);

	fmt::println("main::2");
	resume(co_id);

	fmt::println("main::3");

}
