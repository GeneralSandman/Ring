package main

import {
	fmt;
	debug;
}

typedef Job1 = class {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}


// TestDetail: 测试函数返回 Job1 类型
fn main() {
	fmt::println(return_1_job1_0());
	fmt::println(return_1_job1_1());

	fmt::println(return_2_job1_0());
	fmt::println(return_2_job1_1());

	fmt::println(return_3_job1_0());
	fmt::println(return_3_job1_1());

	fmt::println(return_4_job1_0());
	fmt::println(return_4_job1_1());

	fmt::println(return_5_job1_0());
	fmt::println(return_5_job1_1());

	fmt::println(return_6_job1_0());
	fmt::println(return_6_job1_1());

	fmt::println(return_7_job1_0());
	fmt::println(return_7_job1_1());

	fmt::println(return_8_job1_0());
	fmt::println(return_8_job1_1());


}




fn return_1_job1_0() -> (Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}
fn return_1_job1_1() -> (Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}



fn return_2_job1_0() -> (Job1,Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}
fn return_2_job1_1() -> (Job1,Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}



fn return_3_job1_0() -> (Job1,Job1,Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}
fn return_3_job1_1() -> (Job1,Job1,Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}



fn return_4_job1_0() -> (Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}
fn return_4_job1_1() -> (Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}



fn return_5_job1_0() -> (Job1,Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}
fn return_5_job1_1() -> (Job1,Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}



fn return_6_job1_0() -> (Job1,Job1,Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}
fn return_6_job1_1() -> (Job1,Job1,Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}



fn return_7_job1_0() -> (Job1,Job1,Job1,Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}
fn return_7_job1_1() -> (Job1,Job1,Job1,Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}



fn return_8_job1_0() -> (Job1,Job1,Job1,Job1,Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}
fn return_8_job1_1() -> (Job1,Job1,Job1,Job1,Job1,Job1,Job1,Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	}, Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	}, Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}