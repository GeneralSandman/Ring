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


fn main() {
	var bool   local_bool_value;
	var int    local_int_value;
	var int64  local_int64_value;
	var double local_double_value;
	var string local_string_value;
	var Job    local_job_value;
	var Task   local_task_value;

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


	debug::var_dump(local_bool_value);
	debug::var_dump(local_int_value);
	debug::var_dump(local_int64_value);
	debug::var_dump(local_double_value);
	debug::var_dump(local_string_value);
	debug::var_dump(local_job_value);
	debug::var_dump(local_task_value);

	debug::var_dump(local_bool_array);
	debug::var_dump(local_int_array);
	debug::var_dump(local_int64_array);
	debug::var_dump(local_double_array);
	debug::var_dump(local_string_array);
	debug::var_dump(local_job_array);

	debug::var_dump(local_bool_array_2);
	debug::var_dump(local_int_array_2);
	debug::var_dump(local_int64_array_2);
	debug::var_dump(local_double_array_2);
	debug::var_dump(local_string_array_2);
	debug::var_dump(local_job_array_2);

}
