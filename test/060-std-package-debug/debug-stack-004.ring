//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
}

@main
function main() {
	test0();
}


// ----------------------

function test0() {
	test_two_bool(false, true);
}

function test_two_bool(var bool bool_value_0, var bool bool_value_1) {
	test_two_int(1, 2);
}

function test_two_int(var int int_value_0, var int int_value_1) {
	test_two_double(1.2, 2.3);
}

function test_two_double(var double double_value_0, var double double_value_1) {
	test_two_string("", "");
}

function test_two_string(var string string_value_0, var string string_value_1) {
	test_any(false, 1, 1.2, "a");
}

function test_any(var bool bool_value_0, var int int_value_0, var double double_value_0, var string string_value_0) {
	debug::print_call_stack();
}