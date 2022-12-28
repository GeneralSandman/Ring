//
// File:    condition-oper-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-13
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------


var bool bool_value;
var int int_value;


println_string("\ntest case 1");
bool_value = false;
println_string(bool_value ? "bool_value is true" : "bool_value is false");
bool_value = true;
println_string(bool_value ? "bool_value is true" : "bool_value is false");


println_string("\ntest case 2");
bool_value = false;
println_int(bool_value ? 100 : -100);
bool_value = true;
println_int(bool_value ? 100 : -100);


println_string("\ntest case 3");
bool_value = false;
println_double(bool_value ? 100123.0 : 100.123);
bool_value = true;
println_double(bool_value ? 100123.0 : 100.123);




// -----------------------



println_string("\ntest case 1");
println_string(false ? "bool_value is true" : "bool_value is false");
println_string(true ? "bool_value is true" : "bool_value is false");


println_string("\ntest case 2");
println_int(false ? 100 : -100);
println_int(true ? 100 : -100);


println_string("\ntest case 3");
println_double(false ? 100.123 : 100123.0);
println_double(true ? 100.123 : 100123.0);
