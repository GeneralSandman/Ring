
package main

import {
	fmt;
	debug;
}



typedef class Job1 {
    var bool    Running1;
}

typedef class Job2 {
    var bool    Running2;
    var int     JobID2;
}

typedef class Job3 {
    var bool    Running3;
    var int     JobID3;
    var double  Score3;
}


global {
    var Job1 global_job1_value_0;

    var Job2 global_job2_value_0;

    var Job3 global_job3_value_0;
}

fn main() {


    fmt::println_string("\ntest case 1");

    fmt::println_bool(global_job1_value_0.Running1);
    debug::assert(global_job1_value_0.Running1 == false);

    fmt::println_bool(global_job2_value_0.Running2);
    fmt::println_int(global_job2_value_0.JobID2);
    debug::assert(global_job2_value_0.Running2 == false);
    debug::assert(global_job2_value_0.JobID2 == 0);

    fmt::println_bool(global_job3_value_0.Running3);
    fmt::println_int(global_job3_value_0.JobID3);
    fmt::println_double(global_job3_value_0.Score3);
    debug::assert(global_job3_value_0.Running3 == false);
    debug::assert(global_job3_value_0.JobID3 == 0);
    debug::assert(global_job3_value_0.Score3 == 0.0);



    fmt::println_string("\ntest case 2");

    global_job1_value_0 = Job1{
        Running1: true
    };

    global_job2_value_0 = Job2{
        Running2: true,
        JobID2: 2
    };

    global_job3_value_0 = Job3{
        Running3: true,
        JobID3: 3, 
        Score3: 3.3
    };

    fmt::println_bool(global_job1_value_0.Running1);
    debug::assert(global_job1_value_0.Running1 == true);

    fmt::println_bool(global_job2_value_0.Running2);
    fmt::println_int(global_job2_value_0.JobID2);
    debug::assert(global_job2_value_0.Running2 == true);
    debug::assert(global_job2_value_0.JobID2 == 2);

    fmt::println_bool(global_job3_value_0.Running3);
    fmt::println_int(global_job3_value_0.JobID3);
    fmt::println_double(global_job3_value_0.Score3);
    debug::assert(global_job3_value_0.Running3 == true);
    debug::assert(global_job3_value_0.JobID3 == 3);
    debug::assert(global_job3_value_0.Score3 == 3.3);




    fmt::println_string("\ntest case 3");

    global_job1_value_0 = Job1{
        Running1: false
    };

    global_job2_value_0 = Job2{
        Running2: false,
        JobID2: 222
    };

    global_job3_value_0 = Job3{
        Running3: false,
        JobID3: 333, 
        Score3: 333.333
    };

    fmt::println_bool(global_job1_value_0.Running1);
    debug::assert(global_job1_value_0.Running1 == false);

    fmt::println_bool(global_job2_value_0.Running2);
    fmt::println_int(global_job2_value_0.JobID2);
    debug::assert(global_job2_value_0.Running2 == false);
    debug::assert(global_job2_value_0.JobID2 == 222);

    fmt::println_bool(global_job3_value_0.Running3);
    fmt::println_int(global_job3_value_0.JobID3);
    fmt::println_double(global_job3_value_0.Score3);
    debug::assert(global_job3_value_0.Running3 == false);
    debug::assert(global_job3_value_0.JobID3 == 333);
    debug::assert(global_job3_value_0.Score3 == 333.333);



}