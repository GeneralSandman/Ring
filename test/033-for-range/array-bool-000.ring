package main

import {
	debug;
	fmt;
}

global {

}

@main
function main() {
	var bool[] local_bool_array_0 = new bool[10];

	var int index;
	var bool value;
	
	for(value in range local_bool_array_0) {
		fmt::println_bool(value);
	}
}