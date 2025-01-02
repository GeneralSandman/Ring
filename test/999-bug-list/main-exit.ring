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
	var bool bool_value = return_bool();
}

fn main(var string[] args) {
	os::exit(-1);
}

fn return_bool() -> (bool) {
	fmt::println("return_bool");
	return true;
}