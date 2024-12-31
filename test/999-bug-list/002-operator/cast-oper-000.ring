
package main

import {
	fmt;
	debug;
}

@main
fn main() {


var bool   bool_value;
var int    int_value;
var double double_value;
var string string_value;



// double_value = true; // FIXME: check is strictly in semantic_check
// println(double_value);



fmt::println_string("\ntest case 1");
bool_value = <bool>true;
fmt::println_bool(bool_value);


bool_value = true;
fmt::println_bool(bool_value);


bool_value = <bool>1;
fmt::println_bool(bool_value);


bool_value = <bool>-1;
fmt::println_bool(bool_value);



bool_value = <bool>123.334;
fmt::println_bool(bool_value);


bool_value = <bool>-1234.22;
fmt::println_bool(bool_value);


bool_value = <bool>0;
fmt::println_bool(bool_value);


bool_value = <bool>0.0;
fmt::println_bool(bool_value);





fmt::println_string("\ntest case 1");
int_value = <int>true;
fmt::println_int(int_value);

int_value = <int>223;
fmt::println_int(int_value);

int_value = 223;
fmt::println_int(int_value);

int_value = <int>1234.234;
fmt::println_int(int_value);






fmt::println_string("\ntest case 2");
double_value = <double>true;
fmt::println_double(double_value);

double_value = <double>123;
fmt::println_double(double_value);

double_value = <double>123.123;
fmt::println_double(double_value);

double_value = <double>111+222; // FIXME: bug
fmt::println_double(double_value);

double_value = 123.12333;
fmt::println_double(double_value);





}