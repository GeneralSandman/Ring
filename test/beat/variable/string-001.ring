//
// File:    string-001.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-17
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

string_value = "12" + "23";
println_string(string_value);
println_string("12" + "23");


string_value = "1234567890" + "0987654321";
println_string(string_value);
println_string("1234567890" + "0987654321");


/* string_value = "1" + "2" + "3" + "4"; */
/* println_string(string_value); */



/* string_value = "1" + <string>(1+2+3); */
/* println_string(string_value); */

/* string_value = "1" + <string>int_value; */
/* println_string(string_value); */

/* string_value = "1" + <string>(int_value + int_value); */
/* println_string(string_value); */

/* string_value = "1" + "1"; */
/* println_string(string_value); */
