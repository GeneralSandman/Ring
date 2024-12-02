//
// File:    int-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//

package main

import {
	fmt;
	debug;
}

@main
function main() {

	var bool bool_value;


	fmt::println_bool(false);
	fmt::println_bool(true);
	fmt::println_string("");

	fmt::println_bool(not true);
	fmt::println_bool(not false);
	fmt::println_string("");


	fmt::println_bool(not not false);
	fmt::println_bool(not not true);
	fmt::println_string("");

	fmt::println_bool(not not not true);
	fmt::println_bool(not not not false);
	fmt::println_string("");

	fmt::println_bool(not not not not false);
	fmt::println_bool(not not not not true);
	fmt::println_string("");


	fmt::println_string("---------");


	bool_value = false;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == false);

	bool_value = true;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == true);


	fmt::println_string("");


	bool_value = not true;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == false);

	bool_value = not false;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == true);


	fmt::println_string("");


	bool_value = not not false;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == false);

	bool_value = not not true;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == true);


	fmt::println_string("");


	bool_value = not not not true;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == false);

	bool_value = not not not false;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == true);


	fmt::println_string("");


	bool_value = not not not not false;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == false);

	bool_value = not not not not true;
	fmt::println_bool(bool_value);
	debug::assert(bool_value == true);

}