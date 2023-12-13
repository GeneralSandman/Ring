//
// File:    debug-stack-003.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-12-13
//

package main

import {
	debug;
}

@main
function main() {
	test0();
}

function test0() {
	test1(false);
}

function test1(var bool bool_value) {
	test2(1);
}

function test2(var int int_value) {
	test3(1.2);
}

function test3(var double double_value) {
	test4("a");
}

function test4(var string string_value) {
	debug::print_call_stack();
}
