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


var bool bool_value;


println_bool(false);
println_bool(true);
println_string("");

println_bool(not true);
println_bool(not false);
println_string("");


println_bool(not not false);
println_bool(not not true);
println_string("");

println_bool(not not not true);
println_bool(not not not false);
println_string("");

println_bool(not not not not false);
println_bool(not not not not true);
println_string("");


println_string("---------");


bool_value = false;
println_bool(bool_value);
debug_assert(bool_value == false);

bool_value = true;
println_bool(bool_value);
debug_assert(bool_value == true);


println_string("");


bool_value = not true;
println_bool(bool_value);
debug_assert(bool_value == false);

bool_value = not false;
println_bool(bool_value);
debug_assert(bool_value == true);


println_string("");


bool_value = not not false;
println_bool(bool_value);
debug_assert(bool_value == false);

bool_value = not not true;
println_bool(bool_value);
debug_assert(bool_value == true);


println_string("");


bool_value = not not not true;
println_bool(bool_value);
debug_assert(bool_value == false);

bool_value = not not not false;
println_bool(bool_value);
debug_assert(bool_value == true);


println_string("");


bool_value = not not not not false;
println_bool(bool_value);
debug_assert(bool_value == false);

bool_value = not not not not true;
println_bool(bool_value);
debug_assert(bool_value == true);

