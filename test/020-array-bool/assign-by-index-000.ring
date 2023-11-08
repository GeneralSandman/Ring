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
  global_bool_array_0 = new bool[20];

  fmt::println_string("test cast 1 ------------------------");
  var int index = 0;
  for(index = 0; index < 20; index = index + 1) {
	  fmt::println_bool(global_bool_array_0[index]);
	  debug::debug_assert(global_bool_array_0[index] == false);
  }


  fmt::println_string("\ntest cast 2 ------------------------");
  global_bool_array_0[0] = true;
  global_bool_array_0[1] = true;
  global_bool_array_0[2] = true;
  global_bool_array_0[3] = true;
  global_bool_array_0[4] = true;
  global_bool_array_0[5] = true;
  global_bool_array_0[6] = true;
  global_bool_array_0[7] = true;
  global_bool_array_0[8] = true;
  global_bool_array_0[9] = true;
  global_bool_array_0[10] = true;
  global_bool_array_0[11] = true;
  global_bool_array_0[12] = true;
  global_bool_array_0[13] = true;
  global_bool_array_0[14] = true;
  global_bool_array_0[15] = true;
  global_bool_array_0[16] = true;
  global_bool_array_0[17] = true;
  global_bool_array_0[18] = true;
  global_bool_array_0[19] = true;
  for(index = 0; index < 20; index = index + 1) {
	  fmt::println_bool(global_bool_array_0[index]);
	  debug::debug_assert(global_bool_array_0[index] == true);
  }

}
