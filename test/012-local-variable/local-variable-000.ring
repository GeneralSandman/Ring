package main

import {
	fmt;
	debug;
}

global {
	
}

fn main() {
	var bool   local_bool_value_1;
	var int    local_int_value_1;
	var int64  local_int64_value_1;
	var double local_double_value_1;
	var string local_string_value_1;
	
	fmt::println_string("test case 1");
	fmt::println_bool(local_bool_value_1);
	fmt::println_int(local_int_value_1);
	fmt::println_int64(local_int64_value_1);
	fmt::println_double(local_double_value_1);
	fmt::println_string(local_string_value_1);


	fmt::println_string("\ntest case 2");
	local_bool_value_1   = true;
	local_int_value_1    = 2;
	local_int64_value_1  = 2L;
	local_double_value_1 = 3.0;
	local_string_value_1 = "4";

	fmt::println_bool(local_bool_value_1);
	fmt::println_int(local_int_value_1);
	fmt::println_int64(local_int64_value_1);
	fmt::println_double(local_double_value_1);
	fmt::println_string(local_string_value_1);
}