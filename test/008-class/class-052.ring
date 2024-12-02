
package main

import {
	fmt;
	debug;
}


typedef class Job1 {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;
    field Job2    Job2;

    method printInfo() {
        fmt::printf("Job1({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
    }
    method returnSelf() -> (Job1) {
        return self;
    }
}

typedef class Job2 {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;
    field Job3    Job3;

    method printInfo() {
        fmt::printf("Job2({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
    }
    method returnSelf() -> (Job2) {
        return self;
    }
}

typedef class Job3 {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;
    field Job4    Job4;

    method printInfo() {
        fmt::printf("Job3({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
    }
    method returnSelf() -> (Job3) {
        return self;
    }
}

typedef class Job4 {
    field bool    Bool;
    field int     Int;
    field double  Double;
    field string  String;

    method printInfo() {
        fmt::printf("Job4({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
    }
    method returnSelf() -> (Job4) {
        return self;
    }
}


function copyJob1(var Job1 job) -> (Job1) {
    return job;
}

function copyJob2(var Job1 job) -> (Job2) {
    return job;
}

function copyJob3(var Job1 job) -> (Job3) {
    return job;
}

function copyJob4(var Job1 job) -> (Job4) {
    return job;
}


global {
    var Job1 job_1;
    var Job2 job_2;
    var Job3 job_3;
    var Job4 job_4;
}

// TestDetail: class有4级嵌套
// TestDetail: 测试对象嵌套的初始化
// TestDetail: 测试嵌套访问method

@main
function main() {

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

    fmt::println_string("\ntest case 3-------");
    job_1.printInfo();
    job_1.Job2.printInfo();
    job_1.Job2.Job3.printInfo();
    job_1.Job2.Job3.Job4.printInfo();




    fmt::println_string("\ntest case 4-1-------");
    job_1.printInfo();
    copyJob1(job_1).printInfo();
    copyJob1(job_1).returnSelf().printInfo();
    copyJob1(job_1.returnSelf()).printInfo();


    fmt::println_string("\ntest case 4-2-------");
    job_1.Job2.printInfo();
    copyJob2(job_1.Job2).printInfo();
    copyJob2(job_1.Job2.returnSelf()).printInfo();
    copyJob2(job_1.Job2.returnSelf()).returnSelf().printInfo();
    copyJob2(copyJob1(job_1).Job2.returnSelf()).returnSelf().printInfo();
    copyJob2(copyJob1(job_1).returnSelf().Job2.returnSelf()).returnSelf().printInfo();

    fmt::println_string("\ntest case 4-3-------");
    job_1.Job2.Job3.printInfo();
    copyJob3(job_1.Job2.Job3).printInfo();
    copyJob3(job_1.Job2.Job3.returnSelf().returnSelf().returnSelf()).printInfo();
    // job_1.returnSelf().Job2.Job3.printInfo();
    // job_1.Job2.returnSelf().Job3.printInfo();
    // job_1.Job2.Job3.returnSelf().printInfo();
    // job_1.returnSelf().Job2.returnSelf().Job3.returnSelf().printInfo();


    fmt::println_string("\ntest case 4-4-------");
    job_1.Job2.Job3.Job4.printInfo();
    copyJob4(
        copyJob3(
            copyJob2(
                copyJob1(job_1).Job2
                ).Job3
            ).Job4
        ).printInfo();
    // job_1.returnSelf().returnSelf().Job2.returnSelf().returnSelf().Job3.returnSelf().returnSelf().Job4.returnSelf().returnSelf().printInfo();

}