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

fn main() {
	var double double_value;
	fmt::println_double(double_value);
	debug::assert(double_value == 0.0);
}