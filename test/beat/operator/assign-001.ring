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

var int tmp;


println_string("test case1 --------");
debug_assert(int_value_1 == 0);
debug_assert(int_value_2 == 0);
debug_assert(int_value_3 == 0);
debug_assert(int_value_4 == 0);




println_string("test case2 --------");
tmp = 1;
int_value_1 = tmp++;
int_value_2 = tmp++;
int_value_3 = tmp++;
int_value_4 = tmp++;

debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 2);
debug_assert(int_value_3 == 3);
debug_assert(int_value_4 == 4);


println_string("test case3 --------");
tmp = 1;
int_value_1 = ++tmp;
int_value_2 = ++tmp;
int_value_3 = ++tmp;
int_value_4 = ++tmp;

debug_assert(int_value_1 == 2);
debug_assert(int_value_2 == 3);
debug_assert(int_value_3 == 4);
debug_assert(int_value_4 == 5);





println_string("test case4 --------");
tmp = 1;
int_value_1, int_value_2, int_value_3, int_value_4 = tmp++, tmp++, tmp++, tmp++;

debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 2);
debug_assert(int_value_3 == 3);
debug_assert(int_value_4 == 4);



println_string("test case5 --------");
tmp = 1;
int_value_1, int_value_2, int_value_3, int_value_4 = ++tmp, ++tmp, ++tmp, ++tmp;

debug_assert(int_value_1 == 2);
debug_assert(int_value_2 == 3);
debug_assert(int_value_3 == 4);
debug_assert(int_value_4 == 5);




println_string("test case6 --------");
tmp = 1;
int_value_1, int_value_2 = ++tmp, ++tmp;
int_value_3, int_value_4 = ++tmp, ++tmp;

debug_assert(int_value_1 == 2);
debug_assert(int_value_2 == 3);
debug_assert(int_value_3 == 4);
debug_assert(int_value_4 == 5);
