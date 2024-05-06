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
}

// TestDetail:测试可变参数
// TestDetail:可变参数为 Job... 类型
@main
function main() {
    fmt::println_string("test case 1--------");
    func_variadic_parameter(
        Job{
            Bool:      true,
            Int:       0, 
            Double:    0.0,
            String:    "",
        }
    );

    fmt::println_string("\ntest case 2--------");
    func_variadic_parameter(
        Job{
            Bool:      true,
            Int:       0, 
            Double:    0.0,
            String:    "",
        },
        Job{
            Bool:      false,
            Int:       1, 
            Double:    1.1,
            String:    "#1",
        }
    );


    fmt::println_string("\ntest case 3--------");
    func_variadic_parameter(
        Job{
            Bool:      true,
            Int:       0, 
            Double:    0.0,
            String:    "",
        },
        Job{
            Bool:      false,
            Int:       1, 
            Double:    1.1,
            String:    "#1",
        },
        Job{
            Bool:      true,
            Int:       2, 
            Double:    2.2,
            String:    "#2",
        }
    );


    fmt::println_string("\ntest case 4--------");
    func_variadic_parameter(
        Job{
            Bool:      true,
            Int:       0, 
            Double:    0.0,
            String:    "",
        },
        Job{
            Bool:      false,
            Int:       1, 
            Double:    1.1,
            String:    "#1",
        },
        Job{
            Bool:      true,
            Int:       2, 
            Double:    2.2,
            String:    "#2",
        },
        Job{
            Bool:      false,
            Int:       3, 
            Double:    3.3,
            String:    "#3",
        }
    );
}


function func_variadic_parameter(var Job... array_value) {
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));

    var Job job_value;
    for(job_value in range array_value) {
        job_value.printInfo();
    }
}
