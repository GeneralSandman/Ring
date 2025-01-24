//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	os;
	debug;
	fmt;
}

typedef Job = class {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}

typedef Task = class {
	var bool    Bool;
	var int     Int;
    var int64   Int64;
    var double  Double;
    var string  String;

	var Job     JobValue;
}

typedef FuncType1 = fn();

typedef FuncType2 = fn() -> (FuncType1);


// TestDetail: 测试见的FreeValue , 不支持逃逸
fn main() {

	var FuncType1 func_type1_var;

	//  ----------------------
	fmt::printf("========== return new closure\n");
	func_type1_var = return_closure();
	func_type1_var();
	func_type1_var();
	func_type1_var();
	func_type1_var();


	//  ----------------------
	fmt::printf("========== return new closure\n");
	func_type1_var = return_closure();
	func_type1_var();
	func_type1_var();
	func_type1_var();
	func_type1_var();

}

fn return_closure() -> (FuncType1) {

	var bool   level0_local_bool_value_0;
	var int    level0_local_int_value_0;
	var int64  level0_local_int64_value_0;
	var double level0_local_double_value_0;
	var string level0_local_string_value_0;
	var Job    level0_local_job_value_0;

	level0_local_bool_value_0 = true;
	level0_local_int_value_0 = 1;
	level0_local_int64_value_0 = 1L;
	level0_local_double_value_0 = 1.0;
	level0_local_string_value_0 = "s";
	level0_local_job_value_0 = Job{
		Bool: true, 
		Int:  1, 
		Int64: 1L,
		Double: 1.0, 
		String: "s",
	};
	fmt::printf("----------- in return_closure block\n");
	fmt::printf("[return_closure] level0_local_bool_value_0={}\n", level0_local_bool_value_0);
	fmt::printf("[return_closure] level0_local_int_value_0={}\n", level0_local_int_value_0);
	fmt::printf("[return_closure] level0_local_int64_value_0={}\n", level0_local_int64_value_0);
	fmt::printf("[return_closure] level0_local_double_value_0={}\n", level0_local_double_value_0);
	fmt::printf("[return_closure] level0_local_string_value_0={}\n", level0_local_string_value_0);
	fmt::printf("[return_closure] level0_local_job_value_0={}\n", level0_local_job_value_0);
	fmt::printf("----------- out return_closure block\n\n");

	return fn() {
		level0_local_bool_value_0 = not level0_local_bool_value_0;
		level0_local_int_value_0++;
		level0_local_int64_value_0++;
		level0_local_double_value_0++;
		level0_local_string_value_0 = level0_local_string_value_0 .. to_string(len(level0_local_string_value_0));

		level0_local_job_value_0.Bool = not level0_local_job_value_0.Bool;
		level0_local_job_value_0.Int++;
		level0_local_job_value_0.Int64++;
		level0_local_job_value_0.Double++;
		level0_local_job_value_0.String = level0_local_job_value_0.String .. to_string(len(level0_local_job_value_0.String));

		fmt::printf("----------- in closure block\n");
		fmt::printf("[closure block] level0_local_bool_value_0={}\n", level0_local_bool_value_0);
		fmt::printf("[closure block] level0_local_int_value_0={}\n", level0_local_int_value_0);
		fmt::printf("[closure block] level0_local_int64_value_0={}\n", level0_local_int64_value_0);
		fmt::printf("[closure block] level0_local_double_value_0={}\n", level0_local_double_value_0);
		fmt::printf("[closure block] level0_local_string_value_0={}\n", level0_local_string_value_0);
		fmt::printf("[closure block] level0_local_job_value_0={}\n", level0_local_job_value_0);
		fmt::printf("----------- out closure block\n\n");
	};
}


