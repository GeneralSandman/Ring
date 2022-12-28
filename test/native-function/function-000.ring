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

var bool bool_value;
var int int_value;
var double double_value;
var string string_value;

bool_value = true;
println_bool(true);
println_bool(bool_value);

int_value = 1;
println_int(1);
println_int(int_value);

double_value = 1.1;
println_double(1.1);
println_double(double_value);

string_value = "hello world";
println_string("hello world");
println_string(string_value);


debug_assert(true == true);
debug_assert(true != false);

debug_assert(1 == 1);
debug_assert(1 != 2);

debug_assert(1.1 == 1.1);
debug_assert(1.1 != 1.2);

debug_assert("hello world" == "hello world");
debug_assert("hello world" != "hello world!");


exit(0);


println_string("cant't execute this code");

