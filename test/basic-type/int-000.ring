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

println_int(0);
println_int(-0);

println_int(1);
println_int(-1);

println_int(255);
println_int(-255);

println_int(256);
println_int(-256);

println_int(65535);
println_int(-65535);

println_int(65536);
println_int(-65536);

println_int(65537);
println_int(-65537);

println_int(2147483647);
println_int(-2147483647);

println_int(2147483648);
println_int(-2147483648);

println_string("--------");
println_string("");

var int int_value_1 = 0;
println_int(int_value_1);
debug_assert(int_value_1 == 0);


println_string("");


int_value_1 = 1;
println_int(int_value_1);
debug_assert(int_value_1 == 1);


println_string("");


int_value_1 = 2;
println_int(int_value_1);
debug_assert(int_value_1 == 2);


println_string("");


int_value_1 = 255;
println_int(int_value_1);
debug_assert(int_value_1 == 255);


println_string("");


int_value_1 = 256;
println_int(int_value_1);
debug_assert(int_value_1 == 256);


println_string("");


int_value_1 = 65535;
println_int(int_value_1);
debug_assert(int_value_1 == 65535);


println_string("");


int_value_1 = 65536;
println_int(int_value_1);
debug_assert(int_value_1 == 65536);


println_string("");


int_value_1 = 2147483647;
println_int(int_value_1);
debug_assert(int_value_1 == 2147483647);


println_string("");


int_value_1 = 2147483648;
println_int(int_value_1);
debug_assert(int_value_1 == -2147483648);


println_string("");


int_value_1 = -0;
println_int(int_value_1);
debug_assert(int_value_1 == 0);


println_string("");


int_value_1 = -1;
println_int(int_value_1);
debug_assert(int_value_1 == -1);


println_string("");


int_value_1 = -255;
println_int(int_value_1);
debug_assert(int_value_1 == -255);


println_string("");


int_value_1 = -256;
println_int(int_value_1);
debug_assert(int_value_1 == -256);


println_string("");


int_value_1 = -65535;
println_int(int_value_1);
debug_assert(int_value_1 == -65535);


println_string("");


int_value_1 = -65536;
println_int(int_value_1);
debug_assert(int_value_1 == -65536);


println_string("");


int_value_1 = -2147483647;
println_int(int_value_1);
debug_assert(int_value_1 == -2147483647);


println_string("");


int_value_1 = -2147483648;
println_int(int_value_1);
debug_assert(int_value_1 == -2147483648);


println_string("");



/*
/*


var int int_value_2 = 1;
print("int_value_2(1)=", int_value_2, "\n");
int_value_2 = -int_value_2;
print("int_value_2(-1)=", int_value_2, "\n");


print("\n\n");

var int int_value_3 = 2147483648;
print("int_value_3(2147483648)=", int_value_3, "\n");
int_value_3 = -int_value_3;
print("int_value_3(-2147483648)=", int_value_3, "\n");

print("\n\n");


var int int_value_4 = -2147483648;
print("int_value_4(-2147483648)=", int_value_4, "\n");
int_value_4 = -int_value_4;
print("int_value_4(-2147483648)=", int_value_4, "\n");


print("\n\n");

var int int_value_5 = 0-2147483648;
print("int_value_5(0-2147483648)=", int_value_5, "\n");
int_value_5 = -int_value_5;
print("int_value_5(-2147483648)=", int_value_5, "\n");

*/