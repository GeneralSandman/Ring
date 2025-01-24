
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
    var Job global_job_0;
    var Job global_job_1;
    var Job global_job_2;
    var Job global_job_3;
    var Job global_job_4;
    var Job global_job_5;
    var Job global_job_6;
    var Job global_job_7;
    var Job global_job_8;
    var Job global_job_9;
}

// TestDetail: 交换两个class-object的变量数值, 通过多项赋值直接操作, 不需要中间变量
// TestDetail: 与 上个测试用例不同, 一个一个的交换成员变量
// TestDetail: Code:
// TestDetail: `global_job_0.Bool,   global_job_1.Bool   = global_job_1.Bool,   global_job_0.Bool;`
// TestDetail: `global_job_0.Int,    global_job_1.Int    = global_job_1.Int,    global_job_0.Int;`
// TestDetail: `global_job_0.Double, global_job_1.Double = global_job_1.Double, global_job_0.Double;`
// TestDetail: `global_job_0.String, global_job_1.String = global_job_1.String, global_job_0.String;`

fn main() {

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
    global_job_4 = Job{
        Bool:   true,
        Int:    4,
        Double: 4.0,
        String: "4",
    };
    global_job_5 = Job{
        Bool:   false,
        Int:    5,
        Double: 5.0,
        String: "5",
    };
    global_job_6 = Job{
        Bool:   true,
        Int:    6,
        Double: 6.0,
        String: "6",
    };
    global_job_7 = Job{
        Bool:   false,
        Int:    7,
        Double: 7.0,
        String: "7",
    };
    global_job_8 = Job{
        Bool:   true,
        Int:    8,
        Double: 8.0,
        String: "8",
    };
    global_job_9 = Job{
        Bool:   false,
        Int:    9,
        Double: 9.0,
        String: "9",
    };

    
    fmt::println_string("test case 1-------");
    global_job_0.printInfo();
    global_job_1.printInfo();
    global_job_2.printInfo();
    global_job_3.printInfo();
    global_job_4.printInfo();
    global_job_5.printInfo();
    global_job_6.printInfo();
    global_job_7.printInfo();
    global_job_8.printInfo();
    global_job_9.printInfo();



    fmt::println_string("\ntest case 2-------");
    // 等效于 global_job_0, global_job_1 = global_job_1, global_job_0;
    global_job_0.Bool,   global_job_1.Bool   = global_job_1.Bool,   global_job_0.Bool;
    global_job_0.Int,    global_job_1.Int    = global_job_1.Int,    global_job_0.Int;
    global_job_0.Double, global_job_1.Double = global_job_1.Double, global_job_0.Double;
    global_job_0.String, global_job_1.String = global_job_1.String, global_job_0.String;

    // 等效于 global_job_2, global_job_3 = global_job_3, global_job_2;
    global_job_2.Bool,   global_job_3.Bool   = global_job_3.Bool,   global_job_2.Bool;
    global_job_2.Int,    global_job_3.Int    = global_job_3.Int,    global_job_2.Int;
    global_job_2.Double, global_job_3.Double = global_job_3.Double, global_job_2.Double;
    global_job_2.String, global_job_3.String = global_job_3.String, global_job_2.String;

    // 等效于 global_job_4, global_job_5 = global_job_5, global_job_4;
    global_job_4.Bool,   global_job_5.Bool   = global_job_5.Bool,   global_job_4.Bool;
    global_job_4.Int,    global_job_5.Int    = global_job_5.Int,    global_job_4.Int;
    global_job_4.Double, global_job_5.Double = global_job_5.Double, global_job_4.Double;
    global_job_4.String, global_job_5.String = global_job_5.String, global_job_4.String;

    // 等效于 global_job_6, global_job_7 = global_job_7, global_job_6;
    global_job_6.Bool,   global_job_7.Bool   = global_job_7.Bool,   global_job_6.Bool;
    global_job_6.Int,    global_job_7.Int    = global_job_7.Int,    global_job_6.Int;
    global_job_6.Double, global_job_7.Double = global_job_7.Double, global_job_6.Double;
    global_job_6.String, global_job_7.String = global_job_7.String, global_job_6.String;

    // 等效于 global_job_8, global_job_9 = global_job_9, global_job_8;
    global_job_8.Bool,   global_job_9.Bool   = global_job_9.Bool,   global_job_8.Bool;
    global_job_8.Int,    global_job_9.Int    = global_job_9.Int,    global_job_8.Int;
    global_job_8.Double, global_job_9.Double = global_job_9.Double, global_job_8.Double;
    global_job_8.String, global_job_9.String = global_job_9.String, global_job_8.String;

    

    global_job_0.printInfo();
    global_job_1.printInfo();
    global_job_2.printInfo();
    global_job_3.printInfo();
    global_job_4.printInfo();
    global_job_5.printInfo();
    global_job_6.printInfo();
    global_job_7.printInfo();
    global_job_8.printInfo();
    global_job_9.printInfo();





}