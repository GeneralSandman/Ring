//
// File:    class-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-11
//

package main

import {

}

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);
function print(var any value) -> (int);
function println(var any value) -> (int);
function printf(var string format, var any value)   -> (int);
function printfln(var string format, var any value) -> (int);

// -----------------------------


typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;

    @constructor
    method Job(var bool _Running, var int _JobID, var double _Score);

    method PrintInfo();
};

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

@main
function main() {
    test();
    println_string("------\n");

    println_string("entry[main] begin");

    println_string("\ntest case 1");
    println_int(global_int_value_1);
    println_int(global_int_value_2);
    println_int(global_int_value_3);
    println_int(global_int_value_4);
    println_int(global_int_value_5);
    println_int(global_int_value_6);
    println_int(global_int_value_7);
    println_int(global_int_value_8);
    println_int(global_int_value_9);
    debug_assert(global_int_value_1 == 0);
    debug_assert(global_int_value_2 == 0);
    debug_assert(global_int_value_3 == 0);
    debug_assert(global_int_value_4 == 0);
    debug_assert(global_int_value_5 == 0);
    debug_assert(global_int_value_6 == 0);
    debug_assert(global_int_value_7 == 0);
    debug_assert(global_int_value_8 == 0);
    debug_assert(global_int_value_9 == 0);

    println_string("\ntest case 2");
    global_int_value_1 = 1;
    global_int_value_2 = 2;
    global_int_value_3 = 3;
    global_int_value_4 = 4;
    global_int_value_5 = 5;
    global_int_value_6 = 6;
    global_int_value_7 = 7;
    global_int_value_8 = 8;
    global_int_value_9 = 9;
    println_int(global_int_value_1);
    println_int(global_int_value_2);
    println_int(global_int_value_3);
    println_int(global_int_value_4);
    println_int(global_int_value_5);
    println_int(global_int_value_6);
    println_int(global_int_value_7);
    println_int(global_int_value_8);
    println_int(global_int_value_9);
    debug_assert(global_int_value_1 == 1);
    debug_assert(global_int_value_2 == 2);
    debug_assert(global_int_value_3 == 3);
    debug_assert(global_int_value_4 == 4);
    debug_assert(global_int_value_5 == 5);
    debug_assert(global_int_value_6 == 6);
    debug_assert(global_int_value_7 == 7);
    debug_assert(global_int_value_8 == 8);
    debug_assert(global_int_value_9 == 9);

    println_string("entry[main] end");
}


// test pass
function test() {
    println_string("function[test] begin");

	var int int_value_1;
	var int int_value_2;
	var int int_value_3;
	var int int_value_4;
	var int int_value_5;
	var int int_value_6;
	var int int_value_7;
	var int int_value_8;
	var int int_value_9;

    println_string("\ntest case 1");
    println_int(int_value_1);
    println_int(int_value_2);
    println_int(int_value_3);
    println_int(int_value_4);
    println_int(int_value_5);
    println_int(int_value_6);
    println_int(int_value_7);
    println_int(int_value_8);
    println_int(int_value_9);
    debug_assert(int_value_1 == 0);
    debug_assert(int_value_2 == 0);
    debug_assert(int_value_3 == 0);
    debug_assert(int_value_4 == 0);
    debug_assert(int_value_5 == 0);
    debug_assert(int_value_6 == 0);
    debug_assert(int_value_7 == 0);
    debug_assert(int_value_8 == 0);
    debug_assert(int_value_9 == 0);

    println_string("\ntest case 2");
    int_value_1 = 1;
    int_value_2 = 2;
    int_value_3 = 3;
    int_value_4 = 4;
    int_value_5 = 5;
    int_value_6 = 6;
    int_value_7 = 7;
    int_value_8 = 8;
    int_value_9 = 9;
    println_int(int_value_1);
    println_int(int_value_2);
    println_int(int_value_3);
    println_int(int_value_4);
    println_int(int_value_5);
    println_int(int_value_6);
    println_int(int_value_7);
    println_int(int_value_8);
    println_int(int_value_9);
    debug_assert(int_value_1 == 1);
    debug_assert(int_value_2 == 2);
    debug_assert(int_value_3 == 3);
    debug_assert(int_value_4 == 4);
    debug_assert(int_value_5 == 5);
    debug_assert(int_value_6 == 6);
    debug_assert(int_value_7 == 7);
    debug_assert(int_value_8 == 8);
    debug_assert(int_value_9 == 9);

    println_string("function[test] end");
}