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


typedef fn(double) -> (string) functype_0;
typedef fn(int64) -> (functype_0) functype_1;
typedef fn(int) -> (functype_1) functype_2;


fn return_closure() -> (functype_2) {
	fmt::println("return_closure:: invoke level3");
	var functype_2 func_var;
	func_var = fn(var int  a) -> (functype_1) {
		fmt::printf("return_closure:: invoke level2 int={}\n", a);
		var functype_1 func_var;
		func_var = fn(var int64 a) -> (functype_0) {
			fmt::printf("return_closure:: invoke level1 int64={}\n", a);
			var functype_0 func_var;
			func_var = fn(var double a) -> (string) {
				fmt::printf("return_closure:: invoke level0 double={}\n", a);
				return "hello ring compiler";
			};
			return func_var;
		};
		return func_var;
	};
	return func_var;
}


@main
fn main() {
	var functype_2 tmp_2;
	fmt::println("\nmain::1");
	tmp_2 = return_closure();
	fmt::printf("tmp_2 type:{}\n", reflect::typeof(tmp_2));


	var functype_1 tmp_1;
	fmt::println("\nmain::2");
	tmp_1 = tmp_2(123);
	fmt::printf("tmp_1 type:{}\n", reflect::typeof(tmp_1));

	var functype_0 tmp_0;
	fmt::println("\nmain::3");
	tmp_0 = tmp_1(456L);
	fmt::printf("tmp_0 type:{}\n", reflect::typeof(tmp_0));

	var string tmp;
	fmt::println("\nmain::4");
	tmp = tmp_0(3.1415);
	fmt::printf("tmp type:{}, value:{}\n", reflect::typeof(tmp), tmp);
}




