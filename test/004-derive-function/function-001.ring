
package main

import {
	fmt;
	debug;
}



fn doit1() {
    fmt::println_string("function doit1 BEGIN");
    fmt::println_string("function doit1 END");
}

fn doit2() {
    fmt::println_string("function doit2 BEGIN");

    doit1();

    fmt::println_string("function doit2 END");
}

fn doit3() {
    fmt::println_string("function doit3 BEGIN");

    doit2();

    fmt::println_string("function doit3 END");
}

fn doit4() {
    fmt::println_string("function doit4 BEGIN");

    doit3();
    
    fmt::println_string("function doit4 END");
}

fn doit5() {
    fmt::println_string("function doit5 BEGIN");

    doit4();
    
    fmt::println_string("function doit5 END");
}

fn doit6() {
    fmt::println_string("function doit6 BEGIN");

    doit5();

    fmt::println_string("function doit6 END");
}


fn main() {

    doit6();

}