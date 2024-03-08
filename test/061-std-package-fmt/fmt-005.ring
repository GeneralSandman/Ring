//
// File:    std-fmt-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	fmt;
}

// TestDetail: 测试 fmt::printf 函数

@main
function main() {
	fmt::printf("{} {} {} {}\n", true, 1, 1.1, "hello");
	fmt::printf("\{} {} {} {}\n", true, 1, 1.1, "hello");
	fmt::printf("\{\} {} {} {}\n", true, 1, 1.1, "hello");
	fmt::printf("{\} {} {} {}\n", true, 1, 1.1, "hello");

	// fmt::printf("{} {}", true); // 运行错误, 占位符数量与 args数量不匹配
	// fmt::printf(true, true); // 运行错误, 第一个参数必须是字符串
}