package main

import {
    fmt;
    debug;
}

global {
  var int64[] global_int64_array_0;
}

fn main() {

  fmt::println_string("test cast 1 ------------------------");
  fmt::println_int(len(global_int64_array_0));
	fmt::println_int(cap(global_int64_array_0));
  debug::assert(len(global_int64_array_0) == 0);
  debug::assert(cap(global_int64_array_0) == 0);


  fmt::println_string("\ntest cast 2 ------------------------");

	global_int64_array_0 = new int64[200];

  fmt::println_int(len(global_int64_array_0));
	fmt::println_int(cap(global_int64_array_0));
  debug::assert(len(global_int64_array_0) == 200);
  debug::assert(cap(global_int64_array_0) == 200);
}