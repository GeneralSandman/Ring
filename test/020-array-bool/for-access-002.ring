package main

import {
    fmt;
    debug;
}

global {
  var bool[] global_bool_array_0;
}

@main
function main() {
  var bool bool_value;

  global_bool_array_0 = new bool[200];

  var int index = 0;
  for(bool_value in range global_bool_array_0) {
	  fmt::println_bool(bool_value);
	  debug::assert(bool_value == false);
  }
}
