//
// File:    int-020.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-16
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);


var bool bool_value_1;
var bool bool_value_2;


// ----------------
bool_value_1 = true;
bool_value_2 = true;
if(bool_value_1 and bool_value_2) {
    println_string("both true");
} elseif (bool_value_1 or bool_value_2) {
    println_string("has one true");
} else {
    println_string("both false");
}



// ----------------
bool_value_1 = true;
bool_value_2 = false;
if(bool_value_1 and bool_value_2) {
    println_string("both true");
} elseif (bool_value_1 or bool_value_2) {
    println_string("has one true");
} else {
    println_string("both false");
}



// ----------------
bool_value_1 = false;
bool_value_2 = true;
if(bool_value_1 and bool_value_2) {
    println_string("both true");
} elseif (bool_value_1 or bool_value_2) {
    println_string("has one true");
} else {
    println_string("both false");
}



// ----------------
bool_value_1 = false;
bool_value_2 = false;
if(bool_value_1 and bool_value_2) {
    println_string("both true");
} elseif (bool_value_1 or bool_value_2) {
    println_string("has one true");
} else {
    println_string("both false");
}
