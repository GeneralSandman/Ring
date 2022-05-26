//
// File:    dofor-005.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-26
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------

var int int_value;
var int count;


println_string("[test case 1]");

do(int_value = 2){
    println_int(int_value);
}for(int_value < 10; ++int_value);



println_string("finish for====");
println_int(int_value);
debug_assert(int_value == 10);
println_string("finish for====");




// ------------------

println_string("\n[test case 2]");

count = 0;

do(int_value = 0) {
    if(int_value > 5) {
        continue;
    }
    count++;
    println_int(int_value);
}for(int_value < 10; ++int_value);



println_string("finish for====");
println_int(int_value);
println_bool(int_value == 10);
debug_assert(int_value == 10);

println_int(count);
debug_assert(count == 6);

println_string("finish for====");



// ------------------

println_string("\n[test case 3]");

count = 0;

do(int_value = 0) {
    if(int_value % 2 == 0) {
        println_int(int_value);
    } else {
        continue;
    }
    count++;
}for(int_value < 20; ++int_value);



println_string("finish for====");
println_int(int_value);
println_bool(int_value == 20);
debug_assert(int_value == 20);

println_int(count);
debug_assert(count == 11);

println_string("finish for====");



// ------------------

println_string("\n[test case 4]");

count = 0;

do(int_value = 0) {
    if(int_value % 5 == 0) {
    } else {
        continue;
    }
    count++;
}for(int_value < 100; ++int_value);



println_string("finish for====");
println_int(int_value);
println_bool(int_value == 100);
debug_assert(int_value == 100);

println_int(count);
debug_assert(count == 21);

println_string("finish for====");



// ------------------

println_string("\n[test case 5]");

count = 0;

do(int_value = 0) {
    if(int_value % 5 == 0) {
        count = ++count;
    } else {
        continue;
    }
}for(int_value < 100; ++int_value);



println_string("finish for====");
println_int(int_value);
println_bool(int_value == 100);
debug_assert(int_value == 100);

println_int(count);
debug_assert(count == 21);

println_string("finish for====");



