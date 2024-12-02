package main

import {
    fmt;
    debug;
}

typedef class Job {
    field bool    Running;
    field int     JobID;
    field double  Score;
    field string  Name;
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
        fmt::println_string(global_job_array_0[index].Name);
        debug::assert(global_job_array_0[index].Running == false);
        debug::assert(global_job_array_0[index].JobID   == 0);
        debug::assert(global_job_array_0[index].Score   == 0.0);
        debug::assert(global_job_array_0[index].Name    == "");
    }


    fmt::println_string("\ntest cast 2 ------------------------");
    global_job_array_0[0].Running = false;
    global_job_array_0[0].JobID   = 0;
    global_job_array_0[0].Score   = 0.0;
    global_job_array_0[0].Name    = "a";

    global_job_array_0[1].Running = true;
    global_job_array_0[1].JobID   = 1;
    global_job_array_0[1].Score   = 11.11;
    global_job_array_0[1].Name    = "b";

    global_job_array_0[2].Running = true;
    global_job_array_0[2].JobID   = 2;
    global_job_array_0[2].Score   = 22.22;
    global_job_array_0[2].Name    = "c";

    global_job_array_0[3].Running = true;
    global_job_array_0[3].JobID   = 3;
    global_job_array_0[3].Score   = 33.33;
    global_job_array_0[3].Name    = "d";

    global_job_array_0[4].Running = true;
    global_job_array_0[4].JobID   = 4;
    global_job_array_0[4].Score   = 44.44;
    global_job_array_0[4].Name    = "e";



    fmt::println_string("\ntest cast global_job_array_0[0] ------------------------");
    debug::assert(global_job_array_0[0].Running == false);
    debug::assert(global_job_array_0[0].JobID   == 0);
    debug::assert(global_job_array_0[0].Score   == 0.0);
    debug::assert(global_job_array_0[0].Name    == "a");

    fmt::println_string("\ntest cast global_job_array_0[1] ------------------------");
    debug::assert(global_job_array_0[1].Running == true);
    debug::assert(global_job_array_0[1].JobID   == 1);
    debug::assert(global_job_array_0[1].Score   == 11.11);
    debug::assert(global_job_array_0[1].Name    == "b");

    fmt::println_string("\ntest cast global_job_array_0[2] ------------------------");
    debug::assert(global_job_array_0[2].Running == true);
    debug::assert(global_job_array_0[2].JobID   == 2);
    debug::assert(global_job_array_0[2].Score   == 22.22);
    debug::assert(global_job_array_0[2].Name    == "c");

    fmt::println_string("\ntest cast global_job_array_0[3] ------------------------");
    debug::assert(global_job_array_0[3].Running == true);
    debug::assert(global_job_array_0[3].JobID   == 3);
    debug::assert(global_job_array_0[3].Score   == 33.33);
    debug::assert(global_job_array_0[3].Name    == "d");

    fmt::println_string("\ntest cast global_job_array_0[4] ------------------------");
    debug::assert(global_job_array_0[4].Running == true);
    debug::assert(global_job_array_0[4].JobID   == 4);
    debug::assert(global_job_array_0[4].Score   == 44.44);
    debug::assert(global_job_array_0[4].Name    == "e");


}
