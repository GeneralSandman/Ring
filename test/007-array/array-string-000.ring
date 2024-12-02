
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

  debug::assert(global_string_array_0[0] == "");
  debug::assert(global_string_array_0[1] == "");
  debug::assert(global_string_array_0[2] == "");
  debug::assert(global_string_array_0[3] == "");
  debug::assert(global_string_array_0[4] == "");
  debug::assert(global_string_array_0[5] == "");
  debug::assert(global_string_array_0[6] == "");
  debug::assert(global_string_array_0[7] == "");
  debug::assert(global_string_array_0[8] == "");
  debug::assert(global_string_array_0[9] == "");

}
