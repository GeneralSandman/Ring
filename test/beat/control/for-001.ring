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

int_value = -1;

debug_assert(int_value == -1);
println_int(int_value);
println_string("");

for(; int_value < 10; int_value = int_value + 1) {
	println_int(int_value);
}

println_string("");
debug_assert(int_value == 10);
println_int(int_value);
