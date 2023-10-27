
package main

import {
  fmt;
  debug;
  vm;
}

global {
}

@main
function main() {
    int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vm::garbage_collect();

    test();

    vm::garbage_collect();
}

function test() {
    var int[] local_int_array_0 = int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    local_int_array_0 = int[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vm::garbage_collect();
}
