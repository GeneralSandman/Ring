//
// File:    string-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

// minus 符号
@main
function main() {
	var int local_int_value_0;
	var int64 local_int64_value_0;
	var double local_double_value_0;

	local_int_value_0 = -1;
	fmt::println(local_int_value_0);

	local_int64_value_0 = -1L;
	fmt::println(local_int64_value_0);

	local_double_value_0 = -1.234;
	fmt::println(local_double_value_0);
}