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


var int int_value_1;
var int int_value_2;
var int int_value_3;
var int int_value_4;
var int count;

// -----------
println_string("[Test Case 1]");

count = 0;

for(int_value_1 = 0; int_value_1<10; int_value_1++){
    do(int_value_2 = 0) {


        for(int_value_3 = 0; int_value_3<10; int_value_3++){
            do(int_value_4 = 0) {
        
                count++;

            }for(int_value_4<9; int_value_4++);
        }

    }for(int_value_2<9; int_value_2++);
}

println_string("finish for====");
debug_assert(count == 10 * 10 * 10 * 10);
println_int(count);
debug_assert(int_value_1 == 10);
debug_assert(int_value_2 == 9);
debug_assert(int_value_3 == 10);
debug_assert(int_value_4 == 9);
println_string("finish for====");



