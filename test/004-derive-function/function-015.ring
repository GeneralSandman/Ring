
package main

import {
	fmt;
	debug;
}



fn max(var int parameter_1, var int parameter_2) -> (int) {
	if(parameter_1>=parameter_2) {
		return parameter_1;
	}
	return parameter_2;
}

fn min(var int parameter_1, var int parameter_2) -> (int) {
	if(parameter_1<=parameter_2) {
		return parameter_1;
	}
	return parameter_2;
}


fn add(var int parameter_1, var int parameter_2) -> (int) {
	return parameter_1 + parameter_2;
}


@main
fn main() {

	var int result;



	fmt::println_string("\ntest case 1");
	result = max(122, 123);
	fmt::println_int(result);
	debug::assert(result == 123);




	fmt::println_string("\ntest case 2");
	result = min(124, 123);
	fmt::println_int(result);
	debug::assert(result == 123);




	fmt::println_string("\ntest case 3");
	result = add(124, 123);
	fmt::println_int(result);
	debug::assert(result == 247);




	fmt::println_string("\ntest case 4");
	fmt::println_int(max(1, 100));
	fmt::println_int(min(1234, 12345));
	fmt::println_int(add(100, 1234));


	result = add(max(1, 100), min(1234, 12345));
	fmt::println_int(result);
	debug::assert(result == 1334);





	fmt::println_string("\ntest case 5");

	result = add(add(add(add(1,2), 3), 4), 5);
	fmt::println_int(result);
	debug::assert(result == 15);


}