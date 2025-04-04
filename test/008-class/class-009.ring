
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
    var Runner  Runner;


    var bool[]    BoolArray;
    var int[]     IntArray;
    var double[]  DoubleArray;
    var string[]  StringArray;
    var Runner[]  RunnerArray;
}

typedef Runner = class {
    var bool    Bool;
    var int     Int;
    var double  Double;
    var string  String;
}

global {
    var Job job_0;
    var Runner global_runner_value_0;
}

// TestDetail: class中field支持数组

fn main() {

    // 测试 class field的默认值
    fmt::println_string("test case 1-------");

    debug::assert(job_0.Bool          == false);
    debug::assert(job_0.Int           == 0);
    debug::assert(job_0.Double        == 0.0);
    debug::assert(job_0.String        == "");
    debug::assert(job_0.Runner.Bool   == false);
    debug::assert(job_0.Runner.Int    == 0);
    debug::assert(job_0.Runner.Double == 0.0);
    debug::assert(job_0.Runner.String == "");

    debug::assert(len(job_0.BoolArray)        == 0);
    debug::assert(len(job_0.IntArray)         == 0);
    debug::assert(len(job_0.DoubleArray)      == 0);
    debug::assert(len(job_0.StringArray)      == 0);
    debug::assert(len(job_0.RunnerArray)      == 0);
    debug::assert(cap(job_0.BoolArray)   == 0);
    debug::assert(cap(job_0.IntArray)    == 0);
    debug::assert(cap(job_0.DoubleArray) == 0);
    debug::assert(cap(job_0.StringArray) == 0);
    debug::assert(cap(job_0.RunnerArray) == 0);


    // 测试给class中的field赋值
    fmt::println_string("\ntest case 2-------");
    global_runner_value_0 = Runner{
        String: "2.2",
        Double: 2.2,
        Int:    2,
        Bool:   true
    };

    job_0.Bool      = true;
    job_0.Int       = 1;
    job_0.Double    = 1.1;
    job_0.String    = "1.1";
    job_0.Runner    = global_runner_value_0;
    job_0.BoolArray = new bool[1];
    job_0.IntArray  = new int[2];
    job_0.DoubleArray = new double[3];
    job_0.StringArray = new string[4];
    job_0.RunnerArray = new Runner[5];



    debug::assert(job_0.Bool          == true);
    debug::assert(job_0.Int           == 1);
    debug::assert(job_0.Double        == 1.1);
    debug::assert(job_0.String        == "1.1");
    debug::assert(job_0.Runner.Bool   == true);
    debug::assert(job_0.Runner.Int    == 2);
    debug::assert(job_0.Runner.Double == 2.2);
    debug::assert(job_0.Runner.String == "2.2");

    debug::assert(len(job_0.BoolArray)        == 1);
    debug::assert(len(job_0.IntArray)         == 2);
    debug::assert(len(job_0.DoubleArray)      == 3);
    debug::assert(len(job_0.StringArray)      == 4);
    debug::assert(len(job_0.RunnerArray)      == 5);
    debug::assert(cap(job_0.BoolArray)   == 8);
    debug::assert(cap(job_0.IntArray)    == 8);
    debug::assert(cap(job_0.DoubleArray) == 8);
    debug::assert(cap(job_0.StringArray) == 8);
    debug::assert(cap(job_0.RunnerArray) == 8);


    
    fmt::println_string("\ntest case 3-------");
    global_runner_value_0 = Runner{
        String: "78.98",
        Double: 78.98,
        Int:    78,
        Bool:   true
    };

    job_0 = Job{
        Bool:      true,
        Int:       5, 
        Double:    5.5,
        String:    "5",
        Runner:    global_runner_value_0,

        BoolArray:      new bool[1],
        IntArray:       new int[2],
        DoubleArray:    new double[3],
        StringArray:    new string[4],
        RunnerArray:    new Runner[5]
    };


    debug::assert(job_0.Bool          == true);
    debug::assert(job_0.Int           == 5);
    debug::assert(job_0.Double        == 5.5);
    debug::assert(job_0.String        == "5");
    debug::assert(job_0.Runner.Bool   == true);
    debug::assert(job_0.Runner.Int    == 78);
    debug::assert(job_0.Runner.Double == 78.98);
    debug::assert(job_0.Runner.String == "78.98");

    debug::assert(len(job_0.BoolArray)        == 1);
    debug::assert(len(job_0.IntArray)         == 2);
    debug::assert(len(job_0.DoubleArray)      == 3);
    debug::assert(len(job_0.StringArray)      == 4);
    debug::assert(len(job_0.RunnerArray)      == 5);
    debug::assert(cap(job_0.BoolArray)   == 8);
    debug::assert(cap(job_0.IntArray)    == 8);
    debug::assert(cap(job_0.DoubleArray) == 8);
    debug::assert(cap(job_0.StringArray) == 8);
    debug::assert(cap(job_0.RunnerArray) == 8);

}

    // fmt::println_bool(job_0.Bool);
    // fmt::println_int(job_0.Int);
    // fmt::println_double(job_0.Double);
    // fmt::println_string(job_0.String);
    // fmt::println_bool(job_0.Runner.Bool);
    // fmt::println_int(job_0.Runner.Int);
    // fmt::println_double(job_0.Runner.Double);
    // fmt::println_string(job_0.Runner.String);

    // fmt::println_int(len(job_0.BoolArray));
    // fmt::println_int(len(job_0.IntArray));
    // fmt::println_int(len(job_0.DoubleArray));
    // fmt::println_int(len(job_0.StringArray));
    // fmt::println_int(len(job_0.RunnerArray));
    // fmt::println_int(cap(job_0.BoolArray));
    // fmt::println_int(cap(job_0.IntArray));
    // fmt::println_int(cap(job_0.DoubleArray));
    // fmt::println_int(cap(job_0.StringArray));
    // fmt::println_int(cap(job_0.RunnerArray));