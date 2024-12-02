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

  fmt::println_string("[function main]");
  debug::assert(global_int_array_0[0]  == 0);
  debug::assert(global_int_array_0[1]  == 1);
  debug::assert(global_int_array_0[2]  == 2);
  debug::assert(global_int_array_0[3]  == 3);
  debug::assert(global_int_array_0[4]  == 4);
  debug::assert(global_int_array_0[5]  == 5);
  debug::assert(global_int_array_0[6]  == 6);
  debug::assert(global_int_array_0[7]  == 7);
  debug::assert(global_int_array_0[8]  == 8);
  debug::assert(global_int_array_0[9]  == 9);
  fmt::println_string("[function main]\n");


  use_glocal_variable();


  pass_int_array_to_fun(global_int_array_0);
}

function use_glocal_variable() {
  fmt::println_string("[function use_glocal_variable]");
  debug::assert(global_int_array_0[0]  == 0);
  debug::assert(global_int_array_0[1]  == 1);
  debug::assert(global_int_array_0[2]  == 2);
  debug::assert(global_int_array_0[3]  == 3);
  debug::assert(global_int_array_0[4]  == 4);
  debug::assert(global_int_array_0[5]  == 5);
  debug::assert(global_int_array_0[6]  == 6);
  debug::assert(global_int_array_0[7]  == 7);
  debug::assert(global_int_array_0[8]  == 8);
  debug::assert(global_int_array_0[9]  == 9);
  fmt::println_string("[function use_glocal_variable]\n");
}

function return_int_array() -> (int[]) {
    var int[] local_int_array_0 = int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    fmt::println_string("[function return_int_array]");
    debug::assert(local_int_array_0[0]  == 0);
    debug::assert(local_int_array_0[1]  == 1);
    debug::assert(local_int_array_0[2]  == 2);
    debug::assert(local_int_array_0[3]  == 3);
    debug::assert(local_int_array_0[4]  == 4);
    debug::assert(local_int_array_0[5]  == 5);
    debug::assert(local_int_array_0[6]  == 6);
    debug::assert(local_int_array_0[7]  == 7);
    debug::assert(local_int_array_0[8]  == 8);
    debug::assert(local_int_array_0[9]  == 9);
    fmt::println_string("[function return_int_array]\n");

    return local_int_array_0;
}

function pass_int_array_to_fun(var int[] array) {
  fmt::println_string("[function pass_int_array_to_fun]");
  debug::assert(array[0]  == 0);
  debug::assert(array[1]  == 1);
  debug::assert(array[2]  == 2);
  debug::assert(array[3]  == 3);
  debug::assert(array[4]  == 4);
  debug::assert(array[5]  == 5);
  debug::assert(array[6]  == 6);
  debug::assert(array[7]  == 7);
  debug::assert(array[8]  == 8);
  debug::assert(array[9]  == 9);
  fmt::println_string("[function pass_int_array_to_fun]\n");
}
