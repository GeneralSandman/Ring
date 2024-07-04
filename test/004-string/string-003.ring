
//
// File:    string-003.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-10-20
//

package main

import {
	fmt;
	debug;
  vm;
}

@main
function main() {
    var string string_value;
    string_value = "123";

    fmt::println_int(vm::heap_size());
}
