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
do(int_value = 0) {
    if(int_value == 5) {
        break;
    }
}for(int_value<10; int_value++);

println_string("finish for====");
debug_assert(int_value == 5);
println_int(int_value);
println_string("finish for====");