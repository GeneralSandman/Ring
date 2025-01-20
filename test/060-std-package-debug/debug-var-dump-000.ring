//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	debug;
}


typedef class Job {
    var bool    Bool;
    var int     Int;
	var int64   Int64;
    var double  Double;
    var string  String;
}

typedef class Task {
	var bool    Bool;
	var int     Int;
    var int64   Int64;
    var double  Double;
    var string  String;

	var Job     JobValue;
}

typedef fn(int) -> (string) FuncType;


fn main() {
	var bool     local_bool_value;
	var int      local_int_value;
	var int64    local_int64_value;
	var double   local_double_value;
	var string   local_string_value;
	var Job      local_job_value;
	var Task     local_task_value;
	var FuncType local_func_value;

	local_func_value = fn(var int a) -> (string) {

	};

	var bool[]   local_bool_array = bool[]{false, true};
	var int[]    local_int_array = int[]{1, 2};
	var int64[]  local_int64_array = int64[]{2L, 3L};
	var double[] local_double_array = double[]{1.1, 2.2};
	var string[] local_string_array = string[]{"hello", "world"};
	var Job[]    local_job_array = Job[]{
		Job{
			Bool: false, 
			Int:  1, 
			Int64: 1L,
			Double: 1.1, 
			String: "hello",
		}, 
		Job{
			Bool: true, 
			Int:  2, 
			Int64: 2L,
			Double: 2.2, 
			String: "world",
		},
	};
	var Task[]   local_task_array = Task[]{
		Task{
			Bool: false, 
			Int:  1, 
			Int64: 1L,
			Double: 1.1, 
			String: "hello",
		}, 
		Task{
			Bool: true, 
			Int:  2, 
			Int64: 2L,
			Double: 2.2, 
			String: "world",
		},
	};
	// var FuncType[] local_func_array = new FuncType[2];
	var FuncType[] local_func_array = FuncType[]{
		local_func_value,
		local_func_value,
	};

	var bool[!2] local_bool_array_2 = bool[!2]{
		bool[]{false, true},
		bool[]{true, false},
	};
	var int[!2] local_int_array_2 = int[!2]{
		int[]{1, 2},
		int[]{2, 1},
	};
	var int64[!2] local_int64_array_2 = int64[!2]{
		int64[]{2L, 3L},
		int64[]{3L, 2L},
	};
	var double[!2] local_double_array_2 = double[!2]{
		double[]{1.1, 2.2},
		double[]{2.2, 1.1},
	};
	var string[!2] local_string_array_2 = string[!2]{
        string[]{"hello", "world"},
        string[]{"world", "hello"},
	};
	var Job[!2] local_job_array_2 = Job[!2]{
        Job[]{
			Job{
				Bool: false, 
				Int:  1, 
				Int64: 1L,
				Double: 1.1, 
				String: "hello",
			}, 
			Job{
				Bool: true, 
				Int:  2, 
				Int64: 2L,
				Double: 2.2, 
				String: "world",
			},
		},
		Job[]{
			Job{
				Bool: false, 
				Int:  1, 
				Int64: 1L,
				Double: 1.1, 
				String: "hello",
			}, 
			Job{
				Bool: true, 
				Int:  2, 
				Int64: 2L,
				Double: 2.2, 
				String: "world",
			},
		},
	};
	var Task[!2] local_task_array_2 = Task[!2]{
		Task[]{
			local_task_value,
			local_task_value,
		},
		Task[]{
			local_task_value,
			local_task_value,
		},
	};
	var FuncType[!2] local_func_array_2 = FuncType[!2]{
		FuncType[]{
			local_func_value,
			local_func_value,
		},
		FuncType[]{
			local_func_value,
			local_func_value,
		},
	};


	debug::var_dump(local_bool_value);
	debug::var_dump(local_int_value);
	debug::var_dump(local_int64_value);
	debug::var_dump(local_double_value);
	debug::var_dump(local_string_value);
	debug::var_dump(local_job_value);
	debug::var_dump(local_task_value);
	// debug::var_dump(local_func_value); // 输出：closure(fn(int)->(string)) => 0x12fe96030，是指针，不好测试

	debug::var_dump(local_bool_array);
	debug::var_dump(local_int_array);
	debug::var_dump(local_int64_array);
	debug::var_dump(local_double_array);
	debug::var_dump(local_string_array);
	debug::var_dump(local_job_array);
	debug::var_dump(local_task_array);
	// debug::var_dump(local_func_array); // 输出指针，不太好测试

	debug::var_dump(local_bool_array_2);
	debug::var_dump(local_int_array_2);
	debug::var_dump(local_int64_array_2);
	debug::var_dump(local_double_array_2);
	debug::var_dump(local_string_array_2);
	debug::var_dump(local_job_array_2);
	debug::var_dump(local_task_array_2);
	// debug::var_dump(local_func_array_2); // 输出指针，不太好测试

}
