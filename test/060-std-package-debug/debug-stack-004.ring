//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
}


fn main() {
	test0();
}


// ----------------------

fn test0() {
	test_two_bool(false, true);
}

fn test_two_bool(var bool bool_value_0, var bool bool_value_1) {
	test_two_int(1, 2);
}

fn test_two_int(var int int_value_0, var int int_value_1) {
	test_two_double(1.2, 2.3);
}

fn test_two_double(var double double_value_0, var double double_value_1) {
	test_two_string("", "");
}

fn test_two_string(var string string_value_0, var string string_value_1) {
	test_any(false, 1, 1.2, "a");
}

fn test_any(var bool bool_value_0, var int int_value_0, var double double_value_0, var string string_value_0) {
	debug::print_call_stack();
}