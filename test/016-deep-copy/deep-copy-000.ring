package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	// test_deep_copy_int();
	test_deep_copy_array();
	test_deep_copy_class();
}

fn test_deep_copy_int() {
	var int local_int_value_0 = 0;
	test_fn_int_as_param(local_int_value_0);

	debug::assert(local_int_value_0 == 0);
	fmt::printf("local_int_value_0 = {}\n", local_int_value_0);
}
fn test_fn_int_as_param(var int int_value) {
	int_value = 1;
}


// ------------- 数组的深度copy
fn test_deep_copy_array() {
	fmt::printf("\ntest_deep_copy_array--------------\n");
	var int[] local_int_array_0 = new int[10];


	test_fn_array_as_param(local_int_array_0);

	debug::assert(local_int_array_0[0] == 0);
	fmt::printf("local_int_array_0 = {}\n", local_int_array_0);
}

// 这里 shallow copy，传递的是指针，修改数组中的元素会修改原始数组中的元素
fn test_fn_array_as_param(var int[] int_array) {
	int_array[0] = 1;
	fmt::printf("test_fn_array_as_param int_array = {}\n", int_array);
}


// ------------- 类的深度copy
// 默认空间 1+4+8+8+8=29
typedef Job1 = class {
	var bool    Bool;
	var int     Int;
	var int64   Int64;
	var double  Double;
	var string  String;
}
fn test_deep_copy_class() {
	fmt::printf("\ntest_deep_copy_class--------------\n");

	var Job1 local_job1_value_0;

	test_fn_class_as_param(local_job1_value_0);

	debug::assert(local_job1_value_0.Bool == false);
	fmt::printf("local_job1_value_0 = {}\n", local_job1_value_0);

}
// 这里 shallow copy，传递的是指针，修改field 会影响外层的变量
fn test_fn_class_as_param(var Job1 job1_value) {
	job1_value.Bool = true;
	fmt::printf("test_fn_class_as_param job1_value = {}\n", job1_value);
}