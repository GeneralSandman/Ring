//
// File:    var-default-value-002.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-31
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------

var bool bool_value_1 = true;
var bool bool_value_2, bool_value_3 = true, true;
var bool bool_value_4, bool_value_5, bool_value_6 = true, true, true;

println_string("\ntest case BOOL");
println_bool(bool_value_1);
println_bool(bool_value_2);
println_bool(bool_value_3);
println_bool(bool_value_4);
println_bool(bool_value_5);
println_bool(bool_value_6);
debug_assert(bool_value_1 == true);
debug_assert(bool_value_2 == true);
debug_assert(bool_value_3 == true);
debug_assert(bool_value_4 == true);
debug_assert(bool_value_5 == true);
debug_assert(bool_value_6 == true);






var int int_value_1 = 1;
var int int_value_2, int_value_3 = 2, 3;
var int int_value_4, int_value_5, int_value_6 = 4, 5, 6;

println_string("\ntest case INT");
println_int(int_value_1);
println_int(int_value_2);
println_int(int_value_3);
println_int(int_value_4);
println_int(int_value_5);
println_int(int_value_6);
debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 2);
debug_assert(int_value_3 == 3);
debug_assert(int_value_4 == 4);
debug_assert(int_value_5 == 5);
debug_assert(int_value_6 == 6);






var double double_value_1 = 1.1;
var double double_value_2, double_value_3 = 2.2, 3.3;
var double double_value_4, double_value_5, double_value_6 = 4.4, 5.5, 6.6;

println_string("\ntest case DOUBLE");
println_double(double_value_1);
println_double(double_value_2);
println_double(double_value_3);
println_double(double_value_4);
println_double(double_value_5);
println_double(double_value_6);
debug_assert(double_value_1 == 1.1);
debug_assert(double_value_2 == 2.2);
debug_assert(double_value_3 == 3.3);
debug_assert(double_value_4 == 4.4);
debug_assert(double_value_5 == 5.5);
debug_assert(double_value_6 == 6.6);



