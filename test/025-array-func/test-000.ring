package main

import {
	fmt;
	reflect;
}

typedef fn() FuncType;

fn main() {
	var FuncType[] local_array_func;
	var FuncType   local_value_func;

	
	fmt::println(local_array_func); // pass
	fmt::println(reflect::typeof(local_array_func)); // 这里panic了
	fmt::println(len(local_array_func)); // pass
	fmt::println(capacity(local_array_func)); // pass


	push(local_array_func, fn(){
		fmt::println("local_array_func item 1");
	});
	push(local_array_func, fn(){
		fmt::println("local_array_func item 2");
	});
	// fmt::println(local_array_func);
	// fmt::println(len(local_array_func));
	// fmt::println(capacity(local_array_func));


	// 还不支持
	// for(local_value_func in range local_array_func) {
	// 	local_value_func();
	// }


	local_value_func = pop(local_array_func);
	local_value_func();
	local_value_func = pop(local_array_func);
	local_value_func();

}