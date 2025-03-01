//
// File:    std-fmt-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	fmt;
}

typedef Job1 = class {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;

	fn printInfo() {
		fmt::println(self.Bool, self.Int, self.Double, self.String);
	}
}

global {
	var Job1 global_job1_value_0;
}

// TestDetail: 测试 fmt::println 函数
fn main() {


	fmt::println(false);
	fmt::println(true);
	fmt::println(fmt::sprintf("{}", true));

	fmt::println(0);
	fmt::println(12);
	fmt::println(fmt::sprintf("{}", 13));

	fmt::println(0.0);
	fmt::println(1.23456);
	fmt::println(fmt::sprintf("{}", 3.14));

	fmt::println("123456789_");
	fmt::println("hello world");
	fmt::println(fmt::sprintf("{}", "ring"));
	
	fmt::println(true, 1, 1.1, "hello world");
	fmt::println(fmt::sprintf("{} {} {}  {}", true, 1, 1.1, "hello world"));



	global_job1_value_0.printInfo();
	
	global_job1_value_0 = Job1{
		Bool:   true,
		Int:    1,
		Double: 1.1,
		String: "global_job1_value_0"
	};
	global_job1_value_0.printInfo();

}