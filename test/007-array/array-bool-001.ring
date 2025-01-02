
package main

import {
    fmt;
    debug;
}

global {
  var bool[] bool_array;
}

fn main() {

  bool_array = bool[]{true, false, true, false, true, false, true, false, true, false};


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


  debug::assert(bool_array[0] == true);
  debug::assert(bool_array[1] == false);
  debug::assert(bool_array[2] == true);
  debug::assert(bool_array[3] == false);
  debug::assert(bool_array[4] == true);
  debug::assert(bool_array[5] == false);
  debug::assert(bool_array[6] == true);
  debug::assert(bool_array[7] == false);
  debug::assert(bool_array[8] == true);
  debug::assert(bool_array[9] == false);


}
