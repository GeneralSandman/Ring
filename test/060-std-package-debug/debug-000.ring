//
// File:    std-debug-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
}

global {
	var bool   global_bool_value;
	var int    global_int_value;
	var double global_double_value;
	var string global_string_value;
}

@main
function main() {
	var bool   local_bool_value;
	var int    local_int_value;
	var double local_double_value;
	var string local_string_value;

	test();
	
	debug::debug_assert(true);
	debug::debug_assert(true);
	debug::debug_assert(true);
}

function test() {
	debug::debug_assert(true);
	debug::debug_assert(true);
	debug::debug_assert(true);
	debug::debug_assert(true);
	debug::debug_assert(true);
}