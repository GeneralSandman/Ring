package main

import {
    fmt;
    debug;
}

global {
    var int64[,,,,,,,] global_int64_array_0;
}

@main
function main() {
    global_int64_array_0 = new int64[1,2,3,4,5,6,7,8];

    fmt::println_string("test cast 1 ------------------------");
    debug::assert(len(global_int64_array_0) == 1);
    debug::assert(len(global_int64_array_0[0]) == 2);
    debug::assert(len(global_int64_array_0[0,0]) == 3);
    debug::assert(len(global_int64_array_0[0,0,0]) == 4);
    debug::assert(len(global_int64_array_0[0,0,0,0]) == 5);
    debug::assert(len(global_int64_array_0[0,0,0,0,0]) == 6);
    debug::assert(len(global_int64_array_0[0,0,0,0,0,0]) == 7);
    debug::assert(len(global_int64_array_0[0,0,0,0,0,0,0]) == 8);
    

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

    for(a = 0; a < len(global_int64_array_0); a = a + 1) {
        for(b = 0; b < len(global_int64_array_0[a]); b = b + 1) {
            for(c = 0; c < len(global_int64_array_0[a,b]); c = c + 1) {
                for(d = 0; d < len(global_int64_array_0[a,b,c]); d = d + 1) {
                    for(e = 0; e < len(global_int64_array_0[a,b,c,d]); e = e + 1) {
                        for(f = 0; f < len(global_int64_array_0[a,b,c,d,e]); f = f + 1) {
                            for(g = 0; g < len(global_int64_array_0[a,b,c,d,e,f]); g = g + 1) {
                                for(h = 0; h < len(global_int64_array_0[a,b,c,d,e,f,g]); h = h + 1) {
                                    global_int64_array_0[a,b,c,d,e,f,g,h] = to_int64(num);
                                    num = num + 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    debug::assert(a == 1);
    debug::assert(b == 2);
    debug::assert(c == 3);
    debug::assert(d == 4);
    debug::assert(e == 5);
    debug::assert(f == 6);
    debug::assert(g == 7);
    debug::assert(h == 8);
    debug::assert(num == 40320);



    fmt::println_string("\ntest cast 3 ------------------------");

    num = 0;
    for(a = 0; a < len(global_int64_array_0); a = a + 1) {
        for(b = 0; b < len(global_int64_array_0[a]); b = b + 1) {
            for(c = 0; c < len(global_int64_array_0[a,b]); c = c + 1) {
                for(d = 0; d < len(global_int64_array_0[a,b,c]); d = d + 1) {
                    for(e = 0; e < len(global_int64_array_0[a,b,c,d]); e = e + 1) {
                        for(f = 0; f < len(global_int64_array_0[a,b,c,d,e]); f = f + 1) {
                            for(g = 0; g < len(global_int64_array_0[a,b,c,d,e,f]); g = g + 1) {
                                for(h = 0; h < len(global_int64_array_0[a,b,c,d,e,f,g]); h = h + 1) {
                                    if(global_int64_array_0[a,b,c,d,e,f,g,h] != to_int64(num)) {
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

    debug::assert(num == 40320);

}
