//
// File:    assign-003.ring
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


println_string("\ntest case 1");
var bool bool_value_0;
var int  int_value_0;
var double double_value_0;


println_bool(bool_value_0);
println_int(int_value_0);
println_double(double_value_0);

debug_assert(bool_value_0 == false);
debug_assert(int_value_0 == 0);
debug_assert(double_value_0 == 0.0);





println_string("\ntest case 2");
var bool bool_value_1     = true;
var int  int_value_1      = 1;
var double double_value_1 = 1.23;


println_bool(bool_value_1);
println_int(int_value_1);
println_double(double_value_1);

debug_assert(bool_value_1 == true);
debug_assert(int_value_1 == 1);
debug_assert(double_value_1 == 1.23);




println_string("\ntest case 3");
var bool bool_value_2     = true and true;
var int  int_value_2      = 2147483647;
var double double_value_2 = 2147483647.123;


println_bool(bool_value_2);
println_int(int_value_2);
println_double(double_value_2);

debug_assert(bool_value_2 == true);
debug_assert(int_value_2 == 2147483647);
debug_assert(double_value_2 == 2147483647.123);
