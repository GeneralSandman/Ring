//
// File:    string-001.ring
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


println_string("123" .. "345");
println_string("123" .. "345" .. "567");
println_string("123" .. "345" .. "567" .. "789");

println_string("");
println_string("-----------");

var string string_value;


println_string("\ntest case 1");
string_value = "123-";
println_string(string_value);
debug_assert(string_value == "123-");



println_string("\ntest case 2");
string_value = "123" .. "345";
println_string(string_value);
debug_assert(string_value == "123345");


println_string("\ntest case 3");
string_value = "123" .. "345" .. "567";
println_string(string_value);
debug_assert(string_value == "123345567");


println_string("\ntest case 4");
string_value = "123" .. "345" .. "567" .. "789";
println_string(string_value);
debug_assert(string_value == "123345567789");

