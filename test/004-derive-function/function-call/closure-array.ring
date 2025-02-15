package main

import {
	fmt;
	reflect;
	runtime;
}

typedef FuncTypeVoid2Void = fn();
typedef FuncTypeInt2Void = fn(int);

// TestDetail: array中的元素为匿名函数变量
// TestDetail: 类似于 closure_array[0]() 的直接调用
fn main() {

	test0();

	test1();

}

fn test0() {
	fmt::printf("\ntest0------------------\n");

	var FuncTypeVoid2Void[] local_array_func;

    push(local_array_func, fn(){
        fmt::printf("FuncTypeVoid2Void local_array_func item 0\n");
        // runtime::print_call_stack(); // 这里会打印closure指针，暂时不测试，目前是正确的
	});
	push(local_array_func, fn(){
        fmt::printf("FuncTypeVoid2Void local_array_func item 1\n");
        // runtime::print_call_stack(); // 这里会打印closure指针，暂时不测试，目前是正确的
	});

	local_array_func[0]();
	local_array_func[1]();
}


fn test1() {
	fmt::printf("\ntest1------------------\n");

	var FuncTypeInt2Void[] local_array_func;

    push(local_array_func, fn(var int int_value){
        fmt::printf("FuncTypeInt2Void local_array_func item 0, int_value: {}\n", int_value);
        // runtime::print_call_stack(); // 这里会打印closure指针，暂时不测试，目前是正确的
	});
	push(local_array_func, fn(var int int_value){
        fmt::printf("FuncTypeInt2Void local_array_func item 1, int_value: {}\n", int_value);
        // runtime::print_call_stack(); // 这里会打印closure指针，暂时不测试，目前是正确的
	});

	local_array_func[0](1);
	local_array_func[0](2);
	local_array_func[1](3);
	local_array_func[1](4);
}
