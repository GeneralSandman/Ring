//
// File:    int-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

@main
function main() {


    if("a" == "a") {
        fmt::println_string("test pass");
    } else {
        fmt::println_string("test failed");

    }

    if("a" != "a") {
        fmt::println_string("test failed");
    } else {
        fmt::println_string("test pass");
    }

    if("a" > "a") {
        fmt::println_string("test failed");
    } else {
        fmt::println_string("test pass");
    }

    if("a" >= "a") {
        fmt::println_string("test pass");
    } else {
        fmt::println_string("test failed");
    }

    if("a" < "a") {
        fmt::println_string("test failed");
    } else {
        fmt::println_string("test pass");
    }

    if("a" <= "a") {
        fmt::println_string("test pass");
    } else {
        fmt::println_string("test failed");
    }



    fmt::println_string("----------------");

    if("a" == "b") {
        fmt::println_string("test failed");
    } else {
        fmt::println_string("test pass");
    }

    if("a" != "b") {
        fmt::println_string("test pass");
    } else {
        fmt::println_string("test failed");
    }

    if("a" > "b") {
        fmt::println_string("test failed");
    } else {
        fmt::println_string("test pass");
    }

    if("a" >= "b") {
        fmt::println_string("test failed");
    } else {
        fmt::println_string("test pass");
    }

    if("a" < "b") {
        fmt::println_string("test pass");
    } else {
        fmt::println_string("test failed");
    }

    if("a" <= "b") {
        fmt::println_string("test pass");
    } else {
        fmt::println_string("test failed");
    }



}

