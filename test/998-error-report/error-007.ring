//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
}

fn main() {
	fmt::println("main start");
	var int a = return_int();
}

fn return_int() -> (int) {
	fmt::println("return_int");
	return 1;
}