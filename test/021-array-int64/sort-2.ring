package main

import {
    fmt;
    debug;
}

global {
    var int64[] global_int64_array_0;
}

// TestDetail: 测试通过索引查找数组中的元素, 索引是个复杂表达式
// TestDetail: e.g. global_int64_array_0[i+1] = i;

fn main() {
    var int i = 0;
    global_int64_array_0 = int64[]{9L,8L,7L,6L,5L,4L,3L,2L,1L,0L};


    fmt::println_string("test cast 1 ------------------------");
    for(i = 0; i < len(global_int64_array_0); i++) {
        fmt::println_int64(global_int64_array_0[i]);
    }

    fmt::println_string("\ntest cast 2 ------------------------");
    for(i=0; i+1 < len(global_int64_array_0); i+=2) {
        global_int64_array_0[i] = to_int64(i);
        global_int64_array_0[i+1] = to_int64(i);
    }

    for(i = 0; i < len(global_int64_array_0); i++) {
        fmt::println_int64(global_int64_array_0[i]);
    }
}
