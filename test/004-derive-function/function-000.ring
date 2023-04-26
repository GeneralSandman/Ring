
package main

import {
	fmt;
	debug;
}



function doit1() {
    fmt::println_string("I'm function doit1, go go go!");
}

function doit2() {
    fmt::println_string("I'm function doit2, go go go!");
}

function doit3() {
    fmt::println_string("I'm function doit3, go go go!");
}


function doit4() {
    fmt::println_string("doit4 begin");

    doit1();
    doit2();
    doit3();

    fmt::println_string("doit4 end");
}

@main
function main() {

    fmt::println_string("invoke doit1");
    doit1();


    fmt::println_string("");


    fmt::println_string("invoke doit2");
    doit2();


    fmt::println_string("");


    fmt::println_string("invoke doit3");
    doit3();

    fmt::println_string("");


    fmt::println_string("invoke doit4");
    doit4();

}
