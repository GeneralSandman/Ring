
package main

import {
    fmt;
    debug;
    vm;
    os;
    time;
}


// 测试 time package time() / sleep() 函数
fn main() {
	var int64 timestamp_0;
	var int64 timestamp_1;
	var int64 interval;
	
	timestamp_0 = time::time();
	// fmt::printf("timestamp={}\n", timestamp_0);
	debug::assert(timestamp_0 != 0L);

	time::sleep(1000000000L);

	timestamp_1 = time::time();
	// fmt::printf("timestamp={}\n", timestamp_1);
	debug::assert(timestamp_1 != 0L);

	interval = timestamp_1 - timestamp_0;
	// fmt::printf("interval={} {}\n", interval, interval/1000000000L);
	debug::assert(interval/1000000000L == 1L);
}
