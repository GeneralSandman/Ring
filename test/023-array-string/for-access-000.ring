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
  global_string_array_0 = new string[200];

  var int index = 0;
  for(index = 0; index < 200; index = index + 1) {
	  fmt::println_string(global_string_array_0[index]);
	  debug::assert(global_string_array_0[index] == "");
  }
}
