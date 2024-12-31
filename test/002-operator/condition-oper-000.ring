
package main

import {
	fmt;
	debug;
}

@main
fn main() {


	var bool bool_value;
	var int int_value;


	fmt::println_string("\ntest case 1");
	bool_value = false;
	fmt::println_string(bool_value ? "bool_value is true" : "bool_value is false");
	bool_value = true;
	fmt::println_string(bool_value ? "bool_value is true" : "bool_value is false");


	fmt::println_string("\ntest case 2");
	bool_value = false;
	fmt::println_int(bool_value ? 100 : -100);
	bool_value = true;
	fmt::println_int(bool_value ? 100 : -100);


	fmt::println_string("\ntest case 3");
	bool_value = false;
	fmt::println_double(bool_value ? 100123.0 : 100.123);
	bool_value = true;
	fmt::println_double(bool_value ? 100123.0 : 100.123);




	// -----------------------



	fmt::println_string("\ntest case 1");
	fmt::println_string(false ? "bool_value is true" : "bool_value is false");
	fmt::println_string(true ? "bool_value is true" : "bool_value is false");


	fmt::println_string("\ntest case 2");
	fmt::println_int(false ? 100 : -100);
	fmt::println_int(true ? 100 : -100);


	fmt::println_string("\ntest case 3");
	fmt::println_double(false ? 100.123 : 100123.0);
	fmt::println_double(true ? 100.123 : 100123.0);
	
}