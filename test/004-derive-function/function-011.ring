//
// File:    function-011.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-30
//

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


var int int_value_global_1;
var int int_value_global_2;




function test_1(var int int_value_1, var int int_value_2) {
    println_string("function test_1");

    println_int(int_value_1);
    println_int(int_value_2);

    debug_assert(int_value_1 == 123);
    debug_assert(int_value_2 == 234);

    return int_value_1, int_value_2;

}

@main
function main() {
debug_assert(int_value_global_1 == 0);
debug_assert(int_value_global_2 == 0);

int_value_global_1, int_value_global_2 = test_1(123, 234);

debug_assert(int_value_global_1 == 123);
debug_assert(int_value_global_2 == 234);




}
