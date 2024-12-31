
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
    
    debug::assert(global_int_array_0[9]  == 9);

    vm::garbage_collect();

    debug::assert(global_int_array_0[9]  == 9);

}

fn return_int_array() -> (int[]) {
    var int[] local_int_array_0 = int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    debug::assert(local_int_array_0[9]  == 9);

    return local_int_array_0;
}
