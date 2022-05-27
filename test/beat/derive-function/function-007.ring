//
// File:    function-003.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-23
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------



function test_return_1() {
	var int int_value_local_1;
	int_value_local_1 = 1;
    return int_value_local_1++;
}


function test_return_2() {
	var int int_value_local_1;
	int_value_local_1 = 2;
    return int_value_local_1++, int_value_local_1;
}

function test_return_3() {
	var int int_value_local_1;
	int_value_local_1 = 4;
    return int_value_local_1++, int_value_local_1++, int_value_local_1;
}


var int int_value_1;
var int int_value_2;
var int int_value_3;
var int int_value_4;
var int int_value_5;
var int int_value_6;

debug_assert(int_value_1 == 0);
debug_assert(int_value_2 == 0);
debug_assert(int_value_3 == 0);
debug_assert(int_value_4 == 0);
debug_assert(int_value_5 == 0);
debug_assert(int_value_6 == 0);

println_int(int_value_1);
println_int(int_value_2);
println_int(int_value_3);
println_int(int_value_4);
println_int(int_value_5);
println_int(int_value_6);



// ----------
println_string("\ntest case 1");
int_value_1 = test_return_1();
debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 0);
debug_assert(int_value_3 == 0);
debug_assert(int_value_4 == 0);
debug_assert(int_value_5 == 0);
debug_assert(int_value_6 == 0);

println_int(int_value_1);
println_int(int_value_2);
println_int(int_value_3);
println_int(int_value_4);
println_int(int_value_5);
println_int(int_value_6);


println_string("\ntest case 2");
int_value_1, int_value_2 = test_return_2();
debug_assert(int_value_1 == 2);
debug_assert(int_value_2 == 3);
debug_assert(int_value_3 == 0);
debug_assert(int_value_4 == 0);
debug_assert(int_value_5 == 0);
debug_assert(int_value_6 == 0);

println_int(int_value_1);
println_int(int_value_2);
println_int(int_value_3);
println_int(int_value_4);
println_int(int_value_5);
println_int(int_value_6);


println_string("\ntest case 3");
int_value_1, int_value_2, int_value_3 = test_return_3();
debug_assert(int_value_1 == 4);
debug_assert(int_value_2 == 5);
debug_assert(int_value_3 == 6);
debug_assert(int_value_4 == 0);
debug_assert(int_value_5 == 0);
debug_assert(int_value_6 == 0);


println_int(int_value_1);
println_int(int_value_2);
println_int(int_value_3);
println_int(int_value_4);
println_int(int_value_5);
println_int(int_value_6);


println_string("\ntest case 4");
int_value_1, int_value_2, int_value_3, int_value_4, int_value_5, int_value_6 = test_return_1(), test_return_2(), test_return_3();
debug_assert(int_value_1 == 1);
debug_assert(int_value_2 == 2);
debug_assert(int_value_3 == 3);
debug_assert(int_value_4 == 4);
debug_assert(int_value_5 == 5);
debug_assert(int_value_6 == 6);

println_int(int_value_1);
println_int(int_value_2);
println_int(int_value_3);
println_int(int_value_4);
println_int(int_value_5);
println_int(int_value_6);







