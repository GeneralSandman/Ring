
package main

import {
	fmt;
	debug;
}



typedef class Job {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;

    fn printInfo() {
        fmt::printf("Job({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
    }
}

global {
    var Job[,] global_job_array_0;
}

// TestDetail: 数组的元素为 class-obect, 数组为二维数组
// TestDetail: 一行一行的单独初始化
fn main() {

    global_job_array_0 = new Job[2,2];
    global_job_array_0[0] = Job[]{
        Job{
            Bool:   true,
            Int:    0,
            Double: 0.0,
            String: "job-0",
        },
        Job{
            Bool:   false,
            Int:    1,
            Double: 1.0,
            String: "job-1",
        },
    };
    global_job_array_0[1] = Job[]{
        Job{
            Bool:   true,
            Int:    2,
            Double: 2.0,
            String: "job-2",
        },
        Job{
            Bool:   false,
            Int:    3,
            Double: 3.0,
            String: "job-3",
        },
    };


    fmt::println_string("test case 1");
    global_job_array_0[0,0].printInfo();
    global_job_array_0[0,1].printInfo();
    global_job_array_0[1,0].printInfo();
    global_job_array_0[1,1].printInfo();



    global_job_array_0[1] = Job[]{
        Job{
            Bool:   true,
            Int:    0,
            Double: 0.0,
            String: "job-0",
        },
        Job{
            Bool:   false,
            Int:    1,
            Double: 1.0,
            String: "job-1",
        },
    };
    global_job_array_0[0] = Job[]{
        Job{
            Bool:   true,
            Int:    2,
            Double: 2.0,
            String: "job-2",
        },
        Job{
            Bool:   false,
            Int:    3,
            Double: 3.0,
            String: "job-3",
        },
    };
    fmt::println_string("\ntest case 2");
    global_job_array_0[0,0].printInfo();
    global_job_array_0[0,1].printInfo();
    global_job_array_0[1,0].printInfo();
    global_job_array_0[1,1].printInfo();




}