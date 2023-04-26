
package main

import {
	fmt;
	debug;
}

@main
function main() {


	var bool bool_value;

	bool_value = true;
	fmt::println_bool(bool_value);
	debug::debug_assert(bool_value == true);
	if(bool_value) {
		fmt::println_string("bool_value is true");
	} else {
		fmt::println_string("bool_value is false [FAILED]");
	}
	fmt::println_bool(bool_value);
	debug::debug_assert(bool_value == true);


	fmt::println_string("");

	bool_value = true;
	fmt::println_bool(not bool_value);
	debug::debug_assert(not bool_value == false);
	if(not bool_value) {
		fmt::println_string("not bool_value is true [FAILED]");
	} else {
		fmt::println_string("not bool_value is false");
	}
	fmt::println_bool(not bool_value);
	debug::debug_assert(not bool_value == false);


	fmt::println_string("");
	fmt::println_string("");



	bool_value = false;
	fmt::println_bool(bool_value);
	debug::debug_assert(bool_value == false);
	if(bool_value) {
		fmt::println_string("bool_value is true [FAILED]");
	} else {
		fmt::println_string("bool_value is false");
	}
	fmt::println_bool(bool_value);
	debug::debug_assert(bool_value == false);


	fmt::println_string("");


	bool_value = false;
	fmt::println_bool(not bool_value);
	debug::debug_assert(not bool_value == true);
	if(not bool_value) {
		fmt::println_string("bool_value is true");
	} else {
		fmt::println_string("bool_value is false [FAILED]");
	}
	fmt::println_bool(not bool_value);
	debug::debug_assert(not bool_value == true);


	fmt::println_string("");
	fmt::println_string("");


}
