package main

import {
    fmt;
    debug;
}

global {
  var double[] global_double_array_0;
}

fn main() {
	global_double_array_0 = func_return_double_array();
	
	fmt::println_string("\n=================func main\n");
	fmt::println_double(global_double_array_0[0]);
	fmt::println_double(global_double_array_0[1]);
	fmt::println_double(global_double_array_0[2]);
	fmt::println_double(global_double_array_0[3]);
	fmt::println_double(global_double_array_0[4]);
	fmt::println_double(global_double_array_0[5]);
	fmt::println_double(global_double_array_0[6]);
	fmt::println_double(global_double_array_0[7]);
	fmt::println_double(global_double_array_0[8]);
	fmt::println_double(global_double_array_0[9]);
	fmt::println_double(global_double_array_0[10]);
	fmt::println_double(global_double_array_0[11]);
	fmt::println_double(global_double_array_0[12]);
	fmt::println_double(global_double_array_0[13]);
	fmt::println_double(global_double_array_0[14]);

	debug::assert(global_double_array_0[0]  == 0.0);
	debug::assert(global_double_array_0[1]  == 1.0);
	debug::assert(global_double_array_0[2]  == 2.0);
	debug::assert(global_double_array_0[3]  == 3.0);
	debug::assert(global_double_array_0[4]  == 4.0);
	debug::assert(global_double_array_0[5]  == 5.0);
	debug::assert(global_double_array_0[6]  == 6.0);
	debug::assert(global_double_array_0[7]  == 7.0);
	debug::assert(global_double_array_0[8]  == 8.0);
	debug::assert(global_double_array_0[9]  == 9.0);
	debug::assert(global_double_array_0[10] == 10.0);
	debug::assert(global_double_array_0[11] == 11.0);
	debug::assert(global_double_array_0[12] == 12.0);
	debug::assert(global_double_array_0[13] == 13.0);
	debug::assert(global_double_array_0[14] == 14.0);
}

fn func_return_double_array() -> (double[]) {
	var double[] double_array = double[]{0.0, 1.0, 2.0, 
		3.0, 4.0, 5.0, 
		6.0, 7.0, 8.0, 
		9.0, 10.0, 11.0, 
		12.0, 13.0, 14.0};
	
	fmt::println_string("=================func func_return_double_array\n");
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

	return double_array;
}