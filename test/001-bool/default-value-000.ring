//
// File:    int-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

@main
function main() {
	var bool bool_value;
	fmt::println_bool(bool_value);
	debug::debug_assert(bool_value == false);
}