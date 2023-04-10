//
// File:    006-variable/assign-operation-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-10
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



var int int_value_1;

int_value_1 = 101;
println_int(int_value_1);

int_value_1 = true ? 2 : 1; 
println_int(int_value_1);

int_value_1 = false ? 2 : 1; 
println_int(int_value_1);


int_value_1 = true ? 1+1-1*2*3*4 : 2*2*2*2 ;
println_int(int_value_1);

int_value_1 = false ? 1+1-1*2*3*4 : 2*2*2*2 ;
println_int(int_value_1);


println_string("-----");

var int int_value_2;
var int a;
var int b;

a = 10;
b = 9;


if(a > b) {
	int_value_2 = a;
} else {
	int_value_2 = b;
}
println_int(int_value_2);



int_value_2 = a > b ? a : b ;
println_int(int_value_2);
