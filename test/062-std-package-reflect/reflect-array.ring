package main

import {
	fmt;
    debug;
	reflect;
}

typedef FuncType = fn();

	
fn main() {
	var bool[]     bool_array;
	var int[]      int_array;
	var int64[]    int64_array;
	var double[]   double_array;
	var string[]   string_array;
	var FuncType[] func_array;

	fmt::println(reflect::typeof(bool_array));
	fmt::println(reflect::typeof(int_array));
	fmt::println(reflect::typeof(int64_array));
	fmt::println(reflect::typeof(double_array));
	fmt::println(reflect::typeof(string_array));
	fmt::println(reflect::typeof(func_array));
}