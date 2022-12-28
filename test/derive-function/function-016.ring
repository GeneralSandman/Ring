//
// File:    function-016.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-07
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





function add_one(var int parameter_1) -> (int) {
	return parameter_1 + 1;
}


function add(var int parameter_1, var int parameter_2) -> (int) {
	return parameter_1 + parameter_2;
}






var int int_value = 0;


println_string("\ntest case 1");
println_int(add_one(1));
// println_int(2 == add_one(1)); // FIXME: compiler error



int_value = add_one(add_one(add_one(add_one(add_one(-1)))));
println_int(int_value);
debug_assert(int_value == 4);



int_value = add_one(add_one(add_one(add_one(add_one(0)))));
println_int(int_value);
debug_assert(int_value == 5);

int_value = add_one(add_one(add_one(add_one(add_one(1)))));
println_int(int_value);
debug_assert(int_value == 6);




println_string("\ntest case 2");
int_value = add(1, add(2, 3));
println_int(int_value);
debug_assert(int_value == 6);



int_value = add(1, add(2, add(3, add(4, add(5, 6)))));
println_int(int_value);
debug_assert(int_value == 21);
