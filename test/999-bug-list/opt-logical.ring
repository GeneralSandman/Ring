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

	local_bool_value_0 = false and false;
	fmt::println(local_bool_value_0);

	local_bool_value_0 = true and false;
	fmt::println(local_bool_value_0);

	local_bool_value_0 = false and true;
	fmt::println(local_bool_value_0);

	local_bool_value_0 = true and true;
	fmt::println(local_bool_value_0);


	local_bool_value_0 = false or false;
	fmt::println(local_bool_value_0);

	local_bool_value_0 = true or false;
	fmt::println(local_bool_value_0);

	local_bool_value_0 = false or true;
	fmt::println(local_bool_value_0);

	local_bool_value_0 = true or true;
	fmt::println(local_bool_value_0);
}