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


println_string("123");
println_string("123" + "345");
println_string("123" + "345" + "567");
println_string("123" + "345" + "567" + "789");

println_string("");
println_string("-----------");

var string string_value;

string_value = "123";
println_string(string_value);
// FIXME:
// debug_assert();


string_value = "123" + "345";
println_string(string_value);
// FIXME:
// debug_assert();

string_value = "123" + "345" + "567";
println_string(string_value);
// FIXME:
// debug_assert();

string_value = "123" + "345" + "567" + "789";
println_string(string_value);
// FIXME:
// debug_assert();



/* string_value = "1" + <string>(1+2+3); */
/* println_string(string_value); */

/* string_value = "1" + <string>int_value; */
/* println_string(string_value); */

/* string_value = "1" + <string>(int_value + int_value); */
/* println_string(string_value); */

/* string_value = "1" + "1"; */
/* println_string(string_value); */
