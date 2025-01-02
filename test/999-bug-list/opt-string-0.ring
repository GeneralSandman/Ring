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

fn main() {
	var string local_string_value_0;
	local_string_value_0 = "123" .. "456";
	fmt::println(local_string_value_0);

	local_string_value_0 = "123" .. "456" .. "789";
	fmt::println(local_string_value_0);
}