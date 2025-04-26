package main

import {
	runtime;
}

global {
	var int64 pc;
	var string file;
	var string func_name;
	var int line;
}

fn main() {



	test1();
}

fn test1() {
	test2();
}

fn test2() {
	test3();
}

fn test3() {
	pc, file, func_name, line = runtime::call_info(0);
	fmt::printf("\ncall_info:\n");
	fmt::printf("- pc:{}\n", pc);
	fmt::printf("- file:{}\n", file);
	fmt::printf("- func_name:{}\n", func_name);
	fmt::printf("- line:{}\n", line);

	pc, file, func_name, line = runtime::call_info(1);
	fmt::printf("\ncall_info:\n");
	fmt::printf("- pc:{}\n", pc);
	fmt::printf("- file:{}\n", file);
	fmt::printf("- func_name:{}\n", func_name);
	fmt::printf("- line:{}\n", line);

	pc, file, func_name, line = runtime::call_info(2);
	fmt::printf("\ncall_info:\n");
	fmt::printf("- pc:{}\n", pc);
	fmt::printf("- file:{}\n", file);
	fmt::printf("- func_name:{}\n", func_name);
	fmt::printf("- line:{}\n", line);

	pc, file, func_name, line = runtime::call_info(3);
	fmt::printf("\ncall_info:\n");
	fmt::printf("- pc:{}\n", pc);
	fmt::printf("- file:{}\n", file);
	fmt::printf("- func_name:{}\n", func_name);
	fmt::printf("- line:{}\n", line);


	pc, file, func_name, line = runtime::call_info(4);
	fmt::printf("\ncall_info:\n");
	fmt::printf("- pc:{}\n", pc);
	fmt::printf("- file:{}\n", file);
	fmt::printf("- func_name:{}\n", func_name);
	fmt::printf("- line:{}\n", line);
}