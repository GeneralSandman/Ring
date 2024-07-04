package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递double类型参数
// TestDetail: 分别传递1-8个double类型参数
@main
function main() {

	pass_1_double(0.0);
	pass_1_double(1.0);

	pass_2_double(0.0, 0.0);
	pass_2_double(1.0, 1.0);

	pass_3_double(0.0, 0.0, 0.0);
	pass_3_double(1.0, 1.0, 1.0);

	pass_4_double(0.0, 0.0, 0.0, 0.0);
	pass_4_double(1.0, 1.0, 1.0, 1.0);

	pass_5_double(0.0, 0.0, 0.0, 0.0, 0.0);
	pass_5_double(1.0, 1.0, 1.0, 1.0, 1.0);

	pass_6_double(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	pass_6_double(1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	pass_7_double(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	pass_7_double(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);

	pass_8_double(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	pass_8_double(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
}





function pass_1_double(var double a) {
	fmt::println(a);
}

function pass_2_double(var double a, var double b) {
	fmt::println(a, b);
}

function pass_3_double(var double a, var double b, var double c) {
    fmt::println(a, b, c);
}

function pass_4_double(var double a, var double b, var double c, var double d) {
    fmt::println(a, b, c, d);
}

function pass_5_double(var double a, var double b, var double c, var double d, var double e) {
    fmt::println(a, b, c, d, e);
}

function pass_6_double(var double a, var double b, var double c, var double d, var double e, var double f) {
    fmt::println(a, b, c, d, e, f);
}

function pass_7_double(var double a, var double b, var double c, var double d, var double e, var double f, var double g) {
    fmt::println(a, b, c, d, e, f, g);
}

function pass_8_double(var double a, var double b, var double c, var double d, var double e, var double f, var double g, var double h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

