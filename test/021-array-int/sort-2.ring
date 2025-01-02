package main

import {
    fmt;
    debug;
}

global {
    var int[] global_int_array_0;
}

// TestDetail: 测试通过索引查找数组中的元素, 索引是个复杂表达式
// TestDetail: e.g. global_int_array_0[i+1] = i;

fn main() {
    var int i = 0;
    global_int_array_0 = int[]{9,8,7,6,5,4,3,2,1,0};


    fmt::println_string("test cast 1 ------------------------");
    for(i = 0; i < len(global_int_array_0); i++) {
        fmt::println_int(global_int_array_0[i]);
    }

    fmt::println_string("\ntest cast 2 ------------------------");
    for(i=0; i+1 < len(global_int_array_0); i+=2) {
        global_int_array_0[i] = i;
        global_int_array_0[i+1] = i;
    }

    for(i = 0; i < len(global_int_array_0); i++) {
        fmt::println_int(global_int_array_0[i]);
    }
}
