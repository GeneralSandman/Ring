package main

import {
	debug;
	fmt;
}

global {

}

@main
function main() {
	var string[] local_string_array_0 = []string{"1234567890", "123"};

	var int index;
	var string value;
	
	for(value in range local_string_array_0) {
		fmt::println_string(value);
	}
}