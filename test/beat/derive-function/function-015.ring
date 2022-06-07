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


function max(var int parameter_1, var int parameter_2) -> (int) {
	if(parameter_1>=parameter_2) {
		return parameter_1;
	}
	return parameter_2;
}

function min(var int parameter_1, var int parameter_2) -> (int) {
	if(parameter_1<=parameter_2) {
		return parameter_1;
	}
	return parameter_2;
}


function add(var int parameter_1, var int parameter_2) -> (int) {
	return parameter_1 + parameter_2;
}


var int result;



/*
println_string("\ntest case 1");
result = max(122, 123);
println_int(result);
debug_assert(result == 123);




println_string("\ntest case 2");
result = min(124, 123);
println_int(result);
debug_assert(result == 123);




println_string("\ntest case 3");
result = add(124, 123);
println_int(result);
debug_assert(result == 247);




println_string("\ntest case 4");
println_int(max(1, 100));
println_int(min(1234, 12345));
println_int(add(100, 1234));

*/

result = add(max(1, 100), min(1234, 12345));


/*
println_int(result);
debug_assert(result == 1334);





println_string("\ntest case 5");

result = add(add(add(add(1,2), 3), 4), 5);
println_int(result);
debug_assert(result == 15);

*/








