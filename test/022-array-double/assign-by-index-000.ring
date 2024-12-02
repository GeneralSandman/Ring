package main

import {
    fmt;
    debug;
}

global {
  var double[] global_double_array_0;
}

@main
function main() {
  global_double_array_0 = new double[20];

  fmt::println_string("test cast 1 ------------------------");
  var int index = 0;
  for(index = 0; index < 20; index = index + 1) {
	  fmt::println_double(global_double_array_0[index]);
	  debug::assert(global_double_array_0[index] == 0.0);
  }


  fmt::println_string("\ntest cast 2 ------------------------");
  global_double_array_0[0]  = 3.1415;
  global_double_array_0[1]  = 3.1415;
  global_double_array_0[2]  = 3.1415;
  global_double_array_0[3]  = 3.1415;
  global_double_array_0[4]  = 3.1415;
  global_double_array_0[5]  = 3.1415;
  global_double_array_0[6]  = 3.1415;
  global_double_array_0[7]  = 3.1415;
  global_double_array_0[8]  = 3.1415;
  global_double_array_0[9]  = 3.1415;
  global_double_array_0[10] = 3.1415;
  global_double_array_0[11] = 3.1415;
  global_double_array_0[12] = 3.1415;
  global_double_array_0[13] = 3.1415;
  global_double_array_0[14] = 3.1415;
  global_double_array_0[15] = 3.1415;
  global_double_array_0[16] = 3.1415;
  global_double_array_0[17] = 3.1415;
  global_double_array_0[18] = 3.1415;
  global_double_array_0[19] = 3.1415;
  for(index = 0; index < 20; index = index + 1) {
	  fmt::println_double(global_double_array_0[index]);
	  debug::assert(global_double_array_0[index] == 3.1415);
  }

}
