package main

import {
    fmt;
    debug;
    runtime;
}


// 默认空间 1+4+8+8+8=29
typedef Job0 = class {
    var bool    Bool;
    var int     Int;
    var int64   Int64;
    var double  Double;
	var string  String;
}

// 默认空间 1+4+8+8+8=29
typedef Job1 = class {
  	var bool    Bool;
  	var int     Int;
  	var int64   Int64;
  	var double  Double;
	var string  String;

	var Job0    Job0Value;
}

fn main() {

	test_class_0();
	runtime::gc();
	debug::assert(runtime::heap_size() == 0L);

	test_class_1();
	runtime::gc();
	debug::assert(runtime::heap_size() == 0L);

	test_class_2();
	runtime::gc();
	debug::assert(runtime::heap_size() == 0L);
}

fn test_class_0() {
	fmt::printf("test_class_0 ------------\n");
	
	var Job0 local_job0_value;

	debug::assert(runtime::heap_size() == 29L);
}

fn test_class_1() {
	fmt::printf("test_class_1 ------------\n");
	
	var Job1 local_job1_value; // 58

	debug::assert(runtime::heap_size() == 58L);
}

fn test_class_2() {
	fmt::printf("test_class_2 ------------\n");
	
	var Job0 local_job0_value; // 29
	var Job1 local_job1_value; // 58

	debug::assert(runtime::heap_size() == 87L);

	// FIXME:
	// shallow copy
	// Job0Value 相当于一个指针
	local_job1_value.Job0Value = local_job0_value;

	local_job0_value.Bool = true;
	local_job0_value.Int = 1;
	fmt::printf("local_job0_value:{} local_job1_value:{}\n", local_job0_value, local_job1_value);

	debug::assert(runtime::heap_size() == 87L); // 内存没有增加

	runtime::gc(); // local_job1_value 引用的老的 Job0Value 被回收
	debug::assert(runtime::heap_size() == 58L);

}