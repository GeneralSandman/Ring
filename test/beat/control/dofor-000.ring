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

// -----------------------------


var int int_value;

// -----------
println_string("[Test Case 1]");

for(int_value = 0; int_value < 10; int_value++) {
    println_int(int_value);
}

debug_assert(int_value == 10);
println_int(int_value);

println_string("");


// -----------
println_string("[Test Case 2]");
do(int_value = 0) {
    println_int(int_value);
}for(int_value<10; int_value++);

debug_assert(int_value == 10);
println_int(int_value);