
package main

import {
  fmt;
  debug;
  vm;
}

global {
  var string global_string_value_0;
}

@main
function main() {
    fmt::println_string(global_string_value_0);
    fmt::println_int(vm::heap_size());

    // init
    global_string_value_0 = "1234567890";
    fmt::println_string(global_string_value_0);
    fmt::println_int(vm::heap_size());

    // gc
    vm::garbage_collect();
    fmt::println_string(global_string_value_0);
    fmt::println_int(vm::heap_size());


}
