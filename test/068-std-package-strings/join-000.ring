package main

import {
	fmt;
	strings;
}

fn main() {
	
	fmt::println(strings::join(string[]{}, ","));

	fmt::println(strings::join(string[]{"a"}, ","));

	fmt::println(strings::join(string[]{"a", "b"}, ""));
	fmt::println(strings::join(string[]{"a", "b"}, "="));
}