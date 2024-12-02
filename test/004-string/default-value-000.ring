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
	var string string_value;
	fmt::println_string(string_value);
	debug::assert(string_value == "");
}