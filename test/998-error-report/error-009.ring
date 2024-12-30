//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	os;
	debug;
}


function test() {

}

typedef class Job {
	field int a;
	method PrintInfo(var int a) -> (bool) {
		var int a;
		return false;
	}
}




@main
function main() {
	var bool bool_value;
	var int  int_value;
	var int64 int64_value;
	var string string_value;

	var Job job_value;

	// bool_value = job_value.PrintInfo();

	fmt::println(bool_value, int_value);
}
