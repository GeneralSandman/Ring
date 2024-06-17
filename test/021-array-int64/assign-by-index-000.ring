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
  global_int64_array_0 = new int64[20];

  fmt::println_string("test cast 1 ------------------------");
  var int index = 0;
  for(index = 0; index < 20; index = index + 1) {
	  fmt::println_int64(global_int64_array_0[index]);
	  debug::debug_assert(global_int64_array_0[index] == 0L);
  }


  fmt::println_string("\ntest cast 2 ------------------------");
  global_int64_array_0[0]  =  0L;
  global_int64_array_0[1]  =  1L;
  global_int64_array_0[2]  =  2L;
  global_int64_array_0[3]  =  3L;
  global_int64_array_0[4]  =  4L;
  global_int64_array_0[5]  =  5L;
  global_int64_array_0[6]  =  6L;
  global_int64_array_0[7]  =  7L;
  global_int64_array_0[8]  =  8L;
  global_int64_array_0[9]  =  9L;
  global_int64_array_0[10] = 10L;
  global_int64_array_0[11] = 11L;
  global_int64_array_0[12] = 12L;
  global_int64_array_0[13] = 13L;
  global_int64_array_0[14] = 14L;
  global_int64_array_0[15] = 15L;
  global_int64_array_0[16] = 16L;
  global_int64_array_0[17] = 17L;
  global_int64_array_0[18] = 18L;
  global_int64_array_0[19] = 19L;
  for(index = 0; index < 20; index = index + 1) {
	    fmt::println_int64(global_int64_array_0[index]);
	    debug::debug_assert(global_int64_array_0[index] == to_int64(index));
  }

}
