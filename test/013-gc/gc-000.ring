
package main

import {
  fmt;
  debug;
  vm;
}

global {
  var int[] global_int_array_0;
}

@main
function main() {
  global_int_array_0 = return_int_array();

  fmt::println_pointer(global_int_array_0);

  fmt::println_int(global_int_array_0[0]);
  fmt::println_int(global_int_array_0[9]);

  use_glocal_variable();
}

function use_glocal_variable() {
  fmt::println_pointer(global_int_array_0);

  fmt::println_int(global_int_array_0[0]);
  fmt::println_int(global_int_array_0[9]);
}

function return_int_array() -> (int[]) {
    var int[] local_int_array_0 = int[]{1,2,3,4,5,6,7,8,9,10};
    return local_int_array_0;
}
