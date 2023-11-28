package main

import {
    fmt;
    debug;
}

typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;
}

global {
    var Job[] global_job_array_0;

    var Job global_job_value_0;
}

@main
function main() {
    global_job_array_0 = new Job[5];


    fmt::println_string("test cast 1 ------------------------");
    var int index = 0;
    for(index = 0; index < 5; index = index + 1) {
        fmt::println_bool(global_job_array_0[index].Running);
        fmt::println_int(global_job_array_0[index].JobID);
        fmt::println_double(global_job_array_0[index].Score);
        debug::debug_assert(global_job_array_0[index].Running == false);
        debug::debug_assert(global_job_array_0[index].JobID   == 0);
        debug::debug_assert(global_job_array_0[index].Score   == 0.0);
    }


    fmt::println_string("\ntest cast 2 ------------------------");
    global_job_value_0  = Job{
        Running:  false,
        JobID:    0,
        Score:    0.0
    };
    global_job_array_0[0] = global_job_value_0;

    global_job_value_0  = Job{
        Running:  true,
        JobID:    1,
        Score:    11.11
    };
    global_job_array_0[1] = global_job_value_0;

    global_job_value_0  = Job{
        Running:  true,
        JobID:    2,
        Score:    22.22
    };
    global_job_array_0[2] = global_job_value_0;

    global_job_value_0  = Job{
        Running:  true,
        JobID:    3,
        Score:    33.33
    };
    global_job_array_0[3] = global_job_value_0;

    global_job_value_0  = Job{
        Running:  true,
        JobID:    4,
        Score:    44.44
    };
    global_job_array_0[4] = global_job_value_0;



    fmt::println_string("\ntest cast global_job_array_0[0] ------------------------");
    debug::debug_assert(global_job_array_0[0].Running == false);
    debug::debug_assert(global_job_array_0[0].JobID   == 0);
    debug::debug_assert(global_job_array_0[0].Score   == 0.0);

    fmt::println_string("\ntest cast global_job_array_0[1] ------------------------");
    debug::debug_assert(global_job_array_0[1].Running == true);
    debug::debug_assert(global_job_array_0[1].JobID   == 1);
    debug::debug_assert(global_job_array_0[1].Score   == 11.11);

    fmt::println_string("\ntest cast global_job_array_0[2] ------------------------");
    debug::debug_assert(global_job_array_0[2].Running == true);
    debug::debug_assert(global_job_array_0[2].JobID   == 2);
    debug::debug_assert(global_job_array_0[2].Score   == 22.22);

    fmt::println_string("\ntest cast global_job_array_0[3] ------------------------");
    debug::debug_assert(global_job_array_0[3].Running == true);
    debug::debug_assert(global_job_array_0[3].JobID   == 3);
    debug::debug_assert(global_job_array_0[3].Score   == 33.33);

    fmt::println_string("\ntest cast global_job_array_0[4] ------------------------");
    debug::debug_assert(global_job_array_0[4].Running == true);
    debug::debug_assert(global_job_array_0[4].JobID   == 4);
    debug::debug_assert(global_job_array_0[4].Score   == 44.44);


}
