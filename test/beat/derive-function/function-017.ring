//
// File:    function-017.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-07
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


function test(var int int_value_1, var int int_value_2, var int int_value_3) -> (int) {
    var int result = 0;

    result = result + int_value_1;
    result = result + int_value_2;
    result = result + int_value_3;

    return result;
}


var int int_value;

int_value = 1 + 2;

int_value = test(11, 22, 33);
println_int(int_value);
debug_assert(int_value == 66);

int_value -= test(11, 22, 33);
println_int(int_value);
debug_assert(int_value == 0);
