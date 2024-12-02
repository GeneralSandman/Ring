
package main

import {
	fmt;
	debug;
}

@main
function main() {
	


	var int x;
	var int y;
	var int z;

	var int num;

	// -------------------
	num = 0;
	for(x=0; x<3; x=x+1) {
		for(y=0; y<3; y=y+1) {
			for(z=0; z<3; z=z+1) {
				if(x == 2 and y == 2 and z == 2) {
					fmt::println_int(x);
					fmt::println_int(y);
					fmt::println_int(z);
					fmt::println_string("");
					break 3;
				}
				num = num + 1;
			}
		}
	}

	fmt::println_string("finish for====");
	fmt::println_int(num);
	debug::assert(num == 26);
	debug::assert(x == 2);
	debug::assert(y == 2);
	debug::assert(z == 2);
	fmt::println_string("finish for====");


	fmt::println_string("");
	fmt::println_string("");

	num = 0;
	for(x=0; x<11; x=x+1) {
		for(y=0; y<120; y=y+1) {
			for(z=0; z<13; z=z+1) {
				num+=1;
				if(num > 100){
					break 3;
				}
			}
		}
	}

	fmt::println_string("finish for====");
	fmt::println_int(num);
	debug::assert(num == 101);
	debug::assert(x == 0);
	debug::assert(y == 7);
	debug::assert(z == 9);
	fmt::println_string("finish for====");

}
