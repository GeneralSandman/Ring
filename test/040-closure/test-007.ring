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

typedef function()-> (int) FuncType;


@main
function main() {
	var FuncType tmp0;

	tmp0 = return_closure();

	var int int_value;
	int_value = tmp0();

	fmt::println(int_value);
}

function return_closure() -> (FuncType) {
	var FuncType tmp;
	tmp = function() -> (int){
		return 6456;
	};
	return tmp;
}


