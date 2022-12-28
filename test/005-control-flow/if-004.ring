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


debug_assert(2 > 1);
if(2>1) {
	println_string("check 2>1 pass");
} else {
	println_string("check 2>1 [failed]");
}

println_string("");

if(2<1) {
	println_string("check 2<1 [failed]");
} else {
	println_string("check 2<1 pass");
}
