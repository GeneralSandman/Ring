
package main

import {
	fmt;
	debug;
}



function doit1() {
    fmt::println_string("function doit1 BEGIN");
    fmt::println_string("function doit1 END");
}

function doit2() {
    fmt::println_string("function doit2 BEGIN");

    doit1();

    fmt::println_string("function doit2 END");
}

function doit3() {
    fmt::println_string("function doit3 BEGIN");

    doit2();

    fmt::println_string("function doit3 END");
}

function doit4() {
    fmt::println_string("function doit4 BEGIN");

    doit3();
    
    fmt::println_string("function doit4 END");
}

function doit5() {
    fmt::println_string("function doit5 BEGIN");

    doit4();
    
    fmt::println_string("function doit5 END");
}

function doit6() {
    fmt::println_string("function doit6 BEGIN");

    doit5();

    fmt::println_string("function doit6 END");
}

@main
function main() {

doit6();

}