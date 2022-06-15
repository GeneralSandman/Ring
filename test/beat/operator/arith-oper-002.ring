//
// File:    arith-oper-002.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-15
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------


var double double_value;


// double_value = 1.1;
// println_double(double_value);
// debug_assert(double_value == 1.1);

println_string("\ntest case");
double_value = 1.1 + 2.2 + 3.3;
println_double(double_value);
debug_assert(double_value == 6.6);


println_string("\ntest case");
double_value = double_value + 1.1;
println_double(double_value);
debug_assert(7.700000 == double_value); // FIXME: bug

println_string("\ntest case");
double_value += 1.1;
println_double(double_value);
debug_assert(double_value == 8.8); // FIXME: bug


println_string("\ntest case");
double_value += 1.1 + 2.2;
println_double(double_value);
debug_assert(double_value == 12.1); 

