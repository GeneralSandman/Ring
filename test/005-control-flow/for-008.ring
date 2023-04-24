
package main

import {
	fmt;
	debug;
}

@main
function main() {
    

var int int_value;


for(int_value = 0;int_value < 20; int_value++) {
    fmt::println_int(int_value);
}

fmt::println_string("finish for====");
fmt::println_int(int_value);
debug::debug_assert(int_value == 20);
fmt::println_string("finish for====");



// ---------------
fmt::println_string("");
fmt::println_string("");


for(int_value = 0;int_value < 20; int_value++) {
    break;
    fmt::println_int(int_value);
}

fmt::println_string("finish for====");
fmt::println_int(int_value);
debug::debug_assert(int_value == 0);
fmt::println_string("finish for====");





// ---------------
fmt::println_string("");
fmt::println_string("");


for(int_value = 21;int_value < 20; int_value++) {
    break;
    fmt::println_int(int_value);
}

fmt::println_string("finish for====");
fmt::println_int(int_value);
debug::debug_assert(int_value == 21);
fmt::println_string("finish for====");

}
