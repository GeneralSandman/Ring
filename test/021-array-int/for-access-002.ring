package main

import {
    fmt;
    debug;
}

global {
  var int[] global_int_array_0;
}

fn main() {
	var int value;

  global_int_array_0 = new int[200];

  for(value = range global_int_array_0) {
	  fmt::println_int(value);
	  debug::assert(value == 0);
  }
}
