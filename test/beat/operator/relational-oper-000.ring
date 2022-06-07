//
// File:    relational-oper-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-06
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------

var bool bool_value_1;

var int int_value_1, int_value_2;

var double double_value_1, double_value_2;



println_string("\ntest case 1");
int_value_1 = 1;
int_value_2 = 2;
debug_assert(1 <  2);
debug_assert(1 <= 2);
debug_assert(int_value_1 <  int_value_2);
debug_assert(int_value_1 <= int_value_2);


println_string("\ntest case 2");
int_value_1 = -65536;
int_value_2 = 65535;
debug_assert(-65536 <  65535);
debug_assert(-65536 <= 65535);
debug_assert(int_value_1 <  int_value_2);
debug_assert(int_value_1 <= int_value_2);

debug_assert(65536 >  65535);
debug_assert(65536 >= 65535);
// debug_assert(-int_value_1 >  int_value_2); // FIXME: BUG segment fault
// debug_assert(-int_value_1 >= int_value_2); // FIXME: BUG segment fault





println_string("\ntest case 3");
double_value_1 = 1.23456;
double_value_2 = 1.2345;
debug_assert(1.23456 >  1.2345);
debug_assert(1.23456 >= 1.2345);
debug_assert(double_value_1 > double_value_2);
debug_assert(double_value_1 >= double_value_2);


println_string("\ntest case 4");
double_value_1 = 65535.23456;
double_value_2 = 65536.2345;
debug_assert(65535.23456 <  65536.2345);
debug_assert(65535.23456 <= 65536.2345);
debug_assert(double_value_1 < double_value_2);
debug_assert(double_value_1 <= double_value_2);



println_string("\ntest case 5");
double_value_1 = 65535.23456;
double_value_2 = 65536.2345;
debug_assert(65535.23456 <  65536.2345);
debug_assert(65535.23456 <= 65536.2345);
debug_assert(double_value_1 < 65536.2345);
debug_assert(double_value_1 <= 65536.2345);


println_string("\ntest case 6");
double_value_1 = 1.23456;
double_value_2 = 1.2345;
debug_assert(1.23456 >  double_value_2);
debug_assert(1.23456 >= double_value_2);
debug_assert(double_value_1 > 1.2345);
debug_assert(double_value_1 >= 1.2345);
