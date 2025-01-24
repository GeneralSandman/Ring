
package main

import {
	fmt;
	debug;
}



typedef Job = class {
    var bool    Running;
    var int     JobID;
    var double  Score;

    fn PrintInfo() {
        
    }
}

global {
    var int global_int_value_1;
    var int global_int_value_2;
    var int global_int_value_3;
    var int global_int_value_4;
    var int global_int_value_5;
    var int global_int_value_6;
    var int global_int_value_7;
    var int global_int_value_8;
    var int global_int_value_9;
}

fn main() {
    test();
    fmt::println_string("------\n");

    fmt::println_string("entry[main] begin");

    fmt::println_string("\ntest case 1");
    fmt::println_int(global_int_value_1);
    fmt::println_int(global_int_value_2);
    fmt::println_int(global_int_value_3);
    fmt::println_int(global_int_value_4);
    fmt::println_int(global_int_value_5);
    fmt::println_int(global_int_value_6);
    fmt::println_int(global_int_value_7);
    fmt::println_int(global_int_value_8);
    fmt::println_int(global_int_value_9);
    debug::assert(global_int_value_1 == 0);
    debug::assert(global_int_value_2 == 0);
    debug::assert(global_int_value_3 == 0);
    debug::assert(global_int_value_4 == 0);
    debug::assert(global_int_value_5 == 0);
    debug::assert(global_int_value_6 == 0);
    debug::assert(global_int_value_7 == 0);
    debug::assert(global_int_value_8 == 0);
    debug::assert(global_int_value_9 == 0);

    fmt::println_string("\ntest case 2");
    global_int_value_1 = 1;
    global_int_value_2 = 2;
    global_int_value_3 = 3;
    global_int_value_4 = 4;
    global_int_value_5 = 5;
    global_int_value_6 = 6;
    global_int_value_7 = 7;
    global_int_value_8 = 8;
    global_int_value_9 = 9;
    fmt::println_int(global_int_value_1);
    fmt::println_int(global_int_value_2);
    fmt::println_int(global_int_value_3);
    fmt::println_int(global_int_value_4);
    fmt::println_int(global_int_value_5);
    fmt::println_int(global_int_value_6);
    fmt::println_int(global_int_value_7);
    fmt::println_int(global_int_value_8);
    fmt::println_int(global_int_value_9);
    debug::assert(global_int_value_1 == 1);
    debug::assert(global_int_value_2 == 2);
    debug::assert(global_int_value_3 == 3);
    debug::assert(global_int_value_4 == 4);
    debug::assert(global_int_value_5 == 5);
    debug::assert(global_int_value_6 == 6);
    debug::assert(global_int_value_7 == 7);
    debug::assert(global_int_value_8 == 8);
    debug::assert(global_int_value_9 == 9);

    fmt::println_string("entry[main] end");
}


// test pass
fn test() {
    fmt::println_string("function[test] begin");

	var int int_value_1;
	var int int_value_2;
	var int int_value_3;
	var int int_value_4;
	var int int_value_5;
	var int int_value_6;
	var int int_value_7;
	var int int_value_8;
	var int int_value_9;

    fmt::println_string("\ntest case 1");
    fmt::println_int(int_value_1);
    fmt::println_int(int_value_2);
    fmt::println_int(int_value_3);
    fmt::println_int(int_value_4);
    fmt::println_int(int_value_5);
    fmt::println_int(int_value_6);
    fmt::println_int(int_value_7);
    fmt::println_int(int_value_8);
    fmt::println_int(int_value_9);
    debug::assert(int_value_1 == 0);
    debug::assert(int_value_2 == 0);
    debug::assert(int_value_3 == 0);
    debug::assert(int_value_4 == 0);
    debug::assert(int_value_5 == 0);
    debug::assert(int_value_6 == 0);
    debug::assert(int_value_7 == 0);
    debug::assert(int_value_8 == 0);
    debug::assert(int_value_9 == 0);

    fmt::println_string("\ntest case 2");
    int_value_1 = 1;
    int_value_2 = 2;
    int_value_3 = 3;
    int_value_4 = 4;
    int_value_5 = 5;
    int_value_6 = 6;
    int_value_7 = 7;
    int_value_8 = 8;
    int_value_9 = 9;
    fmt::println_int(int_value_1);
    fmt::println_int(int_value_2);
    fmt::println_int(int_value_3);
    fmt::println_int(int_value_4);
    fmt::println_int(int_value_5);
    fmt::println_int(int_value_6);
    fmt::println_int(int_value_7);
    fmt::println_int(int_value_8);
    fmt::println_int(int_value_9);
    debug::assert(int_value_1 == 1);
    debug::assert(int_value_2 == 2);
    debug::assert(int_value_3 == 3);
    debug::assert(int_value_4 == 4);
    debug::assert(int_value_5 == 5);
    debug::assert(int_value_6 == 6);
    debug::assert(int_value_7 == 7);
    debug::assert(int_value_8 == 8);
    debug::assert(int_value_9 == 9);

    fmt::println_string("function[test] end");
}