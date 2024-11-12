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

	test1();

	test2();
	
	fmt::printf("main end\n");
}

function test1() {
	var int int_value = 0;

	for(int_value = 0; int_value < 10; int_value++) {
		defer function() {
			fmt::printf("test1 defer int_value={}\n", int_value);
		}();
	}
	
	fmt::printf("------------\n");
	fmt::printf("test1 begin\n");
	fmt::printf("test1 end\n");
}

function test2() {
	var int int_value = 0;

	for(int_value = 0; int_value < 10; int_value++) {
		defer function(var int int_value) {
			fmt::printf("test1 defer int_value={}\n", int_value);
		}(int_value);
	}

	fmt::printf("------------\n");
	fmt::printf("test2 begin\n");
	fmt::printf("test2 end\n");
}

