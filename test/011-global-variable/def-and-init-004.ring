package main

import {
	fmt;
	debug;
}


global {
	var int global_count;


	var int global_int_value_0                                         = get_next_global_count_1();
	var int global_int_value_1, global_int_value_2                     = get_next_global_count_2();
	var int global_int_value_3, global_int_value_4, global_int_value_5 = get_next_global_count_3();

	
}

fn get_next_global_count_1() -> (int) {
	var int tmp0 = global_count;
	fmt::printf("invoke get_next_global_count_1\n");
	global_count = global_count + 1;
    return tmp0;
}

fn get_next_global_count_2() -> (int, int) {
	var int tmp0, tmp1 = global_count, global_count+1;
	fmt::printf("invoke get_next_global_count_2\n");
	global_count = global_count + 2;
    return tmp0, tmp1;
}

fn get_next_global_count_3() -> (int, int, int) {
	var int tmp0, tmp1, tmp2 = global_count, global_count+1, global_count+2;
	fmt::printf("invoke get_next_global_count_3\n");
	global_count = global_count + 3;
    return tmp0, tmp1, tmp2;
}

// TestDetail: 测试 int 类型变量的定义和初始化
// TestDetail: 初始化表达式为函数调用
// TestDetail: 初始 初始化的顺序是否正确
@main
fn main() {
	fmt::println("main::start");
	
	var int local_int_value_0                                       = get_next_global_count_1();
	var int local_int_value_1, local_int_value_2                    = get_next_global_count_2();
	var int local_int_value_3, local_int_value_4, local_int_value_5 = get_next_global_count_3();

	debug::assert(global_int_value_0 == 0);
	debug::assert(global_int_value_1 == 1);
	debug::assert(global_int_value_2 == 2);
	debug::assert(global_int_value_3 == 3);
	debug::assert(global_int_value_4 == 4);
	debug::assert(global_int_value_5 == 5);

	debug::assert(local_int_value_0 == 6);
	debug::assert(local_int_value_1 == 7);
	debug::assert(local_int_value_2 == 8);
	debug::assert(local_int_value_3 == 9);
	debug::assert(local_int_value_4 == 10);
	debug::assert(local_int_value_5 == 11);


}