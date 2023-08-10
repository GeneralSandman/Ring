//
// File:    print_heart.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-06
//

package main

import {
	fmt;
	debug;
}

global {
	var double x;
	var double y;
	var double a;
}


@main
function main() {
	for (y = 1.5; y > -1.5; y -= 0.1) {
		for (x = -1.5; x < 1.5; x += 0.05) {
			a = x * x + y * y - 1;
			if(a * a * a - x * x * y * y * y <= 0.0){
				fmt::println_string("*");
			} else {
				fmt::println_string(" ");
			}
		}
		fmt::println_string("\n");
	}
}