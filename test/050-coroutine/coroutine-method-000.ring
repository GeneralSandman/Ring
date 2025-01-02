//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
	fmt;
	self;
}


typedef class Job1 {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;

	fn job_action1(var bool bool_value_0, var bool bool_value_1) {
		fmt::printf("            self:{}\n", self);

		fmt::printf("            Job1::job_action1 bool_value_0:  {}\n", bool_value_0);
		fmt::printf("            Job1::job_action1 bool_value_1:  {}\n", bool_value_1);
	
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
	
		yield();
	
		fmt::printf("            Job1::job_action1 local_bool_value_0:   {}\n", local_bool_value_0);
		fmt::printf("            Job1::job_action1 local_int_value_0:    {}\n", local_int_value_0);
		fmt::printf("            Job1::job_action1 local_int64_value_0:  {}\n", local_int64_value_0);
		fmt::printf("            Job1::job_action1 local_double_value_0: {}\n", local_double_value_0);
		fmt::printf("            Job1::job_action1 local_string_value_0: {}\n", local_string_value_0);
		fmt::printf("            Job1::job_action1 local_job1_value_0:   {}\n", local_job1_value_0);
	}
}



fn main() {

	var int64 co_id;

	var Job1 job1;

	fmt::println("main::1");
	job1.job_action1(true, false);


	job1 = Job1{
		Bool: true,
		Int: 1,
		Int64: 2L,
		Double: 2.34,
		String: "ring",
	};
	
	fmt::println("main::2");
	co_id = launch job1.job_action1(false, true);
	resume(co_id);
	fmt::println("main::3");
	resume(co_id);

}