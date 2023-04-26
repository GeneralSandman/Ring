
package main

import {
	fmt;
	debug;
}

@main
function main() {


	debug::debug_assert(true or true);
	if(true or true) {
		fmt::println_string("check (true or true) pass");
	} else {
		fmt::println_string("check (true or true) [failed]");
	}


	fmt::println_string("");

	debug::debug_assert(false or true);
	if(false or true) {
		fmt::println_string("check (false or true) pass");
	} else {
		fmt::println_string("check (false or true) [failed]");
	}

	fmt::println_string("");

	debug::debug_assert(true or false);
	if(true or false) {
		fmt::println_string("check (true or false) pass");
	} else {
		fmt::println_string("check (true or false) [failed]");
	}

	fmt::println_string("");
	if(false or false) {
		fmt::println_string("check (false or false) [failed]");
	} else {
		fmt::println_string("check (false or false) pass");
	}

}
