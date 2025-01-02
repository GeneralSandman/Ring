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

global {

	var bool global_bool_value_0 = true;
	var bool global_bool_value_1 = false;
	var bool global_bool_value_2, global_bool_value_3 = true, false;
	var bool global_bool_value_4, global_bool_value_5, global_bool_value_6 = true, false, true;
	var bool global_bool_value_7, global_bool_value_8, global_bool_value_9, global_bool_value_10 = false, true, false, true;
	var bool global_bool_value_11, global_bool_value_12, global_bool_value_13, global_bool_value_14, global_bool_value_15 = false, true, false, true, false;

}

fn main(var string[] args) {
	
	fmt::println(global_bool_value_0);
	fmt::println(global_bool_value_1);
	fmt::println(global_bool_value_2);
	fmt::println(global_bool_value_3);
	fmt::println(global_bool_value_4);
	fmt::println(global_bool_value_5);
	fmt::println(global_bool_value_6);
	fmt::println(global_bool_value_7);
	fmt::println(global_bool_value_8);
	fmt::println(global_bool_value_9);
	fmt::println(global_bool_value_10);
	fmt::println(global_bool_value_11);
	fmt::println(global_bool_value_12);
	fmt::println(global_bool_value_13);
	fmt::println(global_bool_value_14);
	fmt::println(global_bool_value_15);


	debug::assert(global_bool_value_0  == true);
	debug::assert(global_bool_value_1  == false);
	debug::assert(global_bool_value_2  == true);
	debug::assert(global_bool_value_3  == false);
	debug::assert(global_bool_value_4  == true);
	debug::assert(global_bool_value_5  == false);
	debug::assert(global_bool_value_6  == true);
	debug::assert(global_bool_value_7  == false);
	debug::assert(global_bool_value_8  == true);
	debug::assert(global_bool_value_9  == false);
	debug::assert(global_bool_value_10 == true);	
	debug::assert(global_bool_value_11 == false);
	debug::assert(global_bool_value_12 == true);
	debug::assert(global_bool_value_13 == false);
	debug::assert(global_bool_value_14 == true);
	debug::assert(global_bool_value_15 == false);


}