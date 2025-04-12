package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	var bool bool_value;
	var int int_value;

	int_value = test() ? 11 : 22;
	fmt::println(int_value);

}

fn test() {

}