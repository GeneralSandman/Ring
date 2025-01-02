package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递double类型参数
// TestDetail: 分别传递1-8个double类型参数
fn main() {

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





fn pass_1_double(var double a) {
	fmt::println(a);
}

fn pass_2_double(var double a, var double b) {
	fmt::println(a, b);
}

fn pass_3_double(var double a, var double b, var double c) {
    fmt::println(a, b, c);
}

fn pass_4_double(var double a, var double b, var double c, var double d) {
    fmt::println(a, b, c, d);
}

fn pass_5_double(var double a, var double b, var double c, var double d, var double e) {
    fmt::println(a, b, c, d, e);
}

fn pass_6_double(var double a, var double b, var double c, var double d, var double e, var double f) {
    fmt::println(a, b, c, d, e, f);
}

fn pass_7_double(var double a, var double b, var double c, var double d, var double e, var double f, var double g) {
    fmt::println(a, b, c, d, e, f, g);
}

fn pass_8_double(var double a, var double b, var double c, var double d, var double e, var double f, var double g, var double h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

