
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
// TestDetail: 根据class-object 内的field进行排序
@main
function main() {

    // global_job_array_0 = new Job[2];

    // global_job_array_0[0].Int = 1;
    // global_job_array_0[1].Int = 2;

    global_job_array_0[0], global_job_array_0[1] = global_job_array_0[1], global_job_array_0[0];
    // global_job_array_0[0].Int, global_job_array_0[1].Int = global_job_array_0[1].Int, global_job_array_0[0].Int;

    // global_job_array_0[0].printInfo();
    // global_job_array_0[1].printInfo();

}