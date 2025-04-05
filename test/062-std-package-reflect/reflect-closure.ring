package main

import {
	fmt;
    debug;
	reflect;
}

typedef FuncType = fn();

	
fn main() {
	var FuncType func_value;

	fmt::println(reflect::typeof(func_value));

	func_value = fn() {
	};
	fmt::println(reflect::typeof(func_value));
}