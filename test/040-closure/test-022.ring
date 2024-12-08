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


typedef function(string...) -> (string) FuncType1;

typedef function(FuncType1) FuncType2;


@main
function main() {

	var FuncType1 func_value;
	func_value = function(var string... str_value) -> (string) {
		return fmt::sprintf("[anonymous function {}]", str_value);
	};

	func2(func_value);
}

function func2(var FuncType1 func_value) {
	var string str_value;

	str_value = func_value("a", "b", "c");

	fmt::printf("func2:{}\n", str_value);
}