//
// File:    package-001.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	fmt;
	debug;
}

@main
function main() {
	fmt::println_bool(true);
	fmt::println_int(123);
	fmt::println_double(123.456);
	fmt::println_string("hello world");

	debug::debug_assert(true == true);
	debug::debug_assert(true == false);
}