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
	global_bool_array_0 = bool[]{true, false, false, 
		true, false, false, 
		true, false, false, 
		true, false, false, 
		true, false, false};
	

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

	debug::assert(global_bool_array_0[0] == true);
	debug::assert(global_bool_array_0[1] == false);
	debug::assert(global_bool_array_0[2] == false);
	debug::assert(global_bool_array_0[3] == true);
	debug::assert(global_bool_array_0[4] == false);
	debug::assert(global_bool_array_0[5] == false);
	debug::assert(global_bool_array_0[6] == true);
	debug::assert(global_bool_array_0[7] == false);
	debug::assert(global_bool_array_0[8] == false);
	debug::assert(global_bool_array_0[9] == true);
	debug::assert(global_bool_array_0[10] == false);
	debug::assert(global_bool_array_0[11] == false);
	debug::assert(global_bool_array_0[12] == true);
	debug::assert(global_bool_array_0[13] == false);
	debug::assert(global_bool_array_0[14] == false);
}