package main

import {
	fmt;
	reflect;
}

typedef fn() FuncType;

// TestDetail: array中的元素为匿名函数变量
fn main() {
	var FuncType[] local_array_func;
	var FuncType   local_value_func;

	
	fmt::println(local_array_func); // pass
	fmt::println(reflect::typeof(local_array_func)); // pass closure[!1] 后续需要优化一下
	fmt::println(len(local_array_func)); // pass
	fmt::println(capacity(local_array_func)); // pass


	push(local_array_func, fn(){
		fmt::println("local_array_func item 0");
	});
	push(local_array_func, fn(){
		fmt::println("local_array_func item 1");
	});
	push(local_array_func, fn(){
		fmt::println("local_array_func item 2");
	});
	push(local_array_func, fn(){
		fmt::println("local_array_func item 3");
	});
	push(local_array_func, fn(){
		fmt::println("local_array_func item 4");
	});

	fmt::println(local_array_func);
	fmt::println(len(local_array_func));
	fmt::println(capacity(local_array_func));


	// pass
	for(local_value_func in range local_array_func) {
		local_value_func();
	}


	local_value_func = pop(local_array_func);
	local_value_func();
	local_value_func = pop(local_array_func);
	local_value_func();
	local_value_func = pop(local_array_func);
	local_value_func();
	local_value_func = pop(local_array_func);
	local_value_func();
	local_value_func = pop(local_array_func);
	local_value_func();

}