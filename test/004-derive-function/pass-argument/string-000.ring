package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递string类型参数
// TestDetail: 分别传递1-8个string类型参数
@main
function main() {

	pass_1_string("0");
	pass_1_string("1");

	pass_2_string("0", "0");
	pass_2_string("1", "1");

	pass_3_string("0", "0", "0");
	pass_3_string("1", "1", "1");

	pass_4_string("0", "0", "0", "0");
	pass_4_string("1", "1", "1", "1");

	pass_5_string("0", "0", "0", "0", "0");
	pass_5_string("1", "1", "1", "1", "1");

	pass_6_string("0", "0", "0", "0", "0", "0");
	pass_6_string("1", "1", "1", "1", "1", "1");

	pass_7_string("0", "0", "0", "0", "0", "0", "0");
	pass_7_string("1", "1", "1", "1", "1", "1", "1");

	pass_8_string("0", "0", "0", "0", "0", "0", "0", "0");
	pass_8_string("1", "1", "1", "1", "1", "1", "1", "1");
}





function pass_1_string(var string a) {
	fmt::println(a);
}

function pass_2_string(var string a, var string b) {
	fmt::println(a, b);
}

function pass_3_string(var string a, var string b, var string c) {
    fmt::println(a, b, c);
}

function pass_4_string(var string a, var string b, var string c, var string d) {
    fmt::println(a, b, c, d);
}

function pass_5_string(var string a, var string b, var string c, var string d, var string e) {
    fmt::println(a, b, c, d, e);
}

function pass_6_string(var string a, var string b, var string c, var string d, var string e, var string f) {
    fmt::println(a, b, c, d, e, f);
}

function pass_7_string(var string a, var string b, var string c, var string d, var string e, var string f, var string g) {
    fmt::println(a, b, c, d, e, f, g);
}

function pass_8_string(var string a, var string b, var string c, var string d, var string e, var string f, var string g, var string h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

