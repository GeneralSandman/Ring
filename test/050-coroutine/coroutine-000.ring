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


function job_action() {
	fmt::println("job_action::1");

	yield();

	fmt::println("job_action::2");

	return;
}

@main
function main() {

	// job_action();


	var int64 co_id;


    co_id = launch(job_action);

	fmt::println("main::1");
	resume(co_id);

	fmt::println("main::2");
	resume(co_id);

	fmt::println("main::3");
}