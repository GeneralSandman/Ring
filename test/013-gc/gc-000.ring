
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
fn main() {
  global_int_array_0 = return_int_array();

  fmt::println_pointer(global_int_array_0);

  fmt::println_int(global_int_array_0[0]);
  fmt::println_int(global_int_array_0[9]);

  use_glocal_variable();
  pass_int_array_to_fun(global_int_array_0);
}

fn use_glocal_variable() {
  fmt::println_pointer(global_int_array_0);

  fmt::println_int(global_int_array_0[0]);
  fmt::println_int(global_int_array_0[9]);
}

fn return_int_array() -> (int[]) {
    var int[] local_int_array_0 = int[]{1,2,3,4,5,6,7,8,9,10};
    return local_int_array_0;
}

fn pass_int_array_to_fun(var int[] array) {
  fmt::println_pointer(array);

}
