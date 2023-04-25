
package main

import {
	fmt;
	debug;
}

@main
function main() {


var bool bool_value;
var int  int_value;
var double double_value;
var string string_value;

// -----------------------
fmt::println_string("\ntest case 1");
print(true);
print("\n");

println(true);



print(123);
print("\n");

println(123);



print(456.123456);
print("\n");
println(456.123456);



print("hello world");
print("\n");
println("hello world");




// -----------------------
fmt::println_string("\ntest case 2");

print(true, 123, 456.123456, "hello world");
print("\n");

println(true, 123, 456.123456, "hello world");



// -----------------------
fmt::println_string("\ntest case 3");
print(true, false, true, false, true, false, "\n");
println(true, false, true, false, true, false);


// -----------------------
fmt::println_string("\ntest case 4");
print(1, 2, 3, 4, 5, 6, 7, "\n");
println(1, 2, 3, 4, 5, 6, 7);



// -----------------------
fmt::println_string("\ntest case 5");
print("1", "2", "3", "4", "5", "6", "7", "\n");
println("1", "2", "3", "4", "5", "6", "7");




// -----------------------
fmt::println_string("\ntest case 6");


print(true, "\n");
println(true);
bool_value = true;
print(bool_value, "\n");
println(bool_value);


print(123, "\n");
println(123);
int_value = 123;
print(int_value, "\n");
println(int_value);

print(456.123456, "\n");
println(456.123456);
double_value = 456.123456;
print(double_value, "\n");
println(double_value);

print("hello world", "\n");
println("hello world");
string_value = "hello world";
print(string_value, "\n");
println(string_value);




// -----------------------
fmt::println_string("\ntest case 7");

print(true, 123, 456.123456, "hello world", "\n");
println(true, 123, 456.123456, "hello world");

print(bool_value, int_value, double_value, string_value, "\n");
println(bool_value, int_value, double_value, string_value);



}