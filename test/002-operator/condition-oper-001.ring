
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
    var bool result;

    fmt::println_string("\ntest case 1-----------");
    true ? test_a() : test_b();
    false ? test_a() : test_b();



    fmt::println_string("\ntest case 2-----------");
    return_true() ? test_a() : test_b();
    return_false() ? test_a() : test_b();



    fmt::println_string("\ntest case 3-----------");

    result = return_true() ? return_true() : return_false();
    fmt::println_bool(result);
    debug::debug_assert(result == true);

    fmt::println_string("\ntest case 4-----------");

    result = return_false() ? return_true() : return_false();
    fmt::println_bool(result);
    debug::debug_assert(result == false);





    fmt::println_string("\ntest case 5-----------");


    fmt::println(true ? 1 : 2);
    fmt::println(false ? 1 : 2);

}