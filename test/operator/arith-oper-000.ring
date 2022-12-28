//
// File:    arith-oper-000.ring
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




println_string("\ntest case 1");

int_value_1, int_value_2 = 0, 0;
println_int(int_value_1);
debug_assert(int_value_1 == 0);
println_int(int_value_2);
debug_assert(int_value_2 == 0);

for(int_value_1=0; int_value_1<100; int_value_1++){
    int_value_2 += 4;
}

println_int(int_value_1);
debug_assert(int_value_1 == 100);
println_int(int_value_2);
debug_assert(int_value_2 == 400);






println_string("\ntest case 2");


int_value_1, int_value_2 = 50, 52;
println_int(int_value_1);
debug_assert(int_value_1 == 50);
println_int(int_value_2);
debug_assert(int_value_2 == 52);

for(; int_value_1<100; int_value_1++){
    int_value_2 += 4;
}

println_int(int_value_1);
debug_assert(int_value_1 == 100);
println_int(int_value_2);
debug_assert(int_value_2 == 252);





println_string("\ntest case 3");




int_value_1, int_value_2 = 0, 0;
println_int(int_value_1);
debug_assert(int_value_1 == 0);
println_int(int_value_2);
debug_assert(int_value_2 == 0);

for(int_value_1=0; int_value_1<100; int_value_1++){
    int_value_2 += int_value_1;
}

println_int(int_value_1);
debug_assert(int_value_1 == 100);
println_int(int_value_2);
debug_assert(int_value_2 == 4950);

