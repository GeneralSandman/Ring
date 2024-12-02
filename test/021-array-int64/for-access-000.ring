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
  global_int64_array_0 = new int64[200];

  var int index = 0;
  for(index = 0; index < 200; index = index + 1) {
	  fmt::println_int64(global_int64_array_0[index]);
	  debug::assert(global_int64_array_0[index] == 0L);
  }
}
