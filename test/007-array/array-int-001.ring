
package main

import {
    fmt;
    debug;
}

global {
  var int int_value;
  var int[] int_array;
}

fn main() {

  int_array = new int[10];

  int_value = int_array[0];
  fmt::println_int(int_value);

  int_value = int_array[1];
  fmt::println_int(int_value);

  int_value = int_array[2];
  fmt::println_int(int_value);

  int_value = int_array[3];
  fmt::println_int(int_value);

  int_value = int_array[4];
  fmt::println_int(int_value);

  int_value = int_array[5];
  fmt::println_int(int_value);

  int_value = int_array[6];
  fmt::println_int(int_value);

  int_value = int_array[7];
  fmt::println_int(int_value);

  int_value = int_array[8];
  fmt::println_int(int_value);

  int_value = int_array[9];
  fmt::println_int(int_value);



}
