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

global {
	var int   producer_count = 10;

	var int64 consumerid;
	var int   consumer_count;
}


fn producer() {
	var int i = 0;

	fmt::printf("producer start work\n");

	for(i = 0; i < producer_count; i++) {
		fmt::printf("producer {}\n", i);
		resume(consumerid);
	}
}


fn consumer() {
	fmt::printf("consumer start work\n");
    for(;;) {
		yield();
		fmt::printf("consumer {}\n", consumer_count);
		consumer_count++;
	}
}

fn main() {

	consumerid = launch consumer();
	resume(consumerid);

	producer();
}