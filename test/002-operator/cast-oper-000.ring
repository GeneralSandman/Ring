//
// File:    cast-oper-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-15
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);
function print(var any value) -> (int);
function println(var any value) -> (int);
function printf(var string format, var any value)   -> (int);
function printfln(var string format, var any value) -> (int);

// -----------------------------


var bool   bool_value;
var int    int_value;
var double double_value;
var string string_value;



// double_value = true; // FIXME: check is strictly in semantic_check
// println(double_value);



println_string("\ntest case 1");
bool_value = <bool>true;
println_bool(bool_value);


bool_value = true;
println_bool(bool_value);


bool_value = <bool>1;
println_bool(bool_value);


bool_value = <bool>-1;
println_bool(bool_value);



bool_value = <bool>123.334;
println_bool(bool_value);


bool_value = <bool>-1234.22;
println_bool(bool_value);


bool_value = <bool>0;
println_bool(bool_value);


bool_value = <bool>0.0;
println_bool(bool_value);





println_string("\ntest case 1");
int_value = <int>true;
println_int(int_value);

int_value = <int>223;
println_int(int_value);

int_value = 223;
println_int(int_value);

int_value = <int>1234.234;
println_int(int_value);






println_string("\ntest case 2");
double_value = <double>true;
println(double_value);

double_value = <double>123;
println(double_value);

double_value = <double>123.123;
println(double_value);

double_value = <double>111+222; // FIXME: bug
println(double_value);

double_value = 123.12333;
println(double_value);





