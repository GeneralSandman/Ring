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


typedef Functype_0 = fn(double) -> (string);
typedef Functype_1 = fn(int64) -> (Functype_0);
typedef Functype_2 = fn(int) -> (Functype_1);


fn return_closure() -> (Functype_2) {
	fmt::println("return_closure:: invoke level3");
	return fn(var int  a) -> (Functype_1) {
		fmt::printf("return_closure:: invoke level2 int={}\n", a);
		return fn(var int64 a) -> (Functype_0) {
			fmt::printf("return_closure:: invoke level1 int64={}\n", a);
			return fn(var double a) -> (string) {
				fmt::printf("return_closure:: invoke level0 double={}\n", a);
				return "hello ring compiler";
			};
		};
	};
}

// TestDetail: 匿名函数
// TestDetail: 不需要定义匿名函数变量, 可以直接返回

fn main() {
	var Functype_2 tmp_2;
	fmt::println("\nmain::1");
	tmp_2 = return_closure();
	fmt::printf("tmp_2 type:{}\n", reflect::typeof(tmp_2));


	var Functype_1 tmp_1;
	fmt::println("\nmain::2");
	tmp_1 = tmp_2(123);
	fmt::printf("tmp_1 type:{}\n", reflect::typeof(tmp_1));

	var Functype_0 tmp_0;
	fmt::println("\nmain::3");
	tmp_0 = tmp_1(456L);
	fmt::printf("tmp_0 type:{}\n", reflect::typeof(tmp_0));

	var string tmp;
	fmt::println("\nmain::4");
	tmp = tmp_0(3.1415);
	fmt::printf("tmp type:{}, value:{}\n", reflect::typeof(tmp), tmp);
}




