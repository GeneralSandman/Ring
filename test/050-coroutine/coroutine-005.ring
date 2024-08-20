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
	var int co_count = 10;
	var int64[] co_id_array = new int64[co_count];

	var int i;
	for(i = 0; i < co_count; i++) {
		co_id = launch job_action1();
		fmt::printf("co_id: {}\n", co_id);
		co_id_array[i] = co_id;
	}


	fmt::printf("patch resume[1]------------------------\n");
	for(i = 0; i < co_count; i++) {
		fmt::printf("resume {}\n", co_id_array[i]);
		resume(co_id_array[i]);
	}

	fmt::printf("patch resume[2]------------------------\n");
	for(i = 0; i < co_count; i++) {
		fmt::printf("resume {}\n", co_id_array[i]);
		resume(co_id_array[i]);
	}




}