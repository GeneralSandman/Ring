//
// File:    int-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------


var int int_value;

int_value = 0;
println_int(int_value);
debug_assert(int_value == 0);

int_value = -0;
println_int(int_value);
debug_assert(int_value == 0);

int_value = 0-0;
println_int(int_value);
debug_assert(int_value == 0);


println_string("");


int_value = 1;
println_int(int_value);
debug_assert(int_value == 1);

int_value = -1;
println_int(int_value);
debug_assert(int_value == -1);

int_value = 0-1;
println_int(int_value);
debug_assert(int_value == -1);


println_string("");


int_value = 2;
println_int(int_value);
debug_assert(int_value == 2);

int_value = -2;
println_int(int_value);
debug_assert(int_value == -2);

int_value = 0-2;
println_int(int_value);
debug_assert(int_value == -2);


println_string("");


int_value = 2147483647;
println_int(int_value);
debug_assert(int_value == 2147483647);

int_value = -2147483647;
println_int(int_value);
debug_assert(int_value == -2147483647);

int_value = 0-2147483647;
println_int(int_value);
debug_assert(int_value == -2147483647);


println_string("");


int_value = 2147483648;
println_int(int_value);
debug_assert(int_value == 2147483648);

int_value = -2147483648;
println_int(int_value);
debug_assert(int_value == -2147483648);

int_value = 0-2147483648;
println_int(int_value);
debug_assert(int_value == -2147483648);
