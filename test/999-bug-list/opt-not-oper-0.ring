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
fn main() {
	var bool local_bool_value_0;

	local_bool_value_0 = not false;
	fmt::println(local_bool_value_0);
	fmt::println(not false);

	local_bool_value_0 = not true;
	fmt::println(local_bool_value_0);
	fmt::println(not true);
}