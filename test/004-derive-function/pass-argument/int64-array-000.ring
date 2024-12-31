package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递int64数组类型参数
// TestDetail: 分别传递1-8个int64数组类型参数
@main
fn main() {

	pass_1_int64_array(int64[]{0L});
	pass_1_int64_array(int64[]{1L});

	pass_2_int64_array(int64[]{0L}, int64[]{0L});
	pass_2_int64_array(int64[]{1L}, int64[]{1L});

	pass_3_int64_array(int64[]{0L}, int64[]{0L}, int64[]{0L});
	pass_3_int64_array(int64[]{1L}, int64[]{1L}, int64[]{1L});

	pass_4_int64_array(int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L});
	pass_4_int64_array(int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L});

	pass_5_int64_array(int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L});
	pass_5_int64_array(int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L});

	pass_6_int64_array(int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L});
	pass_6_int64_array(int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L});

	pass_7_int64_array(int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L});
	pass_7_int64_array(int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L});

	pass_8_int64_array(int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L}, int64[]{0L});
	pass_8_int64_array(int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L}, int64[]{1L});
}





fn pass_1_int64_array(var int64[] a) {
	fmt::println(a);
}

fn pass_2_int64_array(var int64[] a, var int64[] b) {
	fmt::println(a, b);
}

fn pass_3_int64_array(var int64[] a, var int64[] b, var int64[] c) {
    fmt::println(a, b, c);
}

fn pass_4_int64_array(var int64[] a, var int64[] b, var int64[] c, var int64[] d) {
    fmt::println(a, b, c, d);
}

fn pass_5_int64_array(var int64[] a, var int64[] b, var int64[] c, var int64[] d, var int64[] e) {
    fmt::println(a, b, c, d, e);
}

fn pass_6_int64_array(var int64[] a, var int64[] b, var int64[] c, var int64[] d, var int64[] e, var int64[] f) {
    fmt::println(a, b, c, d, e, f);
}

fn pass_7_int64_array(var int64[] a, var int64[] b, var int64[] c, var int64[] d, var int64[] e, var int64[] f, var int64[] g) {
    fmt::println(a, b, c, d, e, f, g);
}

fn pass_8_int64_array(var int64[] a, var int64[] b, var int64[] c, var int64[] d, var int64[] e, var int64[] f, var int64[] g, var int64[] h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

