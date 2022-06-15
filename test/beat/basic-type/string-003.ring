//
// File:    string-003.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-18
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);


var bool bool_value;
var int int_value;
var double double_value;
var string string_value;

var string string_value_1;
var string string_value_2;


string_value_1 = "abcdefg";
println_string(string_value_1);


string_value_2 = "1234456";
println_string(string_value_2);


string_value_1 = "1" .. "2" .. "3";
string_value_2 = "12" .. "3";
println_string(string_value_1);
println_string(string_value_2);


if(string_value_1 == string_value_2) {
    println_string("string_value_1 == string_value_2");
    debug_assert(true);   
} else {
    println_string("string_value_1 != string_value_2");
    debug_assert(false);   
}



if("a" == "b") {
    println_string("a == b");
    debug_assert(false);   
} else {
    println_string("a != b");
    debug_assert(true);   
}

if("ab" == "ab") {
    println_string("ab == ab");
    debug_assert(true);   
} else {
    println_string("ab != ab");
    debug_assert(false);   
}



println_string(string_value_1);
println_string(string_value_2);
println_string(string_value_1 .. string_value_2);

string_value = string_value_1 .. string_value_2;
println_string(string_value);
