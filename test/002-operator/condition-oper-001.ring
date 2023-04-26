
package main

import {
	fmt;
	debug;
}



function test_a(){
    fmt::println_string("invoke function test_a");
}

function test_b(){
    fmt::println_string("invoke function test_b");
}



function return_false() -> (bool) {
    fmt::println_string("invoke function return_false");
    return false;
}

function return_true() -> (bool) {
    fmt::println_string("invoke function return_true");
    return true;
}


@main
function main() {

    fmt::println_string("\ntest case 1");
    false ? test_a() : test_b();
    true ? test_a() : test_b();



    fmt::println_string("\ntest case 2");
    return_false() ? test_a() : test_b();
    return_true() ? test_a() : test_b();




    fmt::println_string("\ntest case 3");
    var bool result;

    result = return_false() ? return_true() : return_false();
    fmt::println_bool(result);
    debug::debug_assert(result == false);

    result = return_true() ? return_true() : return_false();
    fmt::println_bool(result);
    debug::debug_assert(result == true);


    fmt::println_string("\ntest case 4");


    debug::debug_assert(false ? 1 : 2);
    debug::debug_assert(true ? 1 : 2);

}