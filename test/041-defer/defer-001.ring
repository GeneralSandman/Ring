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
fn main() {

	test();
	
	fmt::printf("main end\n");
}

fn test() {
	defer fn() {
		fmt::printf("defer 1\n");
		destory_func();
	}();

	defer fn() {
		fmt::printf("defer 2\n");
		destory_func();
	}();
	

	fmt::printf("test begin\n");
	fmt::printf("test end\n");
}

fn destory_func() {
	fmt::printf("destory_func\n");
}
