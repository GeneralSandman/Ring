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

typedef class Job {
    field bool    Bool;
    field int     Int;
    field int64   Int64;
    field double  Double;
    field string  String;
}

global {
	var bool   global_bool_value_1;
	var int    global_int_value_1;
  var int64  global_int64_value_1;
	var double global_double_value_1;
	var string global_string_value_1;
	var Job    global_job_class_value_1;

  var bool[]   global_bool_array_1;
  var int[]    global_int_array_1;
  var int64[]  global_int64_array_1;
  var double[] global_double_array_1;
  var string[] global_string_array_1;
  var Job[]    global_job_array_1;

  var bool[,]   global_bool_array_2;
  var int[,]    global_int_array_2;
  var int64[,]  global_int64_array_2;
  var double[,] global_double_array_2;
  var string[,] global_string_array_2;
  var Job[,]    global_job_array_2;

  var bool[,,]   global_bool_array_3;
  var int[,,]    global_int_array_3;
  var int64[,,]  global_int64_array_3;
  var double[,,] global_double_array_3;
  var string[,,] global_string_array_3;
  var Job[,,]    global_job_array_3;

  var bool[,,,]   global_bool_array_4;
  var int[,,,]    global_int_array_4;
  var int64[,,,]  global_int64_array_4;
  var double[,,,] global_double_array_4;
  var string[,,,] global_string_array_4;
  var Job[,,,]    global_job_array_4;
}

@main
function main() {
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


  fmt::println_string("\ntest case array one dimension");
  fmt::println_string(reflect::typeof(global_bool_array_1));
  fmt::println_string(reflect::typeof(global_int_array_1));
  fmt::println_string(reflect::typeof(global_int64_array_1));
  fmt::println_string(reflect::typeof(global_double_array_1));
  fmt::println_string(reflect::typeof(global_string_array_1));
  fmt::println_string(reflect::typeof(global_job_array_1));


  fmt::println_string("\ntest case array two dimension");
  fmt::println_string(reflect::typeof(global_bool_array_2));
  fmt::println_string(reflect::typeof(global_int_array_2));
  fmt::println_string(reflect::typeof(global_int64_array_2));
  fmt::println_string(reflect::typeof(global_double_array_2));
  fmt::println_string(reflect::typeof(global_string_array_2));
  fmt::println_string(reflect::typeof(global_job_array_2));


  fmt::println_string("\ntest case array three dimension");
  fmt::println_string(reflect::typeof(global_bool_array_3));
  fmt::println_string(reflect::typeof(global_int_array_3));
  fmt::println_string(reflect::typeof(global_int64_array_3));
  fmt::println_string(reflect::typeof(global_double_array_3));
  fmt::println_string(reflect::typeof(global_string_array_3));
  fmt::println_string(reflect::typeof(global_job_array_3));


  fmt::println_string("\ntest case array four dimension");
  fmt::println_string(reflect::typeof(global_bool_array_4));
  fmt::println_string(reflect::typeof(global_int_array_4));
  fmt::println_string(reflect::typeof(global_int64_array_4));
  fmt::println_string(reflect::typeof(global_double_array_4));
  fmt::println_string(reflect::typeof(global_string_array_4));
  fmt::println_string(reflect::typeof(global_job_array_4));


  fmt::println_string("\ntest case array four dimension 2");
  global_bool_array_4 = new bool[1,2,3,4];
  fmt::println_string(reflect::typeof(global_bool_array_4));
  fmt::println_string(reflect::typeof(global_bool_array_4[0]));
  fmt::println_string(reflect::typeof(global_bool_array_4[0,1]));
  fmt::println_string(reflect::typeof(global_bool_array_4[0,1,2]));
  fmt::println_string(reflect::typeof(global_bool_array_4[0,1,2,3]));

}
