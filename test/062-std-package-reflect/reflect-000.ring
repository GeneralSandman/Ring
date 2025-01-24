//
// File:    std-reflect-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-10-07
//

package main

import {
	fmt;
  debug;
	reflect;
}

typedef Job = class {
    var bool    Bool;
    var int     Int;
    var int64   Int64;
    var double  Double;
    var string  String;
}

global {
	var bool   global_bool_value_1;
	var int    global_int_value_1;
	var int64  global_int64_value_1;
	var double global_double_value_1;
	var string global_string_value_1;
	var Job    global_job_class_value_1;
}

fn main() {
	var bool   bool_value;
	var int    int_value;
	var int64  int64_value;
	var double double_value;
	var string string_value;
	var Job    job_class_value;

	fmt::println_string("test case 1");
	fmt::println_string(reflect::typeof(bool_value));
	fmt::println_string(reflect::typeof(int_value));
	fmt::println_string(reflect::typeof(int64_value));
	fmt::println_string(reflect::typeof(double_value));
	fmt::println_string(reflect::typeof(string_value));
	fmt::println_string(reflect::typeof(job_class_value));


	fmt::println_string("\ntest case 2");
	fmt::println_string(reflect::typeof(global_bool_value_1));
	fmt::println_string(reflect::typeof(global_int_value_1));
	fmt::println_string(reflect::typeof(global_int64_value_1));
	fmt::println_string(reflect::typeof(global_double_value_1));
	fmt::println_string(reflect::typeof(global_string_value_1));
	fmt::println_string(reflect::typeof(global_job_class_value_1));


	fmt::println_string("\ntest case 3");
	fmt::println_string(reflect::typeof(global_job_class_value_1.Bool));
	fmt::println_string(reflect::typeof(global_job_class_value_1.Int));
	fmt::println_string(reflect::typeof(global_job_class_value_1.Int64));
	fmt::println_string(reflect::typeof(global_job_class_value_1.Double));
	fmt::println_string(reflect::typeof(global_job_class_value_1.String));


}
