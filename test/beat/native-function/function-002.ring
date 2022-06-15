//
// File:    function-002.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-15
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


// 先简单写，后改成 rust的方式
printf("_, _, _, _\n", true, 123, 456.123456, "hello world");

printf("_, _\n", true, false);
printf("_, _\n", 123, 234);
printf("_, _\n", 123.456, 654.321);
printf("_, _\n", "hello world", "hello world");
