
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
// TestDetail: 一个个初始化
// TestDetail: 并通过一行多项赋值 翻转
fn main() {
    global_job_array_0 = new Job[10];

    global_job_array_0[0].Bool   = true;
    global_job_array_0[0].Int    = 0;
    global_job_array_0[0].Double = 0.0;
    global_job_array_0[0].String = "0";

    global_job_array_0[1].Bool   = false;
    global_job_array_0[1].Int    = 1;
    global_job_array_0[1].Double = 1.0;
    global_job_array_0[1].String = "1";

    global_job_array_0[2].Bool   = true;
    global_job_array_0[2].Int    = 2;
    global_job_array_0[2].Double = 2.0;
    global_job_array_0[2].String = "2";

    global_job_array_0[3].Bool   = false;
    global_job_array_0[3].Int    = 3;
    global_job_array_0[3].Double = 3.0;
    global_job_array_0[3].String = "3";

    global_job_array_0[4].Bool   = true;
    global_job_array_0[4].Int    = 4;
    global_job_array_0[4].Double = 4.0;
    global_job_array_0[4].String = "4";

    global_job_array_0[5].Bool   = false;
    global_job_array_0[5].Int    = 5;
    global_job_array_0[5].Double = 5.0;
    global_job_array_0[5].String = "5";

    global_job_array_0[6].Bool   = true;
    global_job_array_0[6].Int    = 6;
    global_job_array_0[6].Double = 6.0;
    global_job_array_0[6].String = "6";

    global_job_array_0[7].Bool   = false;
    global_job_array_0[7].Int    = 7;
    global_job_array_0[7].Double = 7.0;
    global_job_array_0[7].String = "7";

    global_job_array_0[8].Bool   = true;
    global_job_array_0[8].Int    = 8;
    global_job_array_0[8].Double = 8.0;
    global_job_array_0[8].String = "8";

    global_job_array_0[9].Bool   = false;
    global_job_array_0[9].Int    = 9;
    global_job_array_0[9].Double = 9.0;
    global_job_array_0[9].String = "9";




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
    for(local_job_value in range global_job_array_0) {
        local_job_value.printInfo();
    }

}