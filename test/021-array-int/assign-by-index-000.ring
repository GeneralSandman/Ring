package main

import {
    fmt;
    debug;
}

global {
  var int[] global_int_array_0;
}

@main
function main() {
  global_int_array_0 = new int[20];

  fmt::println_string("test cast 1 ------------------------");
  var int index = 0;
  for(index = 0; index < 20; index = index + 1) {
	  fmt::println_int(global_int_array_0[index]);
	  debug::debug_assert(global_int_array_0[index] == 0);
  }


  fmt::println_string("\ntest cast 2 ------------------------");
  global_int_array_0[0]  = 0;
  global_int_array_0[1]  = 1;
  global_int_array_0[2]  = 2;
  global_int_array_0[3]  = 3;
  global_int_array_0[4]  = 4;
  global_int_array_0[5]  = 5;
  global_int_array_0[6]  = 6;
  global_int_array_0[7]  = 7;
  global_int_array_0[8]  = 8;
  global_int_array_0[9]  = 9;
  global_int_array_0[10] = 10;
  global_int_array_0[11] = 11;
  global_int_array_0[12] = 12;
  global_int_array_0[13] = 13;
  global_int_array_0[14] = 14;
  global_int_array_0[15] = 15;
  global_int_array_0[16] = 16;
  global_int_array_0[17] = 17;
  global_int_array_0[18] = 18;
  global_int_array_0[19] = 19;
  for(index = 0; index < 20; index = index + 1) {
	  fmt::println_int(global_int_array_0[index]);
	  debug::debug_assert(global_int_array_0[index] == index);
  }

}
