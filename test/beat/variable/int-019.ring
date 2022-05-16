//
// File:    int-019.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-16
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);


var bool bool_value_1;
var bool bool_value_2;

println_bool(bool_value_1);
println_bool(bool_value_2);


if(bool_value_1) {
    println_string("bool_value_1 is true");
} else {
    println_string("bool_value_1 is false");
}


bool_value_1 = true;

if(bool_value_1) {
    println_string("bool_value_1 is true");
} else {
    println_string("bool_value_1 is false");
}

