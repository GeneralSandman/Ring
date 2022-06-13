//
// File:    condition-oper-001.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-13
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------


function test_a(){
    println_string("invoke function test_a");
}

function test_b(){
    println_string("invoke function test_b");
}



function return_false() -> (bool) {
    println_string("invoke function return_false");
    return false;
}

function return_true() -> (bool) {
    println_string("invoke function return_true");
    return true;
}


println_string("\ntest case 1");
false ? test_a() : test_b();
true ? test_a() : test_b();



println_string("\ntest case 2");
return_false() ? test_a() : test_b();
return_true() ? test_a() : test_b();




println_string("\ntest case 3");
var bool result;

result = return_false() ? return_true() : return_false();
println_bool(result);
debug_assert(result == false);

result = return_true() ? return_true() : return_false();
println_bool(result);
debug_assert(result == true);


println_string("\ntest case 4");


debug_assert(false ? 1 : 2);
debug_assert(true ? 1 : 2);
