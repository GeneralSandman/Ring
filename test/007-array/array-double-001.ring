
package main

import {
    fmt;
    debug;
}

global {
  var double double_value;
  var double[] double_array;
}

fn main() {

  double_array = new double[10];

  double_value = double_array[0];
  fmt::println_double(double_value);

  double_value = double_array[1];
  fmt::println_double(double_value);

  double_value = double_array[2];
  fmt::println_double(double_value);

  double_value = double_array[3];
  fmt::println_double(double_value);

  double_value = double_array[4];
  fmt::println_double(double_value);

  double_value = double_array[5];
  fmt::println_double(double_value);

  double_value = double_array[6];
  fmt::println_double(double_value);

  double_value = double_array[7];
  fmt::println_double(double_value);

  double_value = double_array[8];
  fmt::println_double(double_value);

  double_value = double_array[9];
  fmt::println_double(double_value);



}
