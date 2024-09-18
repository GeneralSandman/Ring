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
	var FuncType tmp;

	tmp = function() {
		fmt::println("main:: closure block");
	};

	pass_closure(tmp);
}

function pass_closure(var FuncType func_var) {
	fmt::println("pass_closure::begin");
	func_var();
	fmt::println("pass_closure::end");
}


