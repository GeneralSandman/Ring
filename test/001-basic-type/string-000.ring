//
// File:    string-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

@main
function main() {

	fmt::println_string("1");
	fmt::println_string("2");
	fmt::println_string("3");
	fmt::println_string("4");
	fmt::println_string("5");
	fmt::println_string("hello world!");
	fmt::println_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	fmt::println_string("abcdefghijklmnopqrstuvwxyz");
	fmt::println_string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");


	fmt::println_string("");
	fmt::println_string("-----------");


	var string string_value;

	string_value = "1";
	fmt::println_string(string_value);

	string_value = "2";
	fmt::println_string(string_value);

	string_value = "3";
	fmt::println_string(string_value);

	string_value = "4";
	fmt::println_string(string_value);

	string_value = "5";
	fmt::println_string(string_value);

	string_value = "hello world!";
	fmt::println_string(string_value);

	string_value = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	fmt::println_string(string_value);

	string_value = "abcdefghijklmnopqrstuvwxyz";
	fmt::println_string(string_value);

	string_value = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	fmt::println_string(string_value);


}