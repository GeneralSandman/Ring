package main

import {
    fmt;
    debug;
    runtime;
	reflect;
}


fn main() {
	var int a;
	var int b;

	b++;

	a = b++; // 这样是不被允许的，因为表达式过于复杂，降低可读性
}