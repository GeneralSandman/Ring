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


var int int_value_1;
var int int_value_2;
var int int_value_3;

int_value_1 = 1;
int_value_2 = 2;
int_value_3 = 3;
if(int_value_1 < int_value_2 and int_value_2 < int_value_3) {
	println_string("check (int_value_1 < int_value_2 and int_value_2 < int_value_3) pass\n");
} else {
	println_string("check (int_value_1 < int_value_2 and int_value_2 < int_value_3) failed\n");
}


if(int_value_1 <= int_value_2 and int_value_2 < int_value_3) {
	println_string("check (int_value_1 <= int_value_2 and int_value_2 < int_value_3) pass\n");
} else {
	println_string("check (int_value_1 <= int_value_2 and int_value_2 < int_value_3) failed\n");
}


if(int_value_1 > int_value_2 or int_value_2 < int_value_3) {
	println_string("check (int_value_1 > int_value_2 or int_value_2 < int_value_3) pass\n");
} else {
	println_string("check (int_value_1 > int_value_2 or int_value_2 < int_value_3) failed\n");
}
