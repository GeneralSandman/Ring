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

global {
	var int64 job_action3_co_id;
}


fn job_action1() {
	fmt::println("            job_action1::1");
	job_action2();
	fmt::println("            job_action1::2");
}

fn job_action2() {
	fmt::println("            job_action2::1");
	yield();
	job_action3_co_id = launch job_action3();
	resume(job_action3_co_id);
	fmt::println("            job_action2::2");
	resume(job_action3_co_id);

}

fn job_action3() {
	fmt::println("                job_action3::1");
	job_action4();
	fmt::println("                job_action3::2");

}

fn job_action4() {
	fmt::println("                job_action4::1");
	yield();
	fmt::println("                job_action4::2");
}

@main
fn main() {

	var int64 co_id;


    co_id = launch job_action1();
	fmt::printf("co_id: {}\n", co_id);

	fmt::println("main::1");

	resume(co_id);

	fmt::println("main::2");
	// resume(co_id);

	fmt::println("main::3");

	resume(co_id);

	fmt::println("main::4");

	resume(co_id); // 无效果

}