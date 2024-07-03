package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 bool 类型
@main
function main() {

	pass_1_int(0);
	pass_1_int(1);

	pass_2_int(0, 0);
	pass_2_int(1, 1);

	pass_3_int(0, 0, 0);
	pass_3_int(1, 1, 1);

	pass_4_int(0, 0, 0, 0);
	pass_4_int(1, 1, 1, 1);

	pass_5_int(0, 0, 0, 0, 0);
	pass_5_int(1, 1, 1, 1, 1);

	pass_6_int(0, 0, 0, 0, 0, 0);
	pass_6_int(1, 1, 1, 1, 1, 1);

	pass_7_int(0, 0, 0, 0, 0, 0, 0);
	pass_7_int(1, 1, 1, 1, 1, 1, 1);

	pass_8_int(0, 0, 0, 0, 0, 0, 0, 0);
	pass_8_int(1, 1, 1, 1, 1, 1, 1, 1);
}





function pass_1_int(var int a) {
	fmt::println(a);
}

function pass_2_int(var int a, var int b) {
	fmt::println(a, b);
}

function pass_3_int(var int a, var int b, var int c) {
    fmt::println(a, b, c);
}

function pass_4_int(var int a, var int b, var int c, var int d) {
    fmt::println(a, b, c, d);
}

function pass_5_int(var int a, var int b, var int c, var int d, var int e) {
    fmt::println(a, b, c, d, e);
}

function pass_6_int(var int a, var int b, var int c, var int d, var int e, var int f) {
    fmt::println(a, b, c, d, e, f);
}

function pass_7_int(var int a, var int b, var int c, var int d, var int e, var int f, var int g) {
    fmt::println(a, b, c, d, e, f, g);
}

function pass_8_int(var int a, var int b, var int c, var int d, var int e, var int f, var int g, var int h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

