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

  fmt::println_string("test cast 1 ------------------------");
  fmt::println_int(len(global_double_array_0));
	fmt::println_int(capacity(global_double_array_0));
  debug::debug_assert(len(global_double_array_0) == 0);
  debug::debug_assert(capacity(global_double_array_0) == 0);


  fmt::println_string("\ntest cast 2 ------------------------");

	global_double_array_0 = new double[200];

  fmt::println_int(len(global_double_array_0));
	fmt::println_int(capacity(global_double_array_0));
  debug::debug_assert(len(global_double_array_0) == 200);
  debug::debug_assert(capacity(global_double_array_0) == 200);
}