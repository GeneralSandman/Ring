package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递bool数组类型参数
// TestDetail: 分别传递1-8个bool数组类型参数
@main
function main() {

	pass_1_bool_array(bool[]{false});
	pass_1_bool_array(bool[]{true});

	pass_2_bool_array(bool[]{false}, bool[]{false});
	pass_2_bool_array(bool[]{true},  bool[]{true});

	pass_3_bool_array(bool[]{false}, bool[]{false}, bool[]{false});
	pass_3_bool_array(bool[]{true},  bool[]{true},  bool[]{true});

	pass_4_bool_array(bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false});
	pass_4_bool_array(bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true});

	pass_5_bool_array(bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false});
	pass_5_bool_array(bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true});

	pass_6_bool_array(bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false});
	pass_6_bool_array(bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true});

	pass_7_bool_array(bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false});
	pass_7_bool_array(bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true});

	pass_8_bool_array(bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false}, bool[]{false});
	pass_8_bool_array(bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true},  bool[]{true});
}





function pass_1_bool_array(var bool[] a) {
	fmt::println(a);
}

function pass_2_bool_array(var bool[] a, var bool[] b) {
	fmt::println(a, b);
}

function pass_3_bool_array(var bool[] a, var bool[] b, var bool[] c) {
    fmt::println(a, b, c);
}

function pass_4_bool_array(var bool[] a, var bool[] b, var bool[] c, var bool[] d) {
    fmt::println(a, b, c, d);
}

function pass_5_bool_array(var bool[] a, var bool[] b, var bool[] c, var bool[] d, var bool[] e) {
    fmt::println(a, b, c, d, e);
}

function pass_6_bool_array(var bool[] a, var bool[] b, var bool[] c, var bool[] d, var bool[] e, var bool[] f) {
    fmt::println(a, b, c, d, e, f);
}

function pass_7_bool_array(var bool[] a, var bool[] b, var bool[] c, var bool[] d, var bool[] e, var bool[] f, var bool[] g) {
    fmt::println(a, b, c, d, e, f, g);
}

function pass_8_bool_array(var bool[] a, var bool[] b, var bool[] c, var bool[] d, var bool[] e, var bool[] f, var bool[] g, var bool[] h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

