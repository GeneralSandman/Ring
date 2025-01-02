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

fn main(var string[] args) {

    fmt::println(len(args));
	fmt::println(args);

	var string arg;
	for(arg in range args) {
		fmt::println(arg);
	}
}