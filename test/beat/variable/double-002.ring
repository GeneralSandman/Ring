//
// File:    double-002.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-09
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);


var double double_value;



double_value = 1.1;
println_double(double_value);

double_value = 1.23456;
println_double(double_value);

double_value = 1.1 + 1.23456;
println_double(double_value);


/* double_value = 0-1.1; */
/* println_double(double_value); */
