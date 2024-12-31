//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	debug;
}

// minus 符号
@main
fn main() {
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