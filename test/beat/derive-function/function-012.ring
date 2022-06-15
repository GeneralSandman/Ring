//
// File:    function-012.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-31
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);
function print(var any value) -> (int);
function println(var any value) -> (int);
function printf(var string format, var any value)   -> (int);
function printfln(var string format, var any value) -> (int);


// -----------------------------



function test(var int parameter_1, var int parameter_2, var int parameter_3, var int parameter_4, var int parameter_5, var int parameter_6, var int parameter_7, var int parameter_8, var int parameter_9, var int parameter_10) -> (int) {
	var int int_value_local_1;
	var int int_value_local_2;
	var int int_value_local_3;
	var int int_value_local_4;
	var int int_value_local_5;
	var int int_value_local_6;
	var int int_value_local_7;
	var int int_value_local_8;
	var int int_value_local_9;
	var int int_value_local_10;


	int_value_local_1 = 1;
	int_value_local_2 = 2;
	int_value_local_3 = 3;
	int_value_local_4 = 4;
	int_value_local_5 = 5;
	int_value_local_6 = 6;
	int_value_local_7 = 7;
	int_value_local_8 = 8;
	int_value_local_9 = 9;
	int_value_local_10 = 10;

    debug_assert(int_value_local_1 == 1);
    debug_assert(int_value_local_2 == 2);
    debug_assert(int_value_local_3 == 3);
    debug_assert(int_value_local_4 == 4);
    debug_assert(int_value_local_5 == 5);
    debug_assert(int_value_local_6 == 6);
    debug_assert(int_value_local_7 == 7);
    debug_assert(int_value_local_8 == 8);
    debug_assert(int_value_local_9 == 9);
    debug_assert(int_value_local_10 == 10);

    debug_assert(parameter_1 == 11);
    debug_assert(parameter_2 == 12);
    debug_assert(parameter_3 == 13);
    debug_assert(parameter_4 == 14);
    debug_assert(parameter_5 == 15);
    debug_assert(parameter_6 == 16);
    debug_assert(parameter_7 == 17);
    debug_assert(parameter_8 == 18);
    debug_assert(parameter_9 == 19);
    debug_assert(parameter_10 == 20);

	return int_value_local_1 +
	int_value_local_2 +
	int_value_local_3 +
	int_value_local_4 +
	int_value_local_5 +
	int_value_local_6 +
	int_value_local_7 +
	int_value_local_8 +
	int_value_local_9 +
	int_value_local_10 +
	parameter_1 +
	parameter_2 +
	parameter_3 +
	parameter_4 +
	parameter_5 +
	parameter_6 +
	parameter_7 +
	parameter_8 +
	parameter_9 +
	parameter_10;
}


var int result;
result = test(11,12,13,14,15,16,17,18,19,20);

println_string("\ntest case 1 ======");
println_int(result);
debug_assert(result == 210);



