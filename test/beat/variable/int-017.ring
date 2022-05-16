//
// File:    int-017.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-12
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);


var int int_value;
var int result;



// -------------------
int_value = 1;

int_value++;
println_int(int_value);

++int_value;
println_int(int_value);


result = int_value++;
println_int(result);

/*
println_int(int_value);

int_value++;
println_int(int_value);

++int_value;
println_int(int_value);

int_value--;
println_int(int_value);

--int_value;
println_int(int_value);

*/

// -------------

/*

var int result;
result = 0;
int_value = 1;

println_int(int_value);
println_int(result);

result = int_value++;
println_int(int_value);
println_int(result);

*/
