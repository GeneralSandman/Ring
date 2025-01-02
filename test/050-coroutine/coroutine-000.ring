//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	os;
	debug;
	fmt;
}


fn job_action1() {
	fmt::println("job_action1::1");
	job_action2();
	fmt::println("job_action1::2");
}

fn job_action2() {
	fmt::println("job_action2::1");
	fmt::println("job_action2::2");
}

fn main() {


	launch job_action1();

	fmt::println("main::1");
	fmt::println("main::2");
	fmt::println("main::3");


	fmt::println("-----------");

	job_action1();
}