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


typedef function() FuncType1;
typedef function() -> (FuncType1) FuncType2;

@main
function main() {
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

function return_closure() -> (FuncType2) {
	fmt::println("return_closure begin");

	var FuncType1 tmp;
	tmp = function() -> (FuncType1){
		fmt::println("return_closure::level1 begin");
		return function() {
			fmt::println("return_closure::level2 begin");
		};
	};

	return tmp;
}


