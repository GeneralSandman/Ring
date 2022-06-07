//
// File:    print_heart.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-06
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------

var double x;
var double y;
var double a;


for (y = 1.5; y > -1.5; y -= 0.1) {
	for (x = -1.5; x < 1.5; x += 0.05) {
		a = x * x + y * y - 1;
		if(a * a * a - x * x * y * y * y <= 0.0){
			println_string("*");
		} else {
			println_string(" ");
		}
	}
	println_string("\n");
}