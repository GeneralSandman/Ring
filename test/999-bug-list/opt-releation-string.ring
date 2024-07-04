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

	fmt::println("test case 1------------");

	local_bool_value_0 = "1.0" == "1.0";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = "2.0" == "1.0";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);

	local_bool_value_0 = "1.0" == "2.0";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);

	local_bool_value_0 = "2.0" == "2.0";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);



	
	fmt::println("\ntest case 2------------");

	local_bool_value_0 = "1.0" != "1.0";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);

	local_bool_value_0 = "2.0" != "1.0";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = "1.0" != "2.0";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = "2.0" != "2.0";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);



	fmt::println("\ntest case 3------------");

	local_bool_value_0 = "12345" > "12345";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);

	local_bool_value_0 = "123456" > "12345";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = "123456" > "123455";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = "123456" > "123457";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);


	fmt::println("\ntest case 4------------");

	local_bool_value_0 = "12345" >= "12345";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = "123456" >= "12345";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = "123456" >= "123455";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == true);

	local_bool_value_0 = "123456" >= "123457";
	fmt::println(local_bool_value_0);
	debug::debug_assert(local_bool_value_0 == false);
}