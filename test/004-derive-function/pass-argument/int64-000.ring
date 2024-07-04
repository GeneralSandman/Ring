package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递int64类型参数
// TestDetail: 分别传递1-8个int64类型参数
@main
function main() {

	pass_1_int64(0L);
	pass_1_int64(1L);

	pass_2_int64(0L, 0L);
	pass_2_int64(1L, 1L);

	pass_3_int64(0L, 0L, 0L);
	pass_3_int64(1L, 1L, 1L);

	pass_4_int64(0L, 0L, 0L, 0L);
	pass_4_int64(1L, 1L, 1L, 1L);

	pass_5_int64(0L, 0L, 0L, 0L, 0L);
	pass_5_int64(1L, 1L, 1L, 1L, 1L);

	pass_6_int64(0L, 0L, 0L, 0L, 0L, 0L);
	pass_6_int64(1L, 1L, 1L, 1L, 1L, 1L);

	pass_7_int64(0L, 0L, 0L, 0L, 0L, 0L, 0L);
	pass_7_int64(1L, 1L, 1L, 1L, 1L, 1L, 1L);

	pass_8_int64(0L, 0L, 0L, 0L, 0L, 0L, 0L, 0L);
	pass_8_int64(1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L);
}





function pass_1_int64(var int64 a) {
	fmt::println(a);
}

function pass_2_int64(var int64 a, var int64 b) {
	fmt::println(a, b);
}

function pass_3_int64(var int64 a, var int64 b, var int64 c) {
    fmt::println(a, b, c);
}

function pass_4_int64(var int64 a, var int64 b, var int64 c, var int64 d) {
    fmt::println(a, b, c, d);
}

function pass_5_int64(var int64 a, var int64 b, var int64 c, var int64 d, var int64 e) {
    fmt::println(a, b, c, d, e);
}

function pass_6_int64(var int64 a, var int64 b, var int64 c, var int64 d, var int64 e, var int64 f) {
    fmt::println(a, b, c, d, e, f);
}

function pass_7_int64(var int64 a, var int64 b, var int64 c, var int64 d, var int64 e, var int64 f, var int64 g) {
    fmt::println(a, b, c, d, e, f, g);
}

function pass_8_int64(var int64 a, var int64 b, var int64 c, var int64 d, var int64 e, var int64 f, var int64 g, var int64 h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

