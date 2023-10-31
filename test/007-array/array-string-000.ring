
package main

import {
    fmt;
    debug;
	vm;
}

global {
  var string[] global_string_array_0;
}

@main
function main() {
	global_string_array_0 = new string[10];


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

  debug::debug_assert(global_string_array_0[0] == "");
  debug::debug_assert(global_string_array_0[1] == "");
  debug::debug_assert(global_string_array_0[2] == "");
  debug::debug_assert(global_string_array_0[3] == "");
  debug::debug_assert(global_string_array_0[4] == "");
  debug::debug_assert(global_string_array_0[5] == "");
  debug::debug_assert(global_string_array_0[6] == "");
  debug::debug_assert(global_string_array_0[7] == "");
  debug::debug_assert(global_string_array_0[8] == "");
  debug::debug_assert(global_string_array_0[9] == "");

}
