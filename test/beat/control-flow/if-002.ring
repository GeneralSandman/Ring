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


debug_assert(true or true);
if(true or true) {
	println_string("check (true or true) pass");
} else {
	println_string("check (true or true) [failed]");
}


println_string("");

debug_assert(false or true);
if(false or true) {
	println_string("check (false or true) pass");
} else {
	println_string("check (false or true) [failed]");
}

println_string("");

debug_assert(true or false);
if(true or false) {
	println_string("check (true or false) pass");
} else {
	println_string("check (true or false) [failed]");
}

println_string("");
if(false or false) {
	println_string("check (false or false) [failed]");
} else {
	println_string("check (false or false) pass");
}

