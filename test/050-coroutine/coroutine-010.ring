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


typedef class Job1 {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}


fn job_action1() {
	var bool   local_bool_value_0   ;
	var int    local_int_value_0    ;
	var int64  local_int64_value_0  ;
	var double local_double_value_0 ;
	var string local_string_value_0 ;
	var Job1   local_job1_value_0   ;


	fmt::printf("            job_action1::1\n");
	fmt::printf("            local_bool_value_0:   {}\n", local_bool_value_0);
	fmt::printf("            local_int_value_0:    {}\n", local_int_value_0);
	fmt::printf("            local_int64_value_0:  {}\n", local_int64_value_0);
	fmt::printf("            local_double_value_0: {}\n", local_double_value_0);
	fmt::printf("            local_string_value_0: {}\n", local_string_value_0);
	fmt::printf("            local_job1_value_0:   {}\n", local_job1_value_0);
	fmt::printf("            job_action1::2\n");
}

fn job_action2() {
	var bool   local_bool_value_0   = true;
	var int    local_int_value_0    = 1;
	var int64  local_int64_value_0  = 2L;
	var double local_double_value_0 = 2.34;
	var string local_string_value_0 = "ring";
	var Job1   local_job1_value_0   = Job1{
		Bool: true,
		Int: 1,
		Int64: 2L,
		Double: 2.34,
		String: "ring",
	};


	fmt::printf("            job_action2::1\n");
	fmt::printf("            local_bool_value_0:   {}\n", local_bool_value_0);
	fmt::printf("            local_int_value_0:    {}\n", local_int_value_0);
	fmt::printf("            local_int64_value_0:  {}\n", local_int64_value_0);
	fmt::printf("            local_double_value_0: {}\n", local_double_value_0);
	fmt::printf("            local_string_value_0: {}\n", local_string_value_0);
	fmt::printf("            local_job1_value_0:   {}\n", local_job1_value_0);
	fmt::printf("            job_action2::2\n");
}
@main
fn main() {

	var int64 co_id;

	fmt::println("----launch&resume job_action1----");
	resume(launch job_action1());

	fmt::println("----invoke job_action1----");
	job_action1();



	fmt::println("----launch&resume job_action2----");
	resume(launch job_action2());

	fmt::println("----invoke job_action2----");
	job_action2();

	// // resume(co_id);

	// fmt::println("main::3");

	// resume(co_id);

	// fmt::println("main::4");

	// resume(co_id); // 无效果

}