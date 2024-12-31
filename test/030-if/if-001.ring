
package main

import {
	fmt;
	debug;
}

@main
fn main() {


	var bool bool_value;

	debug::assert(true == true);
	if(true) {
		fmt::println_string("check pass");
	} else {
		fmt::println_string("check pass [failed]");
	}

	fmt::println_string("");

	debug::assert(false == false);
	if(false) {
		fmt::println_string("check pass [failed]\n");
	} else {
		fmt::println_string("check pass\n");
	}


	fmt::println_string("");
	fmt::println_string("");


	debug::assert(not false == true);
	if(not false) {
		fmt::println_string("check pass");
	} else {
		fmt::println_string("check pass [failed]");
	}

	fmt::println_string("");

	debug::assert(not true == false);
	if(not true) {
		fmt::println_string("check pass [failed]\n");
	} else {
		fmt::println_string("check pass\n");
	}


}
