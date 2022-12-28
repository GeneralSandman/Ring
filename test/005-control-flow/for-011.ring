//
// File:    int-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-26
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------

var int int_value;
var int count;


println_string("[test case 1]");

for(int_value = 0; int_value < 10; ++int_value) {
    println_int(int_value);
}



println_string("finish for====");
println_int(int_value);
println_bool(int_value == 10);
debug_assert(int_value == 10);
println_string("finish for====");




// ------------------

println_string("\n[test case 2]");

count = 0;

for(int_value = 0; int_value < 10; ++int_value) {
    if(int_value > 5) {
        continue;
    }
    count++;
    println_int(int_value);
}



println_string("finish for====");
println_int(int_value);
println_bool(int_value == 10);
debug_assert(int_value == 10);

println_int(count);
debug_assert(count == 6);

println_string("finish for====");



// ------------------

println_string("\n[test case 3]");

count = 0;
for(int_value = 0; int_value < 10; ++int_value) {
    if(int_value > 5) {
        break;
        continue;
    }
    count++;
    println_int(int_value);
}



println_string("finish for====");
println_int(int_value);
println_bool(int_value == 6);
debug_assert(int_value == 6);

println_int(count);
debug_assert(count == 6);

println_string("finish for====");
