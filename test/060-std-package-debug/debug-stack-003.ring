//
// File:    debug-stack-003.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-12-13
//

package main

import {
	fmt;
	debug;
}


fn main() {
	fmt::println("fn main()");
	test0();
}

fn test0() {
	fmt::println("fn test0()");
	test1(false);
}

fn test1(var bool bool_value) {
	fmt::println("fn test1()");
	test2(1);
}

fn test2(var int int_value) {
	fmt::println("fn test2()");
	test3(1.2);
}

fn test3(var double double_value) {
	fmt::println("fn test3()");
	test4("a");
}

fn test4(var string string_value) {
	fmt::println("fn test4()");
	debug::print_call_stack();
}
