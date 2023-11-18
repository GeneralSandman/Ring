package main

import {
    fmt;
    debug;
}

global {
  var int[] global_int_array_0;
}

@main
function main() {
	var int value;

  global_int_array_0 = new int[200];

  for(value in range global_int_array_0) {
	  fmt::println_int(value);
	  debug::debug_assert(value == 0);
  }
}
