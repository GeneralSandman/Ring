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
  global_int_array_0 = new int[200];

  var int index = 0;
  for(index = 0; index < 200; index = index + 1) {
	  fmt::println_int(global_int_array_0[index]);
	  debug::debug_assert(global_int_array_0[index] == 0);
  }
}
