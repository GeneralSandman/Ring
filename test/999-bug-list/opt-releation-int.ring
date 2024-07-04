//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

// minus 符号
@main
function main() {
	var bool local_bool_value_0;

	local_bool_value_0 = 1 == 1;
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = 2 == 1;
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);

	local_bool_value_0 = 1 == 2;
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);

	local_bool_value_0 = 2 == 2;
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);


	

	local_bool_value_0 = 1 != 1;
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);

	local_bool_value_0 = 2 != 1;
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = 1 != 2;
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = 2 != 2;
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);



}