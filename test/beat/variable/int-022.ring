//
// File:    int-022.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-16
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function exit(var int int_value);


var int int_value;
var int sum;


// -----------
println_string("[Test Case 1]");

sum = 0;
for(int_value = 1; int_value <= 100; int_value = int_value + 1) {
    sum = sum + int_value;
}

println_int(sum);


// -----------
println_string("[Test Case 2]");

sum = 0;
for(int_value = 1; int_value <= 100; int_value++) {
    sum += int_value;
}

println_int(sum);


// -----------
println_string("[Test Case 3]");

sum = 0;
int_value = 1;
for(; int_value <= 100; int_value+=1) {
    sum += int_value;
}

println_int(sum);


// -----------
println_string("[Test Case 4]");

sum = 0;
int_value = 1;
for(; int_value <= 100;) {
    sum += int_value;
    int_value += 1;
}


println_int(sum);




exit(0);


// -----------
println_string("----------");

sum = 0;
for(int_value = 1; int_value <= 200; int_value = int_value + 1) {
    sum = sum + int_value;
}

println_int(sum);


// ------------
println_string("----------");

sum = 1;
for(int_value = 1; int_value <= 10; int_value = int_value + 1) {
    sum = sum * int_value;
}

println_int(sum);
