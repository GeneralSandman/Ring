//
// File:    assign-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-27
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------

var int int_value_1;
var int int_value_2;
var int tmp;

int_value_1 = 1;
int_value_2 = 2;
debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 2);
println_int(int_value_1);
println_int(int_value_2);


println_string("\ntest case 1");
tmp = int_value_1;
int_value_1 = int_value_2;
int_value_2 = tmp;
debug_assert(int_value_1 == 2);
debug_assert(int_value_2 == 1);
println_int(int_value_1);
println_int(int_value_2);



println_string("\ntest case 2");
int_value_1 = 4;
int_value_2 = 5;

int_value_1, int_value_2 = int_value_2, int_value_1;
debug_assert(int_value_1 == 5);
debug_assert(int_value_2 == 4);
println_int(int_value_1);
println_int(int_value_2);