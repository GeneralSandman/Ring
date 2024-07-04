package main

import {
	fmt;
	debug;
}

typedef class Job1 {
    field bool    Bool;
    field int     Int;
	field int64   Int64;
    field double  Double;
    field string  String;
}


// TestDetail: 测试函数返回 Job1 类型
@main
function main() {
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




function return_1_job1_0() -> (Job1) {
	return Job1{
		Bool:   false,
		Int:    0,
		Int64:  0L,
		Double: 0.0,
		String: "",
	};
}
function return_1_job1_1() -> (Job1) {
	return Job1{
		Bool:   true,
		Int:    1,
		Int64:  1L,
		Double: 1.0,
		String: "ring-v0.2.14-beta",
	};
}



function return_2_job1_0() -> (Job1,Job1) {
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
function return_2_job1_1() -> (Job1,Job1) {
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



function return_3_job1_0() -> (Job1,Job1,Job1) {
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
function return_3_job1_1() -> (Job1,Job1,Job1) {
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



function return_4_job1_0() -> (Job1,Job1,Job1,Job1) {
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
function return_4_job1_1() -> (Job1,Job1,Job1,Job1) {
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



function return_5_job1_0() -> (Job1,Job1,Job1,Job1,Job1) {
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
function return_5_job1_1() -> (Job1,Job1,Job1,Job1,Job1) {
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



function return_6_job1_0() -> (Job1,Job1,Job1,Job1,Job1,Job1) {
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
function return_6_job1_1() -> (Job1,Job1,Job1,Job1,Job1,Job1) {
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



function return_7_job1_0() -> (Job1,Job1,Job1,Job1,Job1,Job1,Job1) {
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
function return_7_job1_1() -> (Job1,Job1,Job1,Job1,Job1,Job1,Job1) {
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



function return_8_job1_0() -> (Job1,Job1,Job1,Job1,Job1,Job1,Job1,Job1) {
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
function return_8_job1_1() -> (Job1,Job1,Job1,Job1,Job1,Job1,Job1,Job1) {
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