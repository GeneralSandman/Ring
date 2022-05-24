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


function func_use_local_variable_hidden_global() {
    var int int_value_global;
    int_value_global = 234;
    println_int(int_value_global);
    println_int(int_value_global);
    println_int(int_value_global);
    println_int(int_value_global);
    debug_assert(int_value_global == 234);
    debug_assert(int_value_global == 234);
    debug_assert(int_value_global == 234);
    debug_assert(int_value_global == 234);
}


// --------------
int_value_global = 1;
println_int(int_value_global);
debug_assert(int_value_global == 1);
debug_assert(int_value_global == 1);
debug_assert(int_value_global == 1);
debug_assert(int_value_global == 1);
println_string("");

func_use_local_variable_hidden_global();
println_string("");

println_int(int_value_global);
debug_assert(int_value_global == 1);
debug_assert(int_value_global == 1);
debug_assert(int_value_global == 1);
debug_assert(int_value_global == 1);
println_string("");

