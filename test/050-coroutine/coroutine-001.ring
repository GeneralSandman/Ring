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


function job_action1() {
	fmt::println("            job_action1::1");
	job_action2();
	fmt::println("            job_action1::2");
}

function job_action2() {
	fmt::println("            job_action2::1");
	yield();
	fmt::println("            job_action2::2");
}

@main
function main() {

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