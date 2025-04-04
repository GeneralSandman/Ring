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

	
	fmt::printf("test init closure array-------\n");
	fmt::println(local_array_func); // empty array
	fmt::println(reflect::typeof(local_array_func)); // closure[!1] TODO: 后续需要优化一下
	fmt::println(len(local_array_func)); // 0
	fmt::println(cap(local_array_func)); // 0


	fmt::printf("\ntest push closure array-------\n");
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

	// 是指针，不太好测试
	// fmt::println(local_array_func); // [closure(0x7fa42a8099e0) closure(0x7fa42a8099f8) closure(0x7fa42a809a10) closure(0x7fa42a809a28) closure(0x7fa42a809a40)]
	fmt::println(reflect::typeof(local_array_func)); // closure[!1] TODO: 后续需要优化一下
	fmt::println(reflect::typeof(local_array_func[0])); // fn() -> ()
	fmt::println(len(local_array_func)); // 5
	fmt::println(cap(local_array_func)); // 8


	// pass
	fmt::printf("\ntest range closure array-------\n");
	for(local_value_func in range local_array_func) {
		local_value_func();
	}


	fmt::printf("\ntest pop closure array-------\n");
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


	fmt::printf("\ntest empty closure array-------\n");
	fmt::println(local_array_func); // empty array
	fmt::println(len(local_array_func)); // 0
	fmt::println(cap(local_array_func)); // 8


	fmt::printf("\ntest new closure array-------\n");
	local_array_func = new FuncType[5];
	fmt::println(local_array_func); // [nil nil nil nil nil]
	fmt::println(len(local_array_func)); // 5
	fmt::println(cap(local_array_func)); // 8


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
	for(local_value_func in range local_array_func) {
		local_value_func();
	}
}