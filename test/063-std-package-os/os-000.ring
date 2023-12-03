
package main

import {
    fmt;
    debug;
    vm;
    os;
}

global {
  var int int_value;
  var int[] int_array;

  var int heap_size;
}

@main
function main() {
    fmt::println_string("before invoke os::exit");
    os::exit(0);
    fmt::println_string("after invoke os::exit");
}
