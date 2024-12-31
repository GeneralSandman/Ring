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
fn main() {
	var int int_value;
	fmt::println_int(int_value);
	debug::assert(int_value == 0);

}