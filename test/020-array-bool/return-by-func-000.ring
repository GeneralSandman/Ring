package main

import {
    fmt;
    debug;
}

global {
  var bool[] global_bool_array_0;
}

@main
function main() {
	global_bool_array_0 = func_return_bool_array();
	
	fmt::println_string("\n=================func main\n");
	fmt::println_bool(global_bool_array_0[0]);
	fmt::println_bool(global_bool_array_0[1]);
	fmt::println_bool(global_bool_array_0[2]);
	fmt::println_bool(global_bool_array_0[3]);
	fmt::println_bool(global_bool_array_0[4]);
	fmt::println_bool(global_bool_array_0[5]);
	fmt::println_bool(global_bool_array_0[6]);
	fmt::println_bool(global_bool_array_0[7]);
	fmt::println_bool(global_bool_array_0[8]);
	fmt::println_bool(global_bool_array_0[9]);
	fmt::println_bool(global_bool_array_0[10]);
	fmt::println_bool(global_bool_array_0[11]);
	fmt::println_bool(global_bool_array_0[12]);
	fmt::println_bool(global_bool_array_0[13]);
	fmt::println_bool(global_bool_array_0[14]);

	debug::debug_assert(global_bool_array_0[0] == true);
	debug::debug_assert(global_bool_array_0[1] == false);
	debug::debug_assert(global_bool_array_0[2] == false);
	debug::debug_assert(global_bool_array_0[3] == true);
	debug::debug_assert(global_bool_array_0[4] == false);
	debug::debug_assert(global_bool_array_0[5] == false);
	debug::debug_assert(global_bool_array_0[6] == true);
	debug::debug_assert(global_bool_array_0[7] == false);
	debug::debug_assert(global_bool_array_0[8] == false);
	debug::debug_assert(global_bool_array_0[9] == true);
	debug::debug_assert(global_bool_array_0[10] == false);
	debug::debug_assert(global_bool_array_0[11] == false);
	debug::debug_assert(global_bool_array_0[12] == true);
	debug::debug_assert(global_bool_array_0[13] == false);
	debug::debug_assert(global_bool_array_0[14] == false);
}

function func_return_bool_array() -> (bool[]) {
	var bool[] bool_array = bool[]{true, false, false, 
		true, false, false, 
		true, false, false, 
		true, false, false, 
		true, false, false};
	
	fmt::println_string("=================func func_return_bool_array\n");
	fmt::println_bool(bool_array[0]);
	fmt::println_bool(bool_array[1]);
	fmt::println_bool(bool_array[2]);
	fmt::println_bool(bool_array[3]);
	fmt::println_bool(bool_array[4]);
	fmt::println_bool(bool_array[5]);
	fmt::println_bool(bool_array[6]);
	fmt::println_bool(bool_array[7]);
	fmt::println_bool(bool_array[8]);
	fmt::println_bool(bool_array[9]);
	fmt::println_bool(bool_array[10]);
	fmt::println_bool(bool_array[11]);
	fmt::println_bool(bool_array[12]);
	fmt::println_bool(bool_array[13]);
	fmt::println_bool(bool_array[14]);

	debug::debug_assert(bool_array[0] == true);
	debug::debug_assert(bool_array[1] == false);
	debug::debug_assert(bool_array[2] == false);
	debug::debug_assert(bool_array[3] == true);
	debug::debug_assert(bool_array[4] == false);
	debug::debug_assert(bool_array[5] == false);
	debug::debug_assert(bool_array[6] == true);
	debug::debug_assert(bool_array[7] == false);
	debug::debug_assert(bool_array[8] == false);
	debug::debug_assert(bool_array[9] == true);
	debug::debug_assert(bool_array[10] == false);
	debug::debug_assert(bool_array[11] == false);
	debug::debug_assert(bool_array[12] == true);
	debug::debug_assert(bool_array[13] == false);
	debug::debug_assert(bool_array[14] == false);

	return bool_array;
}