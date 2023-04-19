//
// File:    main-entry-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-11
//

package job

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

function test(var int int_value_1, var int int_value_2) {
	var int int_value_3;
	var int int_value_4;

    int_value_1 = 1;
    int_value_2 = 2;
    int_value_3 = 3;
    int_value_4 = 4;

    return int_value_1, int_value_2, int_value_3, int_value_4;
}


@main
function main() {
    var int int_value_1;
var int int_value_2;
var int int_value_3;
var int int_value_4;
    
int_value_1, int_value_2, int_value_3, int_value_4 = test(0, 0);

debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 2);
debug_assert(int_value_3 == 3);
debug_assert(int_value_4 == 4);

int_value_1+=1;
debug_assert(int_value_1 == 2);
}
