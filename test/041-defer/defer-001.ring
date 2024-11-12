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


@main
function main() {

	test();
	
	fmt::printf("main end\n");
}

function test() {
	defer function() {
		fmt::printf("defer 1\n");
		destory_func();
	}();

	defer function() {
		fmt::printf("defer 2\n");
		destory_func();
	}();
	

	fmt::printf("test begin\n");
	fmt::printf("test end\n");
}

function destory_func() {
	fmt::printf("destory_func\n");
}
