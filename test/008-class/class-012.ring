
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
    var Job global_job_0;
    var Job global_job_1;
    var Job global_job_2;
    var Job global_job_3;
}

// TestDetail: 交换两个class-object的变量数值
// TestDetail: job_0, job_1 = job_1, job_0;
@main
function main() {

    global_job_0 = Job{
        Bool:   true,
        Int:    0,
        Double: 0.0,
        String: "0",
    };

    global_job_1 = Job{
        Bool:   false,
        Int:    1,
        Double: 1.0,
        String: "1",
    };

    global_job_2 = Job{
        Bool:   true,
        Int:    2,
        Double: 2.0,
        String: "2",
    };

    global_job_3 = Job{
        Bool:   false,
        Int:    3,
        Double: 3.0,
        String: "3",
    };

    fmt::println_string("test case 1-------");
    global_job_0.printInfo();
    global_job_1.printInfo();
    global_job_2.printInfo();
    global_job_3.printInfo();



    fmt::println_string("\ntest case 2-------");
    global_job_0, global_job_1 = global_job_1, global_job_0;
    global_job_2, global_job_3 = global_job_3, global_job_2;

    global_job_0.printInfo();
    global_job_1.printInfo();
    global_job_2.printInfo();
    global_job_3.printInfo();





}