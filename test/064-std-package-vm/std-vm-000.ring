
package main

import {
    fmt;
    debug;
    vm;
}

global {
  var int int_value;
  var int[] int_array;

  var int heap_size;
}

@main
function main() {
  
  // before new
  heap_size = vm::heap_size();
  fmt::println_int(heap_size);
  debug::debug_assert(heap_size == 0);

  int_array = new int[10];

  // after new
  heap_size = vm::heap_size();
  fmt::println_int(heap_size);
  debug::debug_assert(heap_size == 128);

  int_array = new int[10];

  // after new
  heap_size = vm::heap_size();
  fmt::println_int(heap_size);
  debug::debug_assert(heap_size == 256);


  // after gc
  vm::garbage_collect();
  heap_size = vm::heap_size();
  fmt::println_int(heap_size);
  debug::debug_assert(heap_size == 64);
}
