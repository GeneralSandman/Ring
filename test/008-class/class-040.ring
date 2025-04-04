
package main

import {
	fmt;
	debug;
}



typedef Job = class {
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
// TestDetail: 直接通过索引交换元素, 只不过是一次交换一整列
// TestDetail: ```
// TestDetail: global_job_array_0 = new Job[2,2];
// TestDetail: global_job_array_0[0], global_job_array_0[1] = global_job_array_0[1], global_job_array_0[0];
// TestDetail: ```
fn main() {

    global_job_array_0 = new Job[2,2];
    global_job_array_0[0,0] = Job{
        Bool:   true,
        Int:    0,
        Double: 0.0,
        String: "job-0",
    };
    global_job_array_0[0,1] = Job{
        Bool:   false,
        Int:    1,
        Double: 1.0,
        String: "job-1",
    };
    global_job_array_0[1,0] = Job{
        Bool:   true,
        Int:    2,
        Double: 2.0,
        String: "job-2",
    };
    global_job_array_0[1,1] = Job{
        Bool:   false,
        Int:    3,
        Double: 3.0,
        String: "job-3",
    };


    fmt::println_string("test case 1");
    global_job_array_0[0,0].printInfo();
    global_job_array_0[0,1].printInfo();
    global_job_array_0[1,0].printInfo();
    global_job_array_0[1,1].printInfo();



    // var Job[] local_job_array_0;
    global_job_array_0[0,0], global_job_array_0[0,1], global_job_array_0[1,0], global_job_array_0[1,1] = global_job_array_0[1,0], global_job_array_0[1,1], global_job_array_0[0,0], global_job_array_0[0,1];
    fmt::println_string("\ntest case 2");
    global_job_array_0[0,0].printInfo();
    global_job_array_0[0,1].printInfo();
    global_job_array_0[1,0].printInfo();
    global_job_array_0[1,1].printInfo();


    global_job_array_0[0], global_job_array_0[1] = global_job_array_0[1], global_job_array_0[0];
    fmt::println_string("\ntest case 3");
    global_job_array_0[0,0].printInfo();
    global_job_array_0[0,1].printInfo();
    global_job_array_0[1,0].printInfo();
    global_job_array_0[1,1].printInfo();

    var Job[] local_job_array_0;
    local_job_array_0 = global_job_array_0[0];
    global_job_array_0[0] = global_job_array_0[1];
    global_job_array_0[1] = local_job_array_0;
    fmt::println_string("\ntest case 4");
    global_job_array_0[0,0].printInfo();
    global_job_array_0[0,1].printInfo();
    global_job_array_0[1,0].printInfo();
    global_job_array_0[1,1].printInfo();


}