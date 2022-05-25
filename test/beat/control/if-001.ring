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


var bool bool_value;

debug_assert(true == true);
if(true) {
	println_string("check pass");
} else {
	println_string("check pass [failed]");
}

println_string("");

debug_assert(false == false);
if(false) {
	println_string("check pass [failed]\n");
} else {
	println_string("check pass\n");
}


println_string("");
println_string("");


debug_assert(not false == true);
if(not false) {
	println_string("check pass");
} else {
	println_string("check pass [failed]");
}

println_string("");

debug_assert(not true == false);
if(not true) {
	println_string("check pass [failed]\n");
} else {
	println_string("check pass\n");
}

