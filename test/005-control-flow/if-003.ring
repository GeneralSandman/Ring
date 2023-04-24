
package main

import {
	fmt;
	debug;
}

@main
function main() {


debug::debug_assert(true and true);
if(true and true) {
	fmt::println_string("check (true and true) pass");
} else {
	fmt::println_string("check (true and true) [failed]");
}


fmt::println_string("");
if(true and false) {
	fmt::println_string("check (true and false) [failed]");
} else {
	fmt::println_string("check (true and false) pass");
}

fmt::println_string("");
if(false and true) {
	fmt::println_string("check (false and true) [failed]");
} else {
	fmt::println_string("check (false and true) pass");
}

fmt::println_string("");
if(false and false) {
	fmt::println_string("check (false and false) [failed]");
} else {
	fmt::println_string("check (false and false) pass");
}

}
