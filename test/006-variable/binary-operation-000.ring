//
// File:    006-variable/assign-operation-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-10
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


var int int_value;
int_value = 0;
println_int(int_value);

int_value = 123456;
println_int(int_value);

int_value = 123456+234234;
println_int(int_value);

int_value = 2342*2342;
println_int(int_value);

int_value = 2342/2342;
println_int(int_value);

int_value = 234+2342*100;
println_int(int_value);

int_value = 234+2342/100;
println_int(int_value);

int_value = 234+2342/100-100/1;
println_int(int_value);

int_value = 123456+123456*10-100*10+10010;
println_int(int_value);

int_value = int_value + 10;
println_int(int_value);

int_value = int_value - 10;
println_int(int_value);

int_value = int_value * 10;
println_int(int_value);

int_value = int_value / 10;
println_int(int_value);

int_value = int_value % 10;
println_int(int_value);

int_value = int_value % 7;
println_int(int_value);

int_value = int_value % 5;
println_int(int_value);

