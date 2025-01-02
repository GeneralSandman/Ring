
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

fn main() {
    var string string_value;

    fmt::println_string("test cast 1 ------------------------");
    fmt::println_int(len(string_value));
    fmt::println_int(capacity(string_value));


    fmt::println_string("\ntest cast 1 ------------------------");
    string_value = "123";

    fmt::println_int(len(string_value));
    fmt::println_int(capacity(string_value));


    fmt::println_string("\ntest cast 2 ------------------------");
    string_value = "123456789_123456789_123456789_123456789_123456789_";

    fmt::println_int(len(string_value));
    fmt::println_int(capacity(string_value));
}
