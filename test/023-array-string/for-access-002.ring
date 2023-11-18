package main

import {
    fmt;
    debug;
}

global {
  var string[] global_string_array_0;
}

@main
function main() {
  var string string_value;

  global_string_array_0 = new string[200];

  var int index = 0;
  for(string_value in range global_string_array_0) {
	  fmt::println_string(string_value);
	  debug::debug_assert(string_value == "");
  }
}
