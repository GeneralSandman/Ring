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



debug_assert(true and true);
if(true and true) {
	println_string("check (true and true) pass");
} else {
	println_string("check (true and true) [failed]");
}


println_string("");
if(true and false) {
	println_string("check (true and false) [failed]");
} else {
	println_string("check (true and false) pass");
}

println_string("");
if(false and true) {
	println_string("check (false and true) [failed]");
} else {
	println_string("check (false and true) pass");
}

println_string("");
if(false and false) {
	println_string("check (false and false) [failed]");
} else {
	println_string("check (false and false) pass");
}