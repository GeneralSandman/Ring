//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
	fmt;
}


typedef fn() FuncType;

@main
fn main() {

	var int64 co_id;


	co_id = launch fn() {
		for(;true;) {
			time::sleep(1000000000L);
			fmt::printf("time={}          job\n", time::time()/1000000000L);
			yield();
		}
	}();


	for(;true;) {
		time::sleep(1000000000L);
		fmt::printf("time={}  main\n", time::time()/1000000000L);
		resume(co_id);
	}

}
