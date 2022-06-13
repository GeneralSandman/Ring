//
// File:    function-014.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-31
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------


function increase_one(var int int_1) -> (int) {
    return int_1 + 1;
}

function add_two(var int int_1, var int int_2) -> (int) {
    return int_1 + int_2;
}





var int int_value_1;


println_string("\ntest case 1");
int_value_1 = 5;
debug_assert(int_value_1 == 5);

int_value_1 = increase_one(4);
debug_assert(int_value_1 == 5);

int_value_1 = add_two(2, 3);
debug_assert(int_value_1 == 5);


int_value_1 = 5;
int_value_1 += int_value_1;
debug_assert(int_value_1 == 10);





println_string("\ntest case 2");

int_value_1 = 5;
int_value_1 += increase_one(4);
println_int(int_value_1);
debug_assert(int_value_1 == 10);

int_value_1 += increase_one(4);
println_int(int_value_1);
debug_assert(int_value_1 == 15);




println_string("\ntest case 3");

int_value_1 = 5;
int_value_1 += add_two(13, 12);
println_int(int_value_1);
debug_assert(int_value_1 == 30);

int_value_1 += add_two(13, 12);
println_int(int_value_1);
debug_assert(int_value_1 == 55);



