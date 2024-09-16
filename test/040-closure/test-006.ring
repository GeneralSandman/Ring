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


@main
function main() {
	var FuncType tmp0, tmp1;

	tmp0 = return_closure();

	tmp1 = tmp0();

	tmp1();
}

function return_closure() -> (FuncType) {
	fmt::println("return_closure:: begin");

	var FuncType tmp;
	tmp = function() -> (FuncType){
		fmt::println("return_closure::level1 begin");
		return function() {
			fmt::println("return_closure::level2 begin");
		};
	};

	return tmp;
}


