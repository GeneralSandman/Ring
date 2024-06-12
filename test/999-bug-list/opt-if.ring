//
// File:    string-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

// minus 符号
@main
function main() {
	if(false) {
		fmt::println("1");
	} else {
		fmt::println("2");
	}

	if(false and false) {
		fmt::println("1");
	} else {
		fmt::println("2");
	}

}