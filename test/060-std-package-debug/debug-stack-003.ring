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

@main
function main() {
	fmt::println("function main()");
	test0();
}

function test0() {
	fmt::println("function test0()");
	test1(false);
}

function test1(var bool bool_value) {
	fmt::println("function test1()");
	test2(1);
}

function test2(var int int_value) {
	fmt::println("function test2()");
	test3(1.2);
}

function test3(var double double_value) {
	fmt::println("function test3()");
	test4("a");
}

function test4(var string string_value) {
	fmt::println("function test4()");
	debug::print_call_stack();
}
