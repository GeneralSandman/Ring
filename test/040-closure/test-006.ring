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


typedef fn() FuncType1;
typedef fn() -> (FuncType1) FuncType2;

@main
fn main() {
	var FuncType1 tmp1;
	var FuncType2 tmp2;

	fmt::println("\nmain::1");
	tmp2 = return_closure();

	fmt::println("\nmain::2");
	tmp1 = tmp2();

	fmt::println("\nmain::3");
	tmp1();

	fmt::println("\nmain::4");
}

fn return_closure() -> (FuncType2) {
	fmt::println("return_closure begin");

	var FuncType2 tmp2;
	tmp2 = fn() -> (FuncType1){
		fmt::println("return_closure::level1 begin");
		return fn() {
			fmt::println("return_closure::level2 begin");
		};
	};

	return tmp2;
}


