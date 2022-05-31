//
// File:    function-009.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-30
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------



function test() {
	var int int_value_local_1;
	var int int_value_local_2;
	var int int_value_local_3;
	var int int_value_local_4;
	var int int_value_local_5;
	var int int_value_local_6;
	var int int_value_local_7;
	var int int_value_local_8;
	var int int_value_local_9;
	var int int_value_local_10;


	int_value_local_1 = 1;
	int_value_local_2 = 2;
	int_value_local_3 = 3;
	int_value_local_4 = 4;
	int_value_local_5 = 5;
	int_value_local_6 = 6;
	int_value_local_7 = 7;
	int_value_local_8 = 8;
	int_value_local_9 = 9;
	int_value_local_10 = 10;


    println_int(int_value_local_1);
    println_int(int_value_local_2);
    println_int(int_value_local_3);
    println_int(int_value_local_4);
    println_int(int_value_local_5);
    println_int(int_value_local_6);
    println_int(int_value_local_7);
    println_int(int_value_local_8);
    println_int(int_value_local_9);
    println_int(int_value_local_10);

    debug_assert(int_value_local_1 == 1);
    debug_assert(int_value_local_2 == 2);
    debug_assert(int_value_local_3 == 3);
    debug_assert(int_value_local_4 == 4);
    debug_assert(int_value_local_5 == 5);
    debug_assert(int_value_local_6 == 6);
    debug_assert(int_value_local_7 == 7);
    debug_assert(int_value_local_8 == 8);
    debug_assert(int_value_local_9 == 9);
    debug_assert(int_value_local_10 == 10);
}

test();


