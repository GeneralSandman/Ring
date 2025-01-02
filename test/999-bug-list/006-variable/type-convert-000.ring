package main

import {
	fmt;
	debug;
}

fn main() {

var bool bool_value;
var int int_value;
var double double_value;

// int_value = 1.1; // 编译错误
// double_value = 1; // 编译错误
// print("int_value=", int_value, ", double_value=", double_value, "\n");

bool_value = true;
int_value = 1;
double_value = 1.1;
print("bool_value=", bool_value, ", int_value=", int_value, ", double_value=", double_value, "\n");


bool_value = bool(1);
int_value = int(1.1);
double_value = double(1);
print("bool_value=", bool_value, ", int_value=", int_value, ", double_value=", double_value, "\n");


bool_value = bool(1.1);
int_value = int(true);
double_value = double(true);
print("bool_value=", bool_value, ", int_value=", int_value, ", double_value=", double_value, "\n");

bool_value = bool(0.1);
int_value = int(false);
double_value = double(false);
print("bool_value=", bool_value, ", int_value=", int_value, ", double_value=", double_value, "\n");


// bool_value = not bool(0);
// int_value = int(not false); // FIXME: BUG
// double_value = double(not false);
// print("bool_value=", bool_value, ", int_value=", int_value, ", double_value=", double_value, "\n");


// bool_value = bool(-0.1);
// int_value = int(-0.1);
// double_value = double(-0.1);
// print("bool_value=", bool_value, ", int_value=", int_value, ", double_value=", double_value, "\n");

// bool_value = bool(-1.1);
// int_value = int(-1.1);
// double_value = double(-1.1);
// print("bool_value=", bool_value, ", int_value=", int_value, ", double_value=", double_value, "\n");

}