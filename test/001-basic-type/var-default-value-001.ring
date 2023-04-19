//
// File:    var-default-value-001.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-31
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

var bool bool_value_1;
var bool bool_value_2, bool_value_3;
var bool bool_value_4, bool_value_5, bool_value_6;

println_string("\ntest case BOOL");
println_bool(bool_value_1);
println_bool(bool_value_2);
println_bool(bool_value_3);
println_bool(bool_value_4);
println_bool(bool_value_5);
println_bool(bool_value_6);
debug_assert(bool_value_1 == false);
debug_assert(bool_value_2 == false);
debug_assert(bool_value_3 == false);
debug_assert(bool_value_4 == false);
debug_assert(bool_value_5 == false);
debug_assert(bool_value_6 == false);








var int int_value_1;
var int int_value_2, int_value_3;
var int int_value_4, int_value_5, int_value_6;

println_string("\ntest case INT");
println_int(int_value_1);
println_int(int_value_2);
println_int(int_value_3);
println_int(int_value_4);
println_int(int_value_5);
println_int(int_value_6);
debug_assert(int_value_1 == 0);
debug_assert(int_value_2 == 0);
debug_assert(int_value_3 == 0);
debug_assert(int_value_4 == 0);
debug_assert(int_value_5 == 0);
debug_assert(int_value_6 == 0);






var double double_value_1;
var double double_value_2, double_value_3;
var double double_value_4, double_value_5, double_value_6;

println_string("\ntest case DOUBLE");
println_double(double_value_1);
println_double(double_value_2);
println_double(double_value_3);
println_double(double_value_4);
println_double(double_value_5);
println_double(double_value_6);
debug_assert(double_value_1 == 0.0);
debug_assert(double_value_2 == 0.0);
debug_assert(double_value_3 == 0.0);
debug_assert(double_value_4 == 0.0);
debug_assert(double_value_5 == 0.0);
debug_assert(double_value_6 == 0.0);



}