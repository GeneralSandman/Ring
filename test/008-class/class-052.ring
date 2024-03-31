
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

    job_1.returnSelf().Job2;
    // job_1.returnSelf().Job2.Job3.returnSelf().Job4.printInfo();



}