
package main

import {
	fmt;
	debug;
}

// TestDetail: 与 class-0007.ring 大致相同
// TestDetail: 测试 new ClassObject常量时，Field初始化的顺序可以任意顺序


typedef class Runner {
    field bool    Valid;
    field int     RunnerID;
    field double  UseTime;
    field string  RName;
}


typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;
    field string  Name;
    field Runner  Runner;
}

global {
    var Job    job_0;
    var Runner global_runner_value_0;
    var Runner global_runner_value_1;
}


@main
function main() {


    global_runner_value_0 = Runner{
        RName: "2.2",
        UseTime: 2.2,
        RunnerID: 2,
        Valid: true
    };
    job_0 = Job{
        Runner: global_runner_value_0,
        Name: "1.1",
        Score: 1.1,
        JobID: 1, 
        Running: false
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

    debug::debug_assert(job_0.Running == false);
    debug::debug_assert(job_0.JobID   == 1);
    debug::debug_assert(job_0.Score   == 1.1);
    debug::debug_assert(job_0.Name    == "1.1");
    debug::debug_assert(job_0.Runner.Valid      == true);
    debug::debug_assert(job_0.Runner.RunnerID   == 2);
    debug::debug_assert(job_0.Runner.UseTime    == 2.2);
    debug::debug_assert(job_0.Runner.RName      == "2.2");



    fmt::println_string("\ntest case 2");

    global_runner_value_1 = job_0.Runner;

    fmt::println_bool(global_runner_value_1.Valid);
    fmt::println_int(global_runner_value_1.RunnerID);
    fmt::println_double(global_runner_value_1.UseTime);
    fmt::println_string(global_runner_value_1.RName);

    debug::debug_assert(global_runner_value_1.Valid      == true);
    debug::debug_assert(global_runner_value_1.RunnerID   == 2);
    debug::debug_assert(global_runner_value_1.UseTime    == 2.2);
    debug::debug_assert(global_runner_value_1.RName      == "2.2");






}