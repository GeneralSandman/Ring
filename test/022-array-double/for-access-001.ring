package main

import {
    fmt;
    debug;
}

global {
  var double[] global_double_array_0;
}

@main
fn main() {
  global_double_array_0 = new double[200];

  var int index = 0;
  for(index = 0; index < len(global_double_array_0); index = index + 1) {
	  fmt::println_double(global_double_array_0[index]);
	  debug::assert(global_double_array_0[index] == 0.0);
  }
}
