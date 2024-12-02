package main

import {
    fmt;
    debug;
}

global {
  var double[] global_double_array_0;
}

@main
function main() {
	global_double_array_0 = double[]{0.0, 1.0, 2.0, 
		3.0, 4.0, 5.0, 
		6.0, 7.0, 8.0, 
		9.0, 10.0, 11.0, 
		12.0, 13.0, 14.0};
	

	func_accept_double_array(global_double_array_0);
	
}

function func_accept_double_array(var double[] double_array) {
	fmt::println_double(double_array[0]);
	fmt::println_double(double_array[1]);
	fmt::println_double(double_array[2]);
	fmt::println_double(double_array[3]);
	fmt::println_double(double_array[4]);
	fmt::println_double(double_array[5]);
	fmt::println_double(double_array[6]);
	fmt::println_double(double_array[7]);
	fmt::println_double(double_array[8]);
	fmt::println_double(double_array[9]);
	fmt::println_double(double_array[10]);
	fmt::println_double(double_array[11]);
	fmt::println_double(double_array[12]);
	fmt::println_double(double_array[13]);
	fmt::println_double(double_array[14]);

	debug::assert(double_array[0]  == 0.0);
	debug::assert(double_array[1]  == 1.0);
	debug::assert(double_array[2]  == 2.0);
	debug::assert(double_array[3]  == 3.0);
	debug::assert(double_array[4]  == 4.0);
	debug::assert(double_array[5]  == 5.0);
	debug::assert(double_array[6]  == 6.0);
	debug::assert(double_array[7]  == 7.0);
	debug::assert(double_array[8]  == 8.0);
	debug::assert(double_array[9]  == 9.0);
	debug::assert(double_array[10] == 10.0);
	debug::assert(double_array[11] == 11.0);
	debug::assert(double_array[12] == 12.0);
	debug::assert(double_array[13] == 13.0);
	debug::assert(double_array[14] == 14.0);
}