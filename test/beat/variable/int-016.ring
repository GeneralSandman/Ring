//
// File:    int-016.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-11
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);


var int int_value;

int_value = 1;
if(int_value == 2) {
    println_int(int_value);
    println_int(int_value);
} else {
    println_int(int_value);
}

/*
int_value = 0;
if(int_value) {
    int_value += 1;
} else {
    int_value += 2;
}
println_int(int_value);


int_value = 1;
if(int_value) {
    int_value += 3;
} else {
    int_value += 2;
}
println_int(int_value);

*/
