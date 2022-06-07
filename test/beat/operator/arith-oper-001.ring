//
// File:    arith-oper-001.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-07
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------


var int int_value_1, int_value_2;
var double double_value_1, double_value_2;



println_string("\ntest case 1");
double_value_1 = 1.0 + 2.0*3.0 + 4.0/1.0 - 2.0;
println_double(double_value_1);
debug_assert(double_value_1 == 9.0);







println_string("\ntest case 2");
int_value_1, int_value_2 = 0, 0;
double_value_1, double_value_2 = 0.0, 0.0;


for(int_value_1=0; int_value_1<100; int_value_1++){
    double_value_1 += 4.0; // FIXME: bug add_int add_double
    double_value_2 = double_value_2 + 4.0;
}

println_double(double_value_1);
debug_assert(double_value_1 == 400.0);
println_double(double_value_2);
debug_assert(double_value_2 == 400.0);

