
package main

import {
	fmt;
	debug;
}

// TestDetail: 测试 括号运算符
// TestDetail: 括号运算符可以改变运算优先级
@main
function main() {

	var int int_value;

	int_value = 1;
	debug::assert(int_value == 1);

	int_value = 1 + 2*3;
	debug::assert(int_value == 7);

	int_value = (1+2) * 3;
	debug::assert(int_value == 9);

}