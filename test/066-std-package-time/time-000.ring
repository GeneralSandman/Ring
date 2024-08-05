
package main

import {
    fmt;
    debug;
    vm;
    os;
    time;
}


// 测试 time package time() / sleep() 函数
@main
function main() {
	var int64 timestamp_0;
	var int64 timestamp_1;
	
	timestamp_0 = time::time();
	// fmt::printf("timestamp={}\n", timestamp_0);
	debug::debug_assert(timestamp_0 != 0L);

	time::sleep(1000000000L);

	timestamp_1 = time::time();
	// fmt::printf("timestamp={}\n", timestamp_1);
	debug::debug_assert(timestamp_1 != 0L);
	debug::debug_assert(timestamp_1 - timestamp_0 == 1L);
}
