package main

import {
	debug;
	fmt;
}

global {

}

@main
function main() {
	var int[] local_int_array_0 = int[]{1,2,3,4,5,6,7,8,9,0};

	var int index;
	var int value;

	for(index=0; index<10; index++) {
		fmt::println_int(local_int_array_0[index]);
	}

	fmt::println_string("------------");
	
	for(value in range local_int_array_0) {
		fmt::println_int(value);
	}
}