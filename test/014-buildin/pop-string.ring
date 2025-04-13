package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	test_pop_0();
	test_pop_1();
}

// test pass
fn test_pop_0() {
	fmt::printf("test_pop_0 -------\n");

	test_pop_0_();

	runtime::gc();
	fmt::printf("heap_size: {}\n", runtime::heap_size());
	debug::assert(runtime::heap_size() == 0L);
}
fn test_pop_0_() {
	var string[] array = new string[8];


	runtime::gc();
	fmt::printf("heap_size: {}\n", runtime::heap_size());
	debug::assert(runtime::heap_size() == 64L); // 8*8


	// test_pop_0_ test_pop_1_ 的区别
	pop(array);
	runtime::gc();
	fmt::printf("heap_size: {}\n", runtime::heap_size());
	debug::assert(runtime::heap_size() == 56L); // 7*8
	
}



// test pass
fn test_pop_1() {
	fmt::printf("test_pop_1 -------\n");

	test_pop_1_();

	runtime::gc();
	fmt::printf("heap_size: {}\n", runtime::heap_size());
	debug::assert(runtime::heap_size() == 0L);
}
fn test_pop_1_() {
	var string[] array = new string[8];
	var string tmp;


	runtime::gc();
	fmt::printf("heap_size: {}\n", runtime::heap_size());
	debug::assert(runtime::heap_size() == 72L); // 8*8 + 8


	// test_pop_0_ test_pop_1_ 的区别
	// pop(array);
	tmp = pop(array);
	runtime::gc();
	fmt::printf("heap_size: {}\n", runtime::heap_size());
	debug::assert(runtime::heap_size() == 64L); // 8*7 + 8
}