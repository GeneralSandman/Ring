//
// File:    class-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-11
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
function main() -> (int) {
    println_string("function main");
    return 0;
}
