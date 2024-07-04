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

	var Job1 local_job1_value_0 = Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
	
}