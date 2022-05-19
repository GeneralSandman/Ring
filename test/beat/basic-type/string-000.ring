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

println_string("1");
println_string("2");
println_string("3");
println_string("4");
println_string("5");
println_string("hello world!");
println_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
println_string("abcdefghijklmnopqrstuvwxyz");
println_string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");


println_string("");
println_string("-----------");


var string string_value;

string_value = "1";
println_string(string_value);

string_value = "2";
println_string(string_value);

string_value = "3";
println_string(string_value);

string_value = "4";
println_string(string_value);

string_value = "5";
println_string(string_value);

string_value = "hello world!";
println_string(string_value);

string_value = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
println_string(string_value);

string_value = "abcdefghijklmnopqrstuvwxyz";
println_string(string_value);

string_value = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
println_string(string_value);


