
package main

import {
	fmt;
	debug;
}

@main
function main() {

	debug::assert(2 > 1);
	if(2>1) {
		fmt::println_string("check 2>1 pass");
	} else {
		fmt::println_string("check 2>1 [failed]");
	}

	fmt::println_string("");

	if(2<1) {
		fmt::println_string("check 2<1 [failed]");
	} else {
		fmt::println_string("check 2<1 pass");
	}


}
