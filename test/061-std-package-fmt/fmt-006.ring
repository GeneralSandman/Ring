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
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;

	method printInfo() {
		fmt::println(self.Bool, self.Int, self.Double, self.String);
	}
}

global {
	var Job1 global_job1_value_0;
}

// TestDetail: 测试 fmt::println 函数
@main
function main() {


	fmt::println(false);
	fmt::println(true);

	fmt::println(0);
	fmt::println(12);

	fmt::println(0.0);
	fmt::println(1.23456);

	fmt::println("123456789_");
	fmt::println("hello world");
	
	fmt::println(true, 1, 1.1, "hello world");



	global_job1_value_0.printInfo();
	
	global_job1_value_0 = Job1{
		Bool:   true,
		Int:    1,
		Double: 1.1,
		String: "global_job1_value_0"
	};
	global_job1_value_0.printInfo();

}