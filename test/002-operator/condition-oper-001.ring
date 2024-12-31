
package main

import {
	fmt;
	debug;
}



fn test_a(){
    fmt::println_string("invoke function test_a");
}

fn test_b(){
    fmt::println_string("invoke function test_b");
}



fn return_false() -> (bool) {
    fmt::println_string("invoke function return_false");
    return false;
}

fn return_true() -> (bool) {
    fmt::println_string("invoke function return_true");
    return true;
}


@main
fn main() {
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
    debug::assert(result == true);

    fmt::println_string("\ntest case 4-----------");

    result = return_false() ? return_true() : return_false();
    fmt::println_bool(result);
    debug::assert(result == false);





    fmt::println_string("\ntest case 5-----------");


    fmt::println(true ? 1 : 2);
    fmt::println(false ? 1 : 2);

}