//
// File:    string-003.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-18
//


package main

import {
	fmt;
	debug;
}

@main
function main() {

    var bool bool_value;
    var int int_value;
    var double double_value;
    var string string_value;

    var string string_value_1;
    var string string_value_2;


    string_value_1 = "abcdefg";
    fmt::println_string(string_value_1);


    string_value_2 = "1234456";
    fmt::println_string(string_value_2);


    string_value_1 = "1" .. "2" .. "3";
    string_value_2 = "12" .. "3";
    fmt::println_string(string_value_1);
    fmt::println_string(string_value_2);


    if(string_value_1 == string_value_2) {
        fmt::println_string("string_value_1 == string_value_2");
        debug::debug_assert(true);   
    } else {
        fmt::println_string("string_value_1 != string_value_2");
        debug::debug_assert(false);   
    }



    if("a" == "b") {
        fmt::println_string("a == b");
        debug::debug_assert(false);   
    } else {
        fmt::println_string("a != b");
        debug::debug_assert(true);   
    }

    if("ab" == "ab") {
        fmt::println_string("ab == ab");
        debug::debug_assert(true);   
    } else {
        fmt::println_string("ab != ab");
        debug::debug_assert(false);   
    }



    fmt::println_string(string_value_1);
    fmt::println_string(string_value_2);
    fmt::println_string(string_value_1 .. string_value_2);

    string_value = string_value_1 .. string_value_2;
    fmt::println_string(string_value);

}