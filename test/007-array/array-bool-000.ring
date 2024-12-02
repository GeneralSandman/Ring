
package main

import {
    fmt;
    debug;
}

global {
  var bool[] bool_array;
}

@main
function main() {

  bool_array = new bool[10];


  fmt::println_bool(bool_array[0]);
  fmt::println_bool(bool_array[1]);
  fmt::println_bool(bool_array[2]);
  fmt::println_bool(bool_array[3]);
  fmt::println_bool(bool_array[4]);
  fmt::println_bool(bool_array[5]);
  fmt::println_bool(bool_array[6]);
  fmt::println_bool(bool_array[7]);
  fmt::println_bool(bool_array[8]);
  fmt::println_bool(bool_array[9]);


  debug::assert(bool_array[0] == false);
  debug::assert(bool_array[1] == false);
  debug::assert(bool_array[2] == false);
  debug::assert(bool_array[3] == false);
  debug::assert(bool_array[4] == false);
  debug::assert(bool_array[5] == false);
  debug::assert(bool_array[6] == false);
  debug::assert(bool_array[7] == false);
  debug::assert(bool_array[8] == false);
  debug::assert(bool_array[9] == false);


}
