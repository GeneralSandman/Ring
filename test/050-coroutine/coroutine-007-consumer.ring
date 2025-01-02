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


fn producer(var int64 consumer_co_id, var int produce_count) {
	var int i = 0;

	fmt::printf("producer start work\n");

	for(i = 0; i < produce_count; i++) {
		fmt::printf("producer   {}\n", i);
		resume(consumer_co_id);
	}
}

fn consumer_1() {
	var int   consumer_1_count;
	fmt::printf("consumer_1 start work\n");

	var string send_msg;
	var int64 next_consumer_co_id;

    for(;;) {
		yield();
		fmt::printf("consumer_1 {}\n", consumer_1_count);

		send_msg = "\"send a message to consumer_2 " .. to_string(consumer_1_count) .. "\"";

		fmt::printf("consumer_1 send:{}\n", send_msg);


		next_consumer_co_id = launch consumer_2(send_msg);
		resume(next_consumer_co_id);
		resume(next_consumer_co_id);

		consumer_1_count++;
	}
}

fn consumer_2(var string arg) {

	yield();

	fmt::printf("consumer_2 recv:{}\n", arg);
}

fn main() {
	var int64 consumer_1_id;

	consumer_1_id = launch consumer_1();

	resume(consumer_1_id);


	var int produce_count = 5;
	producer(consumer_1_id, produce_count);


}