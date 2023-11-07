package main

import {
	debug;
	fmt;
}

global {

}

@main
function main() {
	var int[] local_int_array_0 = new int[10];

	var int index;
	var int value;
	
	for(value in range local_int_array_0) {
		fmt::println_int(value);
	}
}