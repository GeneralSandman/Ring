package main

import {
    fmt;
    debug;
}

global {
  var double[] global_double_array_0;
}

fn main() {
  var double double_value;

  global_double_array_0 = new double[200];

  for(double_value = range global_double_array_0) {
	  fmt::println_double(double_value);
	  debug::assert(double_value == 0.0);
  }
}
