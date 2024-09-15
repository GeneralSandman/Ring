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
	var FuncType tmp;
	tmp = return_closure();
	tmp();
}

function return_closure() -> (FuncType) {
	return function() {
		fmt::println("return_closure:: closure block");
	};
}


