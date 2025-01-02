package main

import {
    fmt;
    debug;
}

global {
  var bool[] global_bool_array_0;
}

fn main() {
  global_bool_array_0 = new bool[200];

  var int index = 0;
  for(index = 0; index < 200; index = index + 1) {
	  fmt::println_bool(global_bool_array_0[index]);
	  debug::assert(global_bool_array_0[index] == false);
  }
}
