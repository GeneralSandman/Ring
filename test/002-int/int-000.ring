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

fn main() {

	fmt::println_int(0);
	fmt::println_int(-0);
	
	fmt::println_int(1);
	fmt::println_int(-1);
	
	fmt::println_int(255);
	fmt::println_int(-255);
	
	fmt::println_int(256);
	fmt::println_int(-256);
	
	fmt::println_int(65535);
	fmt::println_int(-65535);
	
	fmt::println_int(65536);
	fmt::println_int(-65536);
	
	fmt::println_int(65537);
	fmt::println_int(-65537);
	
	fmt::println_int(2147483647);
	fmt::println_int(-2147483647);
	
	fmt::println_int(2147483648);
	fmt::println_int(-2147483648);
	
	fmt::println_string("--------");
	fmt::println_string("");
	
	var int int_value_1 = 0;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 0);
	
	
	fmt::println_string("");


	int_value_1 = 1;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 1);
	

	fmt::println_string("");

	
	int_value_1 = 2;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 2);
	
	
	fmt::println_string("");
	
	
	int_value_1 = 255;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 255);
	
	
	fmt::println_string("");
	
	
	int_value_1 = 256;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 256);
	
	
	fmt::println_string("");
	
	
	int_value_1 = 65535;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 65535);
	
	
	fmt::println_string("");
	
	
	int_value_1 = 65536;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 65536);
	
	
	fmt::println_string("");
	
	
	int_value_1 = 2147483647;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 2147483647);
	
	
	fmt::println_string("");
	
	
	int_value_1 = 2147483648;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == -2147483648);
	
	
	fmt::println_string("");
	
	
	int_value_1 = -0;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == 0);
	
	
	fmt::println_string("");
	
	
	int_value_1 = -1;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == -1);
	
	
	fmt::println_string("");
	
	
	int_value_1 = -255;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == -255);
	
	
	fmt::println_string("");
	
	
	int_value_1 = -256;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == -256);
	
	
	fmt::println_string("");
	
	
	int_value_1 = -65535;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == -65535);
	
	
	fmt::println_string("");
	
	
	int_value_1 = -65536;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == -65536);
	
	
	fmt::println_string("");
	
	
	int_value_1 = -2147483647;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == -2147483647);
	
	
	fmt::println_string("");
	
	
	int_value_1 = -2147483648;
	fmt::println_int(int_value_1);
	debug::assert(int_value_1 == -2147483648);
	
	
	fmt::println_string("");



	/*
	/*
	
	
	var int int_value_2 = 1;
	print("int_value_2(1)=", int_value_2, "\n");
	int_value_2 = -int_value_2;
	print("int_value_2(-1)=", int_value_2, "\n");
	
	
	print("\n\n");
	
	var int int_value_3 = 2147483648;
	print("int_value_3(2147483648)=", int_value_3, "\n");
	int_value_3 = -int_value_3;
	print("int_value_3(-2147483648)=", int_value_3, "\n");
	
	print("\n\n");
	
	
	var int int_value_4 = -2147483648;
	print("int_value_4(-2147483648)=", int_value_4, "\n");
	int_value_4 = -int_value_4;
	print("int_value_4(-2147483648)=", int_value_4, "\n");
	
	
	print("\n\n");
	
	var int int_value_5 = 0-2147483648;
	print("int_value_5(0-2147483648)=", int_value_5, "\n");
	int_value_5 = -int_value_5;
	print("int_value_5(-2147483648)=", int_value_5, "\n");
	
	*/
	
}
