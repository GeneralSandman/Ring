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

typedef Job = class {
	var FuncType0 FuncField;
}

typedef FuncType0 = fn();



fn job_action2() {
	fmt::println("            job_action2::1");
	yield();
	fmt::println("            job_action2::2");
}

fn main() {

	var Job local_job_value_0 = Job{
		FuncField: fn() {
			fmt::println("            job_action1::1");
			job_action2();
			fmt::println("            job_action1::2");
		}
	};


	var int64 co_id;


    co_id = launch local_job_value_0.FuncField();
	fmt::printf("co_id: {}\n", co_id);

	fmt::println("main::1");

	resume(co_id);

	fmt::println("main::2");
	resume(co_id);

	fmt::println("main::3");


}