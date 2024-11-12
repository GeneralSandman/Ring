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


typedef function(var double a) -> (string) functype_0;
typedef function(var int64 a) -> (functype_0) functype_1;
typedef function(var int  a) -> (functype_1) functype_2;


function return_closure() -> (functype_2) {
	fmt::println("return_closure:: invoke level3");
	return function(var int  a) -> (functype_1) {
		fmt::printf("return_closure:: invoke level2 int={}\n", a);
		return function(var int64 a) -> (functype_0) {
			fmt::printf("return_closure:: invoke level1 int64={}\n", a);
			return function(var double a) -> (string) {
				fmt::printf("return_closure:: invoke level0 double={}\n", a);
				return "hello ring compiler";
			};
		};
	};
}

// TestDetail: 匿名函数
// TestDetail: 不需要定义匿名函数变量, 可以直接返回

@main
function main() {
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



