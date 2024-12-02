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

	local_bool_value_0 = false == false;
	fmt::println(local_bool_value_0);
	debug::assert(local_bool_value_0 == true);

	local_bool_value_0 = true == false;
	fmt::println(local_bool_value_0);
	debug::assert(local_bool_value_0 == false);

	local_bool_value_0 = false == true;
	fmt::println(local_bool_value_0);
	debug::assert(local_bool_value_0 == false);

	local_bool_value_0 = true == true;
	fmt::println(local_bool_value_0);
	debug::assert(local_bool_value_0 == true);


	

	local_bool_value_0 = false != false;
	fmt::println(local_bool_value_0);
	debug::assert(local_bool_value_0 == false);

	local_bool_value_0 = true != false;
	fmt::println(local_bool_value_0);
	debug::assert(local_bool_value_0 == true);

	local_bool_value_0 = false != true;
	fmt::println(local_bool_value_0);
	debug::assert(local_bool_value_0 == true);

	local_bool_value_0 = true != true;
	fmt::println(local_bool_value_0);
	debug::assert(local_bool_value_0 == false);



}