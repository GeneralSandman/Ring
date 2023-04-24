package main

import {
	fmt;
	debug;
}


function a() {
	fmt::println_string("function a");
}

function b() {
	fmt::println_string("function b");
}

@main
function main() {

true ? a() : b();

false ? a() : b();

}
