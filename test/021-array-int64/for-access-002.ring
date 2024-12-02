package main

import {
    fmt;
    debug;
}

global {
  var int64[] global_int64_array_0;
}

@main
function main() {
	var int64 value;

  global_int64_array_0 = new int64[200];

  for(value in range global_int64_array_0) {
	  fmt::println_int64(value);
	  debug::assert(value == 0L);
  }
}
