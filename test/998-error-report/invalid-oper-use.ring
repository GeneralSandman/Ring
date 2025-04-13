package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	
}

// 负号 只能应用在 int/int64/double
fn invalid_use_minus() {
	-return_no_value(); // error
	-false; // error
}

// not 只能应用在 bool
fn invalid_use_not() {
	not false;
	not 1; // error
	not 1.0; // error
	not return_no_value(); // error
}


fn invalid_use_increase() {
	var bool bool_value_0, bool_value_1;
	var int int_value_0, int_value_1;
	var string string_value_0;

	bool_value_0++; // error
	int_value_0++;
	string_value_0++; // error

	int_value_0 = int_value_1;
	int_value_0 = int_value_1++; // error
}

fn return_no_value() {
	return;
}