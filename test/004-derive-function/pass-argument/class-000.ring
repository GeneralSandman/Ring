package main

import {
	fmt;
	debug;
}


typedef class Job1 {
    field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;
}


// TestDetail: 测试函数返回 bool 类型
@main
function main() {

	var Job1 local_job1_value_0;
	var Job1 local_job1_value_1;
	
	local_job1_value_0 = Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
	local_job1_value_1 = Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "qscdevgt456",
	};

	pass_1_job1(local_job1_value_0);
	pass_1_job1(local_job1_value_1);

	pass_2_job1(local_job1_value_0, local_job1_value_0);
	pass_2_job1(local_job1_value_1, local_job1_value_1);

	pass_3_job1(local_job1_value_0, local_job1_value_0, local_job1_value_0);
	pass_3_job1(local_job1_value_1, local_job1_value_1, local_job1_value_1);

	pass_4_job1(local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0);
	pass_4_job1(local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1);

	pass_5_job1(local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0);
	pass_5_job1(local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1);

	pass_6_job1(local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0);
	pass_6_job1(local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1);

	pass_7_job1(local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0);
	pass_7_job1(local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1);

	pass_8_job1(local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0, local_job1_value_0);
	pass_8_job1(local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1, local_job1_value_1);
}





function pass_1_job1(var Job1 a) {
	fmt::println(a);
}

function pass_2_job1(var Job1 a, var Job1 b) {
	fmt::println(a, b);
}

function pass_3_job1(var Job1 a, var Job1 b, var Job1 c) {
    fmt::println(a, b, c);
}

function pass_4_job1(var Job1 a, var Job1 b, var Job1 c, var Job1 d) {
    fmt::println(a, b, c, d);
}

function pass_5_job1(var Job1 a, var Job1 b, var Job1 c, var Job1 d, var Job1 e) {
    fmt::println(a, b, c, d, e);
}

function pass_6_job1(var Job1 a, var Job1 b, var Job1 c, var Job1 d, var Job1 e, var Job1 f) {
    fmt::println(a, b, c, d, e, f);
}

function pass_7_job1(var Job1 a, var Job1 b, var Job1 c, var Job1 d, var Job1 e, var Job1 f, var Job1 g) {
    fmt::println(a, b, c, d, e, f, g);
}

function pass_8_job1(var Job1 a, var Job1 b, var Job1 c, var Job1 d, var Job1 e, var Job1 f, var Job1 g, var Job1 h) {
    fmt::println(a, b, c, d, e, f, g, h);
}

