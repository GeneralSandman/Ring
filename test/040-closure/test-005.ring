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


typedef function() FuncType;


@main
function main() {
	var FuncType tmp0, tmp1;

	tmp0 = function() {
		fmt::println("main:: closure block");
	};
	tmp1 = pass_closure(tmp0);

	fmt::printf("\n\n");

	fmt::println("main::begin");
	tmp1();
	fmt::println("main::end");
	
}

function pass_closure(var FuncType func_var) -> (FuncType) {
	fmt::println("pass_closure::begin");
	func_var();
	fmt::println("pass_closure::end");

	return function() {
		fmt::println("pass_closure:: closure block");
	};
}

