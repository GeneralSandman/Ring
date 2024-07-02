package main

import {
	fmt;
	debug;
}


// TestDetail: 测试函数返回 bool 类型
@main
function main() {

	pass_1_bool(false);
	pass_1_bool(true);

	pass_2_bool(false, false);
	pass_2_bool(true,  true);

	pass_3_bool(false, false, false);
	pass_3_bool(true,  true,  true);

	pass_4_bool(false, false, false, false);
	pass_4_bool(true,  true,  true,  true);

	pass_5_bool(false, false, false, false, false);
	pass_5_bool(true,  true,  true,  true,  true);

	pass_6_bool(false, false, false, false, false, false);
	pass_6_bool(true,  true,  true,  true,  true,  true);

	pass_7_bool(false, false, false, false, false, false, false);
	pass_7_bool(true,  true,  true,  true,  true,  true,  true);

	pass_8_bool(false, false, false, false, false, false, false, false);
	pass_8_bool(true,  true,  true,  true,  true,  true,  true,  true);
}





function pass_1_bool(var bool a) {
	fmt::println(a);
}

function pass_2_bool(var bool a, var bool b) {
	fmt::println(a, b);
}

function pass_3_bool(var bool a, var bool b, var bool c) {
    fmt::println(a, b, c);
}

function pass_4_bool(var bool a, var bool b, var bool c, var bool d) {
    fmt::println(a, b, c, d);
}

function pass_5_bool(var bool a, var bool b, var bool c, var bool d, var bool e) {
    fmt::println(a, b, c, d, e);
}

function pass_6_bool(var bool a, var bool b, var bool c, var bool d, var bool e, var bool f) {
    fmt::println(a, b, c, d, e, f);
}

function pass_7_bool(var bool a, var bool b, var bool c, var bool d, var bool e, var bool f, var bool g) {
    fmt::println(a, b, c, d, e, f, g);
}

function pass_8_bool(var bool a, var bool b, var bool c, var bool d, var bool e, var bool f, var bool g, var bool h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

