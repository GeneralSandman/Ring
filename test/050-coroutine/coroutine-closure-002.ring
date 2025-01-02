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

fn main() {
	var int64 co_id;


	fmt::println("main::0");
	

	co_id = launch fn() {
		fmt::println("    coroutine action::1");
		yield();
		fmt::println("    coroutine action::2");
	}();
	fmt::printf("co_id: {}\n", co_id);


	fmt::println("main::1");

	resume(co_id);

	fmt::println("main::2");

	resume(co_id);

	fmt::println("main::3");
}