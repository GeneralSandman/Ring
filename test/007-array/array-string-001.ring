
package main

import {
    fmt;
    debug;
	vm;
}

global {
  var string[] global_string_array_0;
}

fn main() {

  global_string_array_0 = string[]{"0-", "1-", "2-", "3-", "4-", "5-", "6-", "7-", "8-", "9-"};
  fmt::println_string(global_string_array_0[0]);
  fmt::println_string(global_string_array_0[1]);
  fmt::println_string(global_string_array_0[2]);
  fmt::println_string(global_string_array_0[3]);
  fmt::println_string(global_string_array_0[4]);
  fmt::println_string(global_string_array_0[5]);
  fmt::println_string(global_string_array_0[6]);
  fmt::println_string(global_string_array_0[7]);
  fmt::println_string(global_string_array_0[8]);
  fmt::println_string(global_string_array_0[9]);

  debug::assert(global_string_array_0[0] == "0-");
  debug::assert(global_string_array_0[1] == "1-");
  debug::assert(global_string_array_0[2] == "2-");
  debug::assert(global_string_array_0[3] == "3-");
  debug::assert(global_string_array_0[4] == "4-");
  debug::assert(global_string_array_0[5] == "5-");
  debug::assert(global_string_array_0[6] == "6-");
  debug::assert(global_string_array_0[7] == "7-");
  debug::assert(global_string_array_0[8] == "8-");
  debug::assert(global_string_array_0[9] == "9-");

}
