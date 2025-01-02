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

// 测试 2147483649L 这种形式的 int64常量
fn main() {
	var int64 local_int64_value_0;

	local_int64_value_0 = -2147483649L + -10L;
	fmt::println(local_int64_value_0);
	fmt::println(-2147483649L + -10L);

	local_int64_value_0 = 0L;
	fmt::println(local_int64_value_0);
	fmt::println(0L);

	local_int64_value_0 = -0L;
	fmt::println(local_int64_value_0);
	fmt::println(-0L);

}