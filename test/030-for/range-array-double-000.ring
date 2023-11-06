package main

import {
	debug;
	fmt;
}

global {

}

@main
function main() {
	var double[] local_double_array_0 = new double[10];

	var int index;
	var double value;
	
	for(value in range local_double_array_0) {
		fmt::println_double(value);
	}
}