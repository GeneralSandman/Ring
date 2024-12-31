//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

// minus 符号
@main
fn main() {
	var int local_int_value_0;

	local_int_value_0 = true ? 1 : 2;
	fmt::println(local_int_value_0);

	local_int_value_0 = false ? 1 : 2;
	fmt::println(local_int_value_0);

}