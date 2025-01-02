
package main

import {
	fmt;
	debug;
}


typedef class Job1 {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;
    var Job2    Job2;
}

typedef class Job2 {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;
    var Job3    Job3;
}

typedef class Job3 {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;
    var Job4    Job4;
}

typedef class Job4 {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;
}


global {
    var Job1 job_1;
    var Job2 job_2;
    var Job3 job_3;
    var Job4 job_4;
}

// TestDetail: class有4级嵌套
// TestDetail: 测试对象嵌套的初始化

fn main() {

    // 测试 class field的默认值
    fmt::println_string("test case 1-------");

    debug::assert(job_1.Bool                  == false);
    debug::assert(job_1.Int                   == 0);
    debug::assert(job_1.Double                == 0.0);
    debug::assert(job_1.String                == "");

    debug::assert(job_1.Job2.Bool             == false);
    debug::assert(job_1.Job2.Int              == 0);
    debug::assert(job_1.Job2.Double           == 0.0);
    debug::assert(job_1.Job2.String           == "");

    debug::assert(job_1.Job2.Job3.Bool        == false);
    debug::assert(job_1.Job2.Job3.Int         == 0);
    debug::assert(job_1.Job2.Job3.Double      == 0.0);
    debug::assert(job_1.Job2.Job3.String      == "");

    debug::assert(job_1.Job2.Job3.Job4.Bool   == false);
    debug::assert(job_1.Job2.Job3.Job4.Int    == 0);
    debug::assert(job_1.Job2.Job3.Job4.Double == 0.0);
    debug::assert(job_1.Job2.Job3.Job4.String == "");


    // 测试 对象嵌套初始化
    fmt::println_string("\ntest case 2-------");
    job_1 = Job1{
        Bool:   false,
        Int:    1,
        Double: 1.1,
        String: "1.1",
        Job2:   Job2{
            Bool:   true,
            Int:    2,
            Double: 2.2,
            String: "2.2",
            Job3:   Job3{
                Bool:   false,
                Int:    3,
                Double: 3.3,
                String: "3.3",
                Job4:   Job4{
                    Bool:   true,
                    Int:    4,
                    Double: 4.4,
                    String: "4.4"
                }
            }
        }
    };

    debug::assert(job_1.Bool                  == false);
    debug::assert(job_1.Int                   == 1);
    debug::assert(job_1.Double                == 1.1);
    debug::assert(job_1.String                == "1.1");

    debug::assert(job_1.Job2.Bool             == true);
    debug::assert(job_1.Job2.Int              == 2);
    debug::assert(job_1.Job2.Double           == 2.2);
    debug::assert(job_1.Job2.String           == "2.2");

    debug::assert(job_1.Job2.Job3.Bool        == false);
    debug::assert(job_1.Job2.Job3.Int         == 3);
    debug::assert(job_1.Job2.Job3.Double      == 3.3);
    debug::assert(job_1.Job2.Job3.String      == "3.3");

    debug::assert(job_1.Job2.Job3.Job4.Bool   == true);
    debug::assert(job_1.Job2.Job3.Job4.Int    == 4);
    debug::assert(job_1.Job2.Job3.Job4.Double == 4.4);
    debug::assert(job_1.Job2.Job3.Job4.String == "4.4");

}