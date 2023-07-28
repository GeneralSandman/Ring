
package main

import {
    fmt;
    debug;
}

global {
  var double double_value;
  var double[] double_array;
}

@main
function main() {

  double_array = new double[10];


  fmt::println_double(double_array[0]);
  fmt::println_double(double_array[1]);
  fmt::println_double(double_array[2]);
  fmt::println_double(double_array[3]);
  fmt::println_double(double_array[4]);
  fmt::println_double(double_array[5]);
  fmt::println_double(double_array[6]);
  fmt::println_double(double_array[7]);
  fmt::println_double(double_array[8]);
  fmt::println_double(double_array[9]);


}
