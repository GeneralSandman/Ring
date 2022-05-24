//
// File:    function-003.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-23
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------

var int int_value_global;


function func_use_local_variable() {
    var int int_value_local;
    int_value_local = 123;
    println_int(int_value_local);
    println_int(int_value_local);
    println_int(int_value_local);
    println_int(int_value_local);
    debug_assert(int_value_local == 123);
    debug_assert(int_value_local == 123);
    debug_assert(int_value_local == 123);
    debug_assert(int_value_local == 123);
}

// --------------

int_value_global = 2;
println_int(int_value_global);
println_int(int_value_global);
println_int(int_value_global);
println_int(int_value_global);
debug_assert(int_value_global == 2);
debug_assert(int_value_global == 2);
debug_assert(int_value_global == 2);
debug_assert(int_value_global == 2);
println_string("");

func_use_local_variable();
println_string("");

println_int(int_value_global);
println_int(int_value_global);
println_int(int_value_global);
println_int(int_value_global);
debug_assert(int_value_global == 2);
debug_assert(int_value_global == 2);
debug_assert(int_value_global == 2);
debug_assert(int_value_global == 2);
println_string("");


