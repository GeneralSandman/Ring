//
// File:    int-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

@main
function main() {
	var int int_value;
	fmt::println_int(int_value);
	debug::debug_assert(int_value == 0);

}