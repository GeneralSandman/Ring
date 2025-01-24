
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
    var Job[] global_job_array_0;
}

// TestDetail: 数组的元素为 class-obect
// TestDetail: 直接通过索引对数组元素中的成员赋值
fn main() {

    global_job_array_0 = new Job[4];
    global_job_array_0[0] = Job{
        Bool:   true,
        Int:    0,
        Double: 0.0,
        String: "job-0",
    };
    global_job_array_0[1] = Job{
        Bool:   false,
        Int:    1,
        Double: 1.0,
        String: "job-1",
    };
    global_job_array_0[2] = Job{
        Bool:   true,
        Int:    2,
        Double: 2.0,
        String: "job-2",
    };

    global_job_array_0[3] = Job{
        Bool:   false,
        Int:    3,
        Double: 3.0,
        String: "job-3",
    };


    fmt::println_string("test case 1");
    global_job_array_0[0].printInfo();
    global_job_array_0[1].printInfo();
    global_job_array_0[2].printInfo();
    global_job_array_0[3].printInfo();


    fmt::println_string("\ntest case 2");
    global_job_array_0[0].Int ++;
    global_job_array_0[1].Int ++;
    global_job_array_0[2].Int ++;
    global_job_array_0[3].Int ++;

    global_job_array_0[0].String = global_job_array_0[0].String .. "-test";
    global_job_array_0[1].String = global_job_array_0[1].String .. "-test";
    global_job_array_0[2].String = global_job_array_0[2].String .. "-test";
    global_job_array_0[3].String = global_job_array_0[3].String .. "-test";

    global_job_array_0[0].printInfo();
    global_job_array_0[1].printInfo();
    global_job_array_0[2].printInfo();
    global_job_array_0[3].printInfo();


}