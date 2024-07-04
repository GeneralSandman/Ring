package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递double数组类型参数
// TestDetail: 分别传递1-8个double数组类型参数
@main
function main() {

	pass_1_double_array(double[]{0.0});
	pass_1_double_array(double[]{1.0});

	pass_2_double_array(double[]{0.0}, double[]{0.0});
	pass_2_double_array(double[]{1.0}, double[]{1.0});

	pass_3_double_array(double[]{0.0}, double[]{0.0}, double[]{0.0});
	pass_3_double_array(double[]{1.0}, double[]{1.0}, double[]{1.0});

	pass_4_double_array(double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0});
	pass_4_double_array(double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0});

	pass_5_double_array(double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0});
	pass_5_double_array(double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0});

	pass_6_double_array(double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0});
	pass_6_double_array(double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0});

	pass_7_double_array(double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0});
	pass_7_double_array(double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0});

	pass_8_double_array(double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0}, double[]{0.0});
	pass_8_double_array(double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0}, double[]{1.0});
}





function pass_1_double_array(var double[] a) {
	fmt::println(a);
}

function pass_2_double_array(var double[] a, var double[] b) {
	fmt::println(a, b);
}

function pass_3_double_array(var double[] a, var double[] b, var double[] c) {
    fmt::println(a, b, c);
}

function pass_4_double_array(var double[] a, var double[] b, var double[] c, var double[] d) {
    fmt::println(a, b, c, d);
}

function pass_5_double_array(var double[] a, var double[] b, var double[] c, var double[] d, var double[] e) {
    fmt::println(a, b, c, d, e);
}

function pass_6_double_array(var double[] a, var double[] b, var double[] c, var double[] d, var double[] e, var double[] f) {
    fmt::println(a, b, c, d, e, f);
}

function pass_7_double_array(var double[] a, var double[] b, var double[] c, var double[] d, var double[] e, var double[] f, var double[] g) {
    fmt::println(a, b, c, d, e, f, g);
}

function pass_8_double_array(var double[] a, var double[] b, var double[] c, var double[] d, var double[] e, var double[] f, var double[] g, var double[] h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

