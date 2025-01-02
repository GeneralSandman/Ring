package main

import {
	fmt;
	debug;
}


fn a() {
	fmt::println_string("function a");
}

fn b() {
	fmt::println_string("function b");
}

fn main() {

	true ? a() : b();
	
	false ? a() : b();

}
