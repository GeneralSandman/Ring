//
// File:    std-fmt-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	fmt;
}

typedef class Job1 {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;

	fn printInfo() {
		fmt::printf("Bool:{} Int:{} Double:{} String:{}\n", self.Bool, self.Int, self.Double, self.String);
	}
}

global {
	var Job1 global_job1_value_0;
}

// TestDetail: 测试 fmt::printf 函数

@main
fn main() {
	fmt::printf("{} {} {} {}\n", true, 1, 1.1, "hello");
	fmt::printf("\{} {} {} {}\n", true, 1, 1.1, "hello");
	fmt::printf("\{\} {} {} {}\n", true, 1, 1.1, "hello");
	fmt::printf("{\} {} {} {}\n", true, 1, 1.1, "hello");

	// fmt::printf("{} {}", true); // 运行错误, 占位符数量与 args数量不匹配
	// fmt::printf(true, true); // 运行错误, 第一个参数必须是字符串


	global_job1_value_0.printInfo();

	
	global_job1_value_0 = Job1{
		Bool:   true,
		Int:    1,
		Double: 1.1,
		String: "global_job1_value_0"
	};
	global_job1_value_0.printInfo();
}