package main

import {
	fmt;
	strings;
}

@main
function main() {
	
	fmt::println(strings::join(string[]{"a", "b"}, "="));
}
