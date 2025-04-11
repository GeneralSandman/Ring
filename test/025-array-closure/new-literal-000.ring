package main

import {
	fmt;
	reflect;
}

typedef FuncType = fn();

// TestDetail: array中的元素为匿名函数变量
fn main() {
	var FuncType[] local_array_func;
	var FuncType   local_value_func;

	fmt::printf("\ntest new closure literal array-------\n");
	local_array_func = FuncType[] {
		fn(){
			fmt::println("local_array_func item 0, array-clsoure-literal");
		},
		fn(){
			fmt::println("local_array_func item 1, array-clsoure-literal");
		},
		fn(){
			fmt::println("local_array_func item 2, array-clsoure-literal");
		},
		fn(){
			fmt::println("local_array_func item 3, array-clsoure-literal");
		},
	};
	// 是指针，不太好测试
	// fmt::println(local_array_func); // [closure(0x15172d460) closure(0x15172d478) closure(0x15172d490) closure(0x15172d4a8)]
	fmt::println(len(local_array_func)); // 4
	fmt::println(cap(local_array_func)); // 8

	// pass
	fmt::printf("\ntest range closure array-------\n");
	for(local_value_func = range local_array_func) {
		local_value_func();
	}
}