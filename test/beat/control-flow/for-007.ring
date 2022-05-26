//
// File:    for-007.ring
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


for(int_value = 0;int_value < 20; int_value++) {
    println_int(int_value);
}

println_string("finish for====");
println_int(int_value);
debug_assert(int_value == 20);
println_string("finish for====");


// ---------------
println_string("");
println_string("");


for(int_value = 0;int_value < 20; int_value++) {
    if(int_value >= 10) {
        println_string("int_value >= 10 break");
        break;
    }
    println_int(int_value);
}

println_string("finish for====");
println_int(int_value);
debug_assert(int_value == 10);
println_string("finish for====");





// ---------------
println_string("");
println_string("");


for(int_value = 0;int_value < 20; int_value++) {
    if(int_value >= 10) {
        println_string("int_value >= 10 break");
        break;
    }
    println_int(int_value);
}

println_string("finish for====");
println_int(int_value);
debug_assert(int_value == 10);
println_string("finish for====");
