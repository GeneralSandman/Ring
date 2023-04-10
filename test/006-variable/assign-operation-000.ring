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


var int int_value = 1;

// assign
int_value = 2;
println_int(int_value);


// add-assign
println_string("\ntest add-assign operation");
int_value += 1;
println_int(int_value);

int_value += 2;
println_int(int_value);

int_value += 10;
println_int(int_value);

int_value += 1+2+3+4+5+6+7;
println_int(int_value);



// sub-assign
println_string("\ntest sub-assign operation");
int_value -= 1;
println_int(int_value);

int_value -= 1;
println_int(int_value);

int_value -= 4;
println_int(int_value);

int_value -= 4 - 1 - 1 -1 + 3;
println_int(int_value);



println_string("\ntest mul-assign operation");
int_value *= 100;
println_int(int_value);

int_value *= 2;
println_int(int_value);

int_value *= 30;
println_int(int_value);

int_value *= 1 + 1;
println_int(int_value);



println_string("\ntest div-assign operation");
int_value /= 5;
println_int(int_value);

int_value /= 4;
println_int(int_value);

int_value /= 3;
println_int(int_value);

int_value /= 3 + 1 + 2;
println_int(int_value);



println_string("\ntest mod-assign operation");
int_value %= 60 - 1;
println_int(int_value);

int_value %= 10;
println_int(int_value);

int_value %= 2 + 1;
println_int(int_value);

int_value %= 1;
println_int(int_value);