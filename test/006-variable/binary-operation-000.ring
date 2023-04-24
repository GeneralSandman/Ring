package main

import {
	fmt;
	debug;
}

@main
function main() {

var int int_value;
int_value = 0;
fmt::println_int(int_value);

int_value = 123456;
fmt::println_int(int_value);

int_value = 123456+234234;
fmt::println_int(int_value);

int_value = 2342*2342;
fmt::println_int(int_value);

int_value = 2342/2342;
fmt::println_int(int_value);

int_value = 234+2342*100;
fmt::println_int(int_value);

int_value = 234+2342/100;
fmt::println_int(int_value);

int_value = 234+2342/100-100/1;
fmt::println_int(int_value);

int_value = 123456+123456*10-100*10+10010;
fmt::println_int(int_value);

int_value = int_value + 10;
fmt::println_int(int_value);

int_value = int_value - 10;
fmt::println_int(int_value);

int_value = int_value * 10;
fmt::println_int(int_value);

int_value = int_value / 10;
fmt::println_int(int_value);

int_value = int_value % 10;
fmt::println_int(int_value);

int_value = int_value % 7;
fmt::println_int(int_value);

int_value = int_value % 5;
fmt::println_int(int_value);

}