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
    var Job[,,,,,,,] global_job_array_0;
}

// TestDetail: 测试八维数组，数组元素为class

@main
function main() {
    global_job_array_0 = new Job[1,2,3,4,5,6,7,8];

    fmt::println_string("test cast 1 ------------------------");
    debug::debug_assert(len(global_job_array_0) == 1);
    debug::debug_assert(len(global_job_array_0[0]) == 2);
    debug::debug_assert(len(global_job_array_0[0,0]) == 3);
    debug::debug_assert(len(global_job_array_0[0,0,0]) == 4);
    debug::debug_assert(len(global_job_array_0[0,0,0,0]) == 5);
    debug::debug_assert(len(global_job_array_0[0,0,0,0,0]) == 6);
    debug::debug_assert(len(global_job_array_0[0,0,0,0,0,0]) == 7);
    debug::debug_assert(len(global_job_array_0[0,0,0,0,0,0,0]) == 8);
    

    var int a;
    var int b;
    var int c;
    var int d;
    var int e;
    var int f;
    var int g;
    var int h;
    var int num;

    fmt::println_string("\ntest cast 2 ------------------------");

    for(a = 0; a < len(global_job_array_0); a = a + 1) {
        for(b = 0; b < len(global_job_array_0[a]); b = b + 1) {
            for(c = 0; c < len(global_job_array_0[a,b]); c = c + 1) {
                for(d = 0; d < len(global_job_array_0[a,b,c]); d = d + 1) {
                    for(e = 0; e < len(global_job_array_0[a,b,c,d]); e = e + 1) {
                        for(f = 0; f < len(global_job_array_0[a,b,c,d,e]); f = f + 1) {
                            for(g = 0; g < len(global_job_array_0[a,b,c,d,e,f]); g = g + 1) {
                                for(h = 0; h < len(global_job_array_0[a,b,c,d,e,f,g]); h = h + 1) {
                                    global_job_array_0[a,b,c,d,e,f,g,h] = Job{
                                        Running:  true,
                                        JobID:    num,
                                        Score:    22.22,
                                        Name:     "test job"
                                    };
                                    num = num + 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    debug::debug_assert(a == 1);
    debug::debug_assert(b == 2);
    debug::debug_assert(c == 3);
    debug::debug_assert(d == 4);
    debug::debug_assert(e == 5);
    debug::debug_assert(f == 6);
    debug::debug_assert(g == 7);
    debug::debug_assert(h == 8);
    debug::debug_assert(num == 40320);



    fmt::println_string("\ntest cast 3 ------------------------");

    num = 0;
    for(a = 0; a < len(global_job_array_0); a = a + 1) {
        for(b = 0; b < len(global_job_array_0[a]); b = b + 1) {
            for(c = 0; c < len(global_job_array_0[a,b]); c = c + 1) {
                for(d = 0; d < len(global_job_array_0[a,b,c]); d = d + 1) {
                    for(e = 0; e < len(global_job_array_0[a,b,c,d]); e = e + 1) {
                        for(f = 0; f < len(global_job_array_0[a,b,c,d,e]); f = f + 1) {
                            for(g = 0; g < len(global_job_array_0[a,b,c,d,e,f]); g = g + 1) {
                                for(h = 0; h < len(global_job_array_0[a,b,c,d,e,f,g]); h = h + 1) {
                                    if(global_job_array_0[a,b,c,d,e,f,g,h].Running != true) {
                                        fmt::println_string("test failed");
                                    }
                                    if(global_job_array_0[a,b,c,d,e,f,g,h].JobID != num) {
                                        fmt::println_string("test failed");
                                    }
                                    if(global_job_array_0[a,b,c,d,e,f,g,h].Score != 22.22) {
                                        fmt::println_string("test failed");
                                    }
                                    if(global_job_array_0[a,b,c,d,e,f,g,h].Name != "test job") {
                                        fmt::println_string("test failed");
                                    }
                                    
                                    num = num + 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    debug::debug_assert(num == 40320);

}
