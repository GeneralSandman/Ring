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

	fmt::printf("main begin\n");

	test();
	
	fmt::printf("main end\n");
}

function test() {

	fmt::printf("test begin\n");


	defer function() {
		
		fmt::printf("defer 1 begin\n");
		
		defer function() {
			fmt::printf("    defer 1 --- defer\n");
		}();

		fmt::printf("defer 1 end\n");
	}();


	defer function() {
		
		fmt::printf("defer 2 begin\n");
		
		defer function() {
			fmt::printf("    defer 2 --- defer\n");
		}();

		fmt::printf("defer 2 end\n");
	}();

	
	

	fmt::printf("test end\n");
}
