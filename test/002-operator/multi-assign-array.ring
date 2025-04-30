package main

import {
	fmt;
	debug;
	reflect;
}


// TestDetail: 同时定义多个数组并且 初始化
fn main() {
	test0();

	test1();

}

fn test0() {
	fmt::printf("test0-------------------\n");

	var int[] local_int_array_0, local_int_array_1 = new int[8], new int[16];

	fmt::println(reflect::typeof(local_int_array_0));
	fmt::println(len(local_int_array_0));
	fmt::println(cap(local_int_array_0));
	fmt::println(local_int_array_0);

	fmt::println(reflect::typeof(local_int_array_1));
	fmt::println(len(local_int_array_1));
	fmt::println(cap(local_int_array_1));
	fmt::println(local_int_array_1);

}

fn test1() {
	fmt::printf("test1-------------------\n");
	
	var int[] local_int_array_0, local_int_array_1 = 
		int[]{1,2,3,4,5,6,7,8}, 
		int[]{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

	fmt::println(reflect::typeof(local_int_array_0));
	fmt::println(len(local_int_array_0));
	fmt::println(cap(local_int_array_0));
	fmt::println(local_int_array_0);

	fmt::println(reflect::typeof(local_int_array_1));
	fmt::println(len(local_int_array_1));
	fmt::println(cap(local_int_array_1));
	fmt::println(local_int_array_1);
}

