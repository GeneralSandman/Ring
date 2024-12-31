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


fn test(var bool a) {

}

typedef class Job {
	var int a;
	fn PrintInfo(var int a, var bool b) {
	}
}


typedef fn(int, bool) FuncType;


// 主要看函数调用，参数是不是匹配
@main
fn main() {

	test_call();

	test_launch();
}

fn test_call() {
	// test(true);

	// var Job job_value;
	// job_value.PrintInfo();


	// var FuncType func_type_var;
	// func_type_var = fn()(var int a, var bool b) {
	// 	fmt::println("func_type_var", a, b);
	// };
	// func_type_var(false, false);


	// fn (var int a) {
	// 	fmt::println("anonymous a=", a);
	// }(1);
}

fn test_launch() {


	// launch test(true);


	// var Job job_value;
	// launch job_value.PrintInfo(1, false);


	// var FuncType func_type_var;
	// func_type_var = fn()(var int a, var bool b) {
	// 	fmt::println("func_type_var", a, b);
    // };
	// launch func_type_var(1, false);

	launch fn(var string a) {

	}("");
}
