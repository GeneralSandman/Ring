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

bool_value = true;
println_bool(bool_value);
debug_assert(bool_value == true);
if(bool_value) {
	println_string("bool_value is true");
} else {
	println_string("bool_value is false [FAILED]");
}
println_bool(bool_value);
debug_assert(bool_value == true);


println_string("");

bool_value = true;
println_bool(not bool_value);
debug_assert(not bool_value == false);
if(not bool_value) {
	println_string("not bool_value is true [FAILED]");
} else {
	println_string("not bool_value is false");
}
println_bool(not bool_value);
debug_assert(not bool_value == false);


println_string("");
println_string("");



bool_value = false;
println_bool(bool_value);
debug_assert(bool_value == false);
if(bool_value) {
	println_string("bool_value is true [FAILED]");
} else {
	println_string("bool_value is false");
}
println_bool(bool_value);
debug_assert(bool_value == false);


println_string("");


bool_value = false;
println_bool(not bool_value);
debug_assert(not bool_value == true);
if(not bool_value) {
	println_string("bool_value is true");
} else {
	println_string("bool_value is false [FAILED]");
}
println_bool(not bool_value);
debug_assert(not bool_value == true);


println_string("");
println_string("");

