//
// File:    string-003.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-18
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function exit(var int int_value);


var bool bool_value;
var int int_value;
var double double_value;
var string string_value;

bool_value = false;
string_value = <string>bool_value;
println_string(string_value);

bool_value = true;
string_value = <string>bool_value;
println_string(string_value);
