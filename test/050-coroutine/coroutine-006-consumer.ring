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

}


fn producer(var int64 next_job_co_id, var int produce_count) {
	var int i = 0;

	fmt::printf("producer start work\n");

	for(i = 0; i < produce_count; i++) {
		fmt::printf("producer   {}\n", i);
		resume(next_job_co_id);
	}
}


fn consumer_1(var int64 next_job_co_id) {
	var int   consumer_1_count;
	fmt::printf("consumer_1 start work\n");

    for(;;) {
		yield();
		fmt::printf("consumer_1 {}\n", consumer_1_count);
		consumer_1_count++;
		resume(next_job_co_id);
	}
}

fn consumer_2() {
	var int   consumer_2_count;
	fmt::printf("consumer_2 start work\n");

    for(;;) {
		yield();
		fmt::printf("consumer_2 {}\n", consumer_2_count);
		consumer_2_count++;
	}
}

@main
fn main() {
	var int64 consumer_1_id;
	var int64 consumer_2_id;

	consumer_2_id = launch consumer_2();
	consumer_1_id = launch consumer_1(consumer_2_id);


	resume(consumer_2_id);
	resume(consumer_1_id);


	var int produce_count = 10;
	producer(consumer_1_id, produce_count);


}