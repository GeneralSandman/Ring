
package main

import {
	fmt;
	debug;
}



typedef class Job {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;

    method printInfo() {
        fmt::printf("Job({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
    }
}

global {
    var Job[] global_job_array_0;
}

// TestDetail: 数组的元素为 class-obect
// TestDetail: 通过一行多项赋值一个个初始化
// TestDetail: 多项赋值的右边全部为 class-object literal
@main
function main() {
    global_job_array_0 = new Job[10];

    global_job_array_0[0], global_job_array_0[1], global_job_array_0[2], global_job_array_0[3], 
    global_job_array_0[4], global_job_array_0[5], global_job_array_0[6], global_job_array_0[7],
    global_job_array_0[8], global_job_array_0[9]  = 
    Job{
        Bool:   true,
        Int:    0,
        Double: 0.0,
        String: "0",
    },
    Job{
        Bool:   false,
        Int:    1,
        Double: 1.0,
        String: "1",
    },
    Job{
        Bool:   true,
        Int:    2,
        Double: 2.0,
        String: "2",
    },
    Job{
        Bool:   false,
        Int:    3,
        Double: 3.0,
        String: "3",
    },
    Job{
        Bool:   true,
        Int:    4,
        Double: 4.0,
        String: "4",
    },
    Job{
        Bool:   false,
        Int:    5,
        Double: 5.0,
        String: "5",
    },
    Job{
        Bool:   true,
        Int:    6,
        Double: 6.0,
        String: "6",
    },
    Job{
        Bool:   false,
        Int:    7,
        Double: 7.0,
        String: "7",
    },
    Job{
        Bool:   true,
        Int:    8,
        Double: 8.0,
        String: "8",
    },
    Job{
        Bool:   false,
        Int:    9,
        Double: 9.0,
        String: "9",
    };



    fmt::println_string("test case 1-------");
    var Job local_job_value;
    for(local_job_value in range global_job_array_0) {
        local_job_value.printInfo();
    }






    global_job_array_0[0], global_job_array_0[1], global_job_array_0[2], global_job_array_0[3], 
    global_job_array_0[4], global_job_array_0[5], global_job_array_0[6], global_job_array_0[7],
    global_job_array_0[8], global_job_array_0[9]  = 
    global_job_array_0[9], global_job_array_0[8], global_job_array_0[7], global_job_array_0[6],
    global_job_array_0[5], global_job_array_0[4], global_job_array_0[3], global_job_array_0[2],
    global_job_array_0[1], global_job_array_0[0];


    fmt::println_string("\ntest case 2-------");
    var Job local_job_value;
    for(local_job_value in range global_job_array_0) {
        local_job_value.printInfo();
    }

}