package main

import {
    fmt;
    debug;
}

global {
  var string[] global_string_array_0;
}

fn main() {

  fmt::println_string("test cast 1 ------------------------");
  fmt::println_int(len(global_string_array_0));
	fmt::println_int(cap(global_string_array_0));
  debug::assert(len(global_string_array_0) == 0);
  debug::assert(cap(global_string_array_0) == 0);


  fmt::println_string("\ntest cast 2 ------------------------");

	global_string_array_0 = new string[200];

  fmt::println_int(len(global_string_array_0));
	fmt::println_int(cap(global_string_array_0));
  debug::assert(len(global_string_array_0) == 200);
  debug::assert(cap(global_string_array_0) == 200);
}