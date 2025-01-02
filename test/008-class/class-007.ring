
package main

import {
	fmt;
	debug;
}

// TestDetail: Class定义的嵌套
// TestDetail: 测试Class A 中的field为Class B
// TestDetail: Class A, Class B中的field 均存在 bool/int/double/string


typedef class Runner {
    var bool    Valid;
    var int     RunnerID;
    var double  UseTime;
    var string  RName;
}


typedef class Job {
    var bool    Running;
    var int     JobID;
    var double  Score;
    var string  Name;
    var Runner  Runner;
}

global {
    var Job    job_0;
    var Runner global_runner_value_0;
    var Runner global_runner_value_1;
}


fn main() {


    global_runner_value_0 = Runner{
        Valid: true,
        RunnerID: 2,
        UseTime: 2.2,
        RName: "2.2"
    };
    job_0 = Job{
        Running: false,
        JobID: 1, 
        Score: 1.1,
        Name: "1.1",
        Runner: global_runner_value_0
    };

    fmt::println_string("test case 1");
    fmt::println_bool(job_0.Running);
    fmt::println_int(job_0.JobID);
    fmt::println_double(job_0.Score);
    fmt::println_string(job_0.Name);
    fmt::println_bool(job_0.Runner.Valid);
    fmt::println_int(job_0.Runner.RunnerID);
    fmt::println_double(job_0.Runner.UseTime);
    fmt::println_string(job_0.Runner.RName);

    debug::assert(job_0.Running == false);
    debug::assert(job_0.JobID   == 1);
    debug::assert(job_0.Score   == 1.1);
    debug::assert(job_0.Name    == "1.1");
    debug::assert(job_0.Runner.Valid      == true);
    debug::assert(job_0.Runner.RunnerID   == 2);
    debug::assert(job_0.Runner.UseTime    == 2.2);
    debug::assert(job_0.Runner.RName      == "2.2");



    fmt::println_string("\ntest case 2");

    global_runner_value_1 = job_0.Runner;

    fmt::println_bool(global_runner_value_1.Valid);
    fmt::println_int(global_runner_value_1.RunnerID);
    fmt::println_double(global_runner_value_1.UseTime);
    fmt::println_string(global_runner_value_1.RName);

    debug::assert(global_runner_value_1.Valid      == true);
    debug::assert(global_runner_value_1.RunnerID   == 2);
    debug::assert(global_runner_value_1.UseTime    == 2.2);
    debug::assert(global_runner_value_1.RName      == "2.2");






}