package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	test();
}

// fn test_not_define() {
// 	a[1];
// }

// fn test_not_array() {
// 	var int a;
// 	a[1];
// }

// fn test_invalid_dimension() {
// 	var int[] a;
// 	a[1,1];
// }

fn test() {
	var int[,,] array = new int[3,3,3];

	fmt::println(reflect::typeof(array[0]));
}