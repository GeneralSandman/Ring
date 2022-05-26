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


var int x;
var int y;
var int z;

var int num;

// -------------------
num = 0;
for(x=0; x<3; x=x+1) {
	for(y=0; y<3; y=y+1) {
		for(z=0; z<3; z=z+1) {
			if(x == 2 and y == 2 and z == 2) {
				println_int(x);
				println_int(y);
				println_int(z);
				println_string("");
				break 3;
			}
			num = num + 1;
		}
	}
}

println_string("finish for====");
println_int(num);
debug_assert(num == 26);
debug_assert(x == 2);
debug_assert(y == 2);
debug_assert(z == 2);
println_string("finish for====");


println_string("");
println_string("");

num = 0;
for(x=0; x<11; x=x+1) {
	for(y=0; y<120; y=y+1) {
		for(z=0; z<13; z=z+1) {
			num+=1;
			if(num > 100){
				break 3;
			}
		}
	}
}

println_string("finish for====");
println_int(num);
debug_assert(num == 101);
debug_assert(x == 0);
debug_assert(y == 7);
debug_assert(z == 9);
println_string("finish for====");

