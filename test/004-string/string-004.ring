
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

// TestDetail: 测试转义字符

@main
function main() {
    var string string_value;

    fmt::println_string("1234567890");


    fmt::println_string("\ntest case 1-----------------------------");
    string_value = "1234567890";
    fmt::println_string(string_value);
    fmt::println_int(len(string_value));
    debug::assert(len(string_value) == 10);

    fmt::println_string("\ntest case 2-----------------------------");
    string_value = "12\t34567890";
    fmt::println_string(string_value);
    fmt::println_int(len(string_value));
    debug::assert(len(string_value) == 11);


    fmt::println_string("\ntest case 3-----------------------------");
    string_value = "12\n34567890";
    fmt::println_string(string_value);
    fmt::println_int(len(string_value));
    debug::assert(len(string_value) == 11);


    fmt::println_string("\ntest case 4-----------------------------");
    string_value = "12\r34567890";
    fmt::println_string(string_value);
    fmt::println_int(len(string_value));
    debug::assert(len(string_value) == 11);


    fmt::println_string("\ntest case 5-----------------------------");
    string_value = "12\s34567890";
    fmt::println_string(string_value);
    fmt::println_int(len(string_value));
    debug::assert(len(string_value) == 12);


    fmt::println_string("\ntest case 5-----------------------------");
    // 这行应该报错
    string_value = "123456\"7890";
    fmt::println_string(string_value);
    fmt::println_int(len(string_value));
    debug::assert(len(string_value) == 11);
}
