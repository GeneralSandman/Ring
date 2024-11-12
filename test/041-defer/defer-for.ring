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
	var int int_value = 0;

	for(int_value = 0; int_value < 10; int_value++) {
		defer function() {
			fmt::printf("defer closure\n");
		}();
	}
	

	fmt::printf("test begin\n");
	fmt::printf("test end\n");
}

