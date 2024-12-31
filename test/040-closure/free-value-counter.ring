//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	os;
	debug;
	fmt;
}

typedef fn() -> (int64) FuncType1;

// TestDetail: 测试见的FreeValue , 不支持逃逸
@main
fn main() {

	var FuncType1 counter0;
	var FuncType1 counter1;
	var int64 count;

	fmt::println("------------");
	counter0 = get_counter(10L, 5L);

	count = counter0();
	fmt::printf("count = {}\n", count);
	debug::assert(count == 15L);

	count = counter0();
	fmt::printf("count = {}\n", count);
	debug::assert(count == 20L);



	fmt::println("------------");
	counter1 = get_counter(10L, 5L);

	count = counter1();
	fmt::printf("count = {}\n", count);
	debug::assert(count == 15L);

	count = counter1();
	fmt::printf("count = {}\n", count);
	debug::assert(count == 20L);


	fmt::println("+++++++++++");
	count = counter0();
	fmt::printf("count = {}\n", count);
	debug::assert(count == 25L);

	count = counter0();
	fmt::printf("count = {}\n", count);
	debug::assert(count == 30L);



	fmt::println("+++++++++++");
	count = counter1();
	fmt::printf("count = {}\n", count);
	debug::assert(count == 25L);

	count = counter1();
	fmt::printf("count = {}\n", count);
	debug::assert(count == 30L);

}

fn get_counter(var int64 begin, var int64 step) -> (FuncType1) {

	var int64 level0_local_int_value_0 = begin;

	return fn() -> (int64) {
		level0_local_int_value_0 += step;
		return level0_local_int_value_0;
	};
}


