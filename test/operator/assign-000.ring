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
var int int_value_3;
var int int_value_4;



println_string("test case1 --------");
debug_assert(int_value_1 == 0);
debug_assert(int_value_2 == 0);
debug_assert(int_value_3 == 0);
debug_assert(int_value_4 == 0);




println_string("test case2--------");
int_value_1 = 1;
int_value_2 = 2;
int_value_3 = 3;
int_value_4 = 4;

debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 2);
debug_assert(int_value_3 == 3);
debug_assert(int_value_4 == 4);




println_string("test case3--------");


int_value_1, int_value_2, int_value_3, int_value_4 = 1, 2, 3, 4;


debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 2);
debug_assert(int_value_3 == 3);
debug_assert(int_value_4 == 4);




println_string("test case4--------");


int_value_1, int_value_2 = 11, 22;
int_value_3, int_value_4 = 33, 44;


debug_assert(int_value_1 == 11);
debug_assert(int_value_2 == 22);
debug_assert(int_value_3 == 33);
debug_assert(int_value_4 == 44);




println_string("test case4--------");


int_value_1, int_value_2, int_value_3 = 111, 222, 333;
int_value_4 = 444;


debug_assert(int_value_1 == 111);
debug_assert(int_value_2 == 222);
debug_assert(int_value_3 == 333);
debug_assert(int_value_4 == 444);
