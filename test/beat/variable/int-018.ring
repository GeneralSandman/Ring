//
// File:    int-018.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-16
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);



var bool bool_value;

bool_value = false;
println_bool(bool_value);

bool_value = true;
println_bool(bool_value);

bool_value = not true;
println_bool(bool_value);

bool_value = not false;
println_bool(bool_value);


bool_value = not not false;
println_bool(bool_value);

bool_value = not not true;
println_bool(bool_value);


bool_value = not not not true;
println_bool(bool_value);

bool_value = not not not false;
println_bool(bool_value);



bool_value = not not not not false;
println_bool(bool_value);

bool_value = not not not not true;
println_bool(bool_value);



