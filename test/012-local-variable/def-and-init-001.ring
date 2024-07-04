package main

import {
	fmt;
	debug;
}

global {
	
}

typedef class Job1 {
    field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;
}


@main
function main() {

	var bool   local_bool_value_0,   local_bool_value_1   = true, false;
	var int    local_int_value_0,    local_int_value_1    = 1, 2;
	var int64  local_int64_value_0,  local_int64_value_1  = 655367L, 655368L;
	var double local_double_value_0, local_double_value_1 = 655367655367.0, 655367655367.123;
	var string local_string_value_0, local_string_value_1 = "ring-v0.2.14-release", "ring-v0.2.14-beta";
	var Job1   local_job1_value_0,   local_job1_value_1   = 
		Job1{
			Bool:   true,
			Int:    1,
			Int64:  2L,
			Double: 3.0,
			String: "local_job1_value_0",
		},
		Job1{
			Bool:   false,
			Int:    11,
			Int64:  12L,
			Double: 13.0,
			String: "local_job1_value_1",
		};

	fmt::println(local_bool_value_0,   local_bool_value_1);
	fmt::println(local_int_value_0,    local_int_value_1);
	fmt::println(local_int64_value_0,  local_int64_value_1);
	fmt::println(local_double_value_0, local_double_value_1);
	fmt::println(local_string_value_0, local_string_value_1);
	fmt::println(local_job1_value_0,   local_job1_value_1);

}