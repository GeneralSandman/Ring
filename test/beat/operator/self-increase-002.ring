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
var int result;


int_value = 1;
result = 1;

debug_assert(int_value == 1);
debug_assert(result == 1);
println_string("");


int_value = 1;
result = 1;

result = int_value-1;
debug_assert(int_value == 1);
debug_assert(result == 0);
println_string("");


int_value = 1;
result = 1;

result = int_value--;
debug_assert(int_value == 0);
debug_assert(result == 1);
println_string("");


int_value = 1;
result = 1;

result = --int_value;
debug_assert(int_value == 0);
debug_assert(result == 0);
println_string("");


// ------------


int_value = 10;
result = 10;

result = int_value-1;
debug_assert(int_value == 10);
debug_assert(result == 9);
println_string("");



int_value = 10;
result = 10;

result = int_value++;
debug_assert(int_value == 11);
debug_assert(result == 10);
println_string("");


int_value = 10;
result = 10;

result = ++int_value;
debug_assert(int_value == 11);
debug_assert(result == 11);
println_string("");

