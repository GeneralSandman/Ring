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


typedef fn() FuncType;


fn main() {
	var FuncType tmp;
	tmp = return_closure();
	tmp();
}

fn return_closure() -> (FuncType) {
	return fn() {
		fmt::println("return_closure:: closure block");
	};
}


