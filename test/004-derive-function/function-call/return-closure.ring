package main

import {
	fmt;
	reflect;
	runtime;
}

typedef FuncTypeVoid2Void = fn();

typedef FuncTypeInt2Void = fn(int);
typedef FuncTypeInt2String = fn(int) -> (string);

// TestDetail: 函数返回匿名函数直接调用
// TestDetail: 类似于 return_closure()();
fn main() {

	test0();

	test1();

	test2();

	test3();

}

fn test0() {
	fmt::printf("\ntest0------------------\n");
	
	// 方法1
	var FuncTypeVoid2Void local_func_var;
	local_func_var = return_closure_0();
	local_func_var();


	// 方法2 与 方法1 等价
	return_closure_0()();
}
fn return_closure_0() -> (FuncTypeVoid2Void) {
	fmt::printf("return_closure_0 build closure:FuncTypeVoid2Void\n");
	return fn() {
		fmt::printf("return_closure_0 closure block\n");
		// runtime::print_call_stack(); // 这里会打印closure指针，暂时不测试，目前是正确的
	};
}


fn test1() {
	fmt::printf("\ntest1------------------\n");

	// 方法1
	var FuncTypeInt2Void local_func_var;
	local_func_var = return_closure_1();
	local_func_var(123);

	// 方法2
	return_closure_1()(456);

}
fn return_closure_1() -> (FuncTypeInt2Void) {
	fmt::printf("return_closure_1 build closure:FuncTypeInt2Void\n");
	return fn(var int int_param) {
		fmt::printf("return_closure_1 closure block receive int_param={}\n", int_param);
	};
}



fn test2() {
	fmt::printf("\ntest2------------------\n");

	var string local_string_var;

	// 方法1
	var FuncTypeInt2String local_func_var;
	local_func_var = return_closure_2();
	local_string_var = local_func_var(123);
	fmt::printf("test2 local_string_var =`{}`\n", local_string_var);

	// 方法2
	local_string_var = return_closure_2()(456);
	fmt::printf("test2 local_string_var =`{}`\n", local_string_var);

}
fn return_closure_2() -> (FuncTypeInt2String) {
	fmt::printf("return_closure_2 build closure:FuncTypeInt2String\n");
	return fn(var int int_param) -> (string) {
		fmt::printf("return_closure_2 closure block receive int_param={}\n", int_param);
		return to_string(int_param);
	};
}



// test3 稍微复杂
// return_closure_3 会有自由变量的逃逸测试
fn test3() {
	fmt::printf("\ntest3------------------\n");

	var string local_string_var;

	// 方法1
	var FuncTypeInt2String local_func_var;
	local_func_var = return_closure_3(3.14);
	local_string_var = local_func_var(1);
	fmt::printf("test3 local_string_var =`{}`\n", local_string_var);
	local_string_var = local_func_var(2);
	fmt::printf("test3 local_string_var =`{}`\n", local_string_var);

	// 方法2
	local_string_var = return_closure_3(3.1415)(3);
	fmt::printf("test3 local_string_var =`{}`\n", local_string_var);

}
fn return_closure_3(var double double_param) -> (FuncTypeInt2String) {
	fmt::printf("return_closure_3 build closure:FuncTypeInt2String\n");
	return fn(var int int_param) -> (string) {
		fmt::printf("return_closure_3 free_value double_param={}\n", double_param);
		fmt::printf("return_closure_3 receive int_param={}\n", int_param);
		return fmt::sprintf("double_param ={}, int_param={}", double_param, int_param);
	};
}