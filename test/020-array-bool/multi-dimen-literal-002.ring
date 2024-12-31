package main

import {
    fmt;
    debug;
}

global {
    var bool[,] global_bool_array_0;
}


// TestDetail: 测试多维数组的初始化
// TestDetail: 二维数组的初始化

@main
fn main() {
    global_bool_array_0 =  bool[,]{
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false},
        bool[]{true, false, true, false, true, false, true, false, true, false}
    };


    debug::assert(len(global_bool_array_0)    == 10);
    debug::assert(len(global_bool_array_0[0]) == 10);
    debug::assert(len(global_bool_array_0[1]) == 10);
    debug::assert(len(global_bool_array_0[2]) == 10);
    debug::assert(len(global_bool_array_0[3]) == 10);
    debug::assert(len(global_bool_array_0[4]) == 10);
    debug::assert(len(global_bool_array_0[5]) == 10);
    debug::assert(len(global_bool_array_0[6]) == 10);
    debug::assert(len(global_bool_array_0[7]) == 10);
    debug::assert(len(global_bool_array_0[8]) == 10);
    debug::assert(len(global_bool_array_0[9]) == 10);

    var int i;
    var int j;
    var int num;
    var bool bool_value = true;

    // 偶数为 true, 奇数为 false
    for(i=0; i<len(global_bool_array_0); i=i+1) {
        for(j=0; j<len(global_bool_array_0[i]); j=j+1) {
            if(global_bool_array_0[i,j] != bool_value){
                fmt::println_string("test failed");
            } 

            bool_value = not bool_value;
            num++;
        }
    }

    debug::assert(num == 100);


}
