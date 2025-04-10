package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}

fn main() {
	test_range_bool_array_literal();

	test_range_bool();
	test_range_class();

	test_range_class_field();

}

fn test_range_bool() {
	fmt::printf("test_range_bool -------------\n");

	var int index;
	var bool   bool_tmp;
	var bool[] array_tmp;

	var bool[,] bool_array_2 = bool[,] {
		bool[] {false, true},
		bool[] {true,  false},
	};

	for(array_tmp in range bool_array_2) {
		fmt::printf("value = {}\n", array_tmp);
	}

	for(bool_tmp in range bool_array_2[0]) {
		fmt::printf("value = {}\n", bool_tmp);
	}
	for(bool_tmp in range bool_array_2[1]) {
		fmt::printf("value = {}\n", bool_tmp);
	}
}

fn test_range_bool_array_literal() {
	fmt::printf("test_range_bool_array_literal -------------\n");
	
	var bool bool_tmp;

	for(bool_tmp in range bool[]{false, true, false, true}) {
		fmt::printf("value = {}\n", bool_tmp);
	}
}

typedef Job0 = class {
    var bool    Bool;
    var int     Int;
    var int64   Int64;
    var double  Double;
}
fn test_range_class() {
	fmt::printf("test_range_class -------------\n");
	var Job0   class_tmp;
	var Job0[] array_tmp;

	var Job0[,] local_class_array_0 = Job0[,] {
		Job0[]{
			Job0{
				Bool: false,
				Int: 0,
				Int64: 0L,
				Double: 0.0,
			},
			Job0{
				Bool: true,
				Int: 1,
				Int64: 1L,
				Double: 1.0,
			},
		},
		Job0[]{
			Job0{
				Bool: true,
				Int: 2,
				Int64: 2L,
				Double: 2.0,
			},
			Job0{
				Bool: false,
				Int: 3,
				Int64: 3L,
				Double: 3.0,
			},
		},
	};

	for(array_tmp in range local_class_array_0) {
		fmt::printf("value = {}\n", array_tmp);
	}

	for(class_tmp in range local_class_array_0[0]){
		fmt::printf("value = {}\n", class_tmp);
	}
	for(class_tmp in range local_class_array_0[1]){
		fmt::printf("value = {}\n", class_tmp);
	}

}


typedef Job1 = class {
	var int[] IntArray;
}

fn test_range_class_field() {
	fmt::printf("test_range_class_field -------------\n");

	var Job1 local_class_value_0 = Job1{
		IntArray: int[]{1, 2, 3, 4, 5},
	};

	var int int_tmp;

	for(int_tmp in range local_class_value_0.IntArray) {
		fmt::printf("value = {}\n", int_tmp);
	}
}