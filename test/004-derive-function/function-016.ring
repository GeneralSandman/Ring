
package main

import {
	fmt;
	debug;
}






fn add_one(var int parameter_1) -> (int) {
	return parameter_1 + 1;
}


fn add(var int parameter_1, var int parameter_2) -> (int) {
	return parameter_1 + parameter_2;
}




fn main() {


	var int int_value = 0;


	fmt::println_string("\ntest case 1");
	fmt::println_int(add_one(1));
	fmt::println_bool(2 == add_one(1));
	debug::assert(2 == add_one(1));



	int_value = add_one(add_one(add_one(add_one(add_one(-1)))));
	fmt::println_int(int_value);
	debug::assert(int_value == 4);



	int_value = add_one(add_one(add_one(add_one(add_one(0)))));
	fmt::println_int(int_value);
	debug::assert(int_value == 5);

	int_value = add_one(add_one(add_one(add_one(add_one(1)))));
	fmt::println_int(int_value);
	debug::assert(int_value == 6);




	fmt::println_string("\ntest case 2");
	int_value = add(1, add(2, 3));
	fmt::println_int(int_value);
	debug::assert(int_value == 6);



	int_value = add(1, add(2, add(3, add(4, add(5, 6)))));
	fmt::println_int(int_value);
	debug::assert(int_value == 21);

}