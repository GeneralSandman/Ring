//
// File:    int-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
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

@main
function main() {
var bool bool_value;
println_bool(bool_value);
debug_assert(bool_value == false);


var int int_value;
println_int(int_value);
debug_assert(int_value == 0);


var double double_value;
println_double(double_value);
debug_assert(double_value == 0.0);
}