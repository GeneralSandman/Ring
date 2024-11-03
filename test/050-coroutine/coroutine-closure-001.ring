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


typedef function() FuncType;

@main
function main() {
	var int64 co_id;


	co_id = launch function() {
		fmt::println(" coroutine action::1");
		yield();
		fmt::println(" coroutine action::2");
	}();

	resume(co_id);

	resume(co_id);
}