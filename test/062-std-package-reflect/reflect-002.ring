//
// File:    std-reflect-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-10-07
//

package main

import {
	fmt;
  debug;
	reflect;
}

typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;
    field string  Name;
}

// TestDetail: 通过 字符串比较的方式来比较获取 typeof
// TestDetail: reflect::typeof(bool_value) == "bool"
@main
function main() {
	var bool   bool_value;
	var int    int_value;
	var double double_value;
	var string string_value;
	var Job    job_class_value;

	fmt::println_string("test case 1");
	fmt::println_string(reflect::typeof(bool_value));
	fmt::println_string(reflect::typeof(int_value));
	fmt::println_string(reflect::typeof(double_value));
	fmt::println_string(reflect::typeof(string_value));
	fmt::println_string(reflect::typeof(job_class_value));

	fmt::println_string("test case 2");
	debug::debug_assert(reflect::typeof(bool_value)      == "bool");
	debug::debug_assert(reflect::typeof(int_value)       == "int");
	debug::debug_assert(reflect::typeof(double_value)    == "double");
	debug::debug_assert(reflect::typeof(string_value)    == "string");
	debug::debug_assert(reflect::typeof(job_class_value) == "Job");


}
