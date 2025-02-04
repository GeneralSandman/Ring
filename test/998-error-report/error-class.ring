//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
}

typedef Job = class {
	var bool     Bool;
    var int      Int;
    var int64    Int64;
    var double   Double;
    var string   String;
	var FuncType FuncField;
}

typedef FuncType = fn() -> (string);

//TestDetail: 初始化类中的field， 强制检查类型
fn main() {

	var Job local_job_value = Job {
		Bool: return_bool(),
		Int:  return_int(),
		Int64: return_int64(),
		Double: return_double(),
		String: return_string(),
		FuncField: fn() -> (string) {
			fmt::println("FuncField");
			return "tmp";
		},
	};

	fmt::println(local_job_value);
	local_job_value.FuncField();




	local_job_value.Int = 2;
	local_job_value.FuncField = fn() -> (string) {
		fmt::println("FuncField2");
		return "tmp2";
	};

	fmt::println(local_job_value);
	local_job_value.FuncField();
	
}


fn return_bool() -> (bool) {
	return true;
}

fn return_int() -> (int) {
	return 2;
}

fn return_int64() -> (int64) {
    return 3L;
}

fn return_double() -> (double) {
    return 4.0;
}

fn return_string() -> (string) {
    return "hello";
}