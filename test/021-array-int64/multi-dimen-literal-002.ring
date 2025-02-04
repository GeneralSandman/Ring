package main

import {
    fmt;
    debug;
}

global {
    var int64[,] global_int64_array_0;
}


// TestDetail: 测试多维数组的初始化
// TestDetail: 二维数组的初始化

fn main() {
    global_int64_array_0 =  int64[,]{
        int64[]{ 0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L},
        int64[]{10L,11L,12L,13L,14L,15L,16L,17L,18L,19L},
        int64[]{20L,21L,22L,23L,24L,25L,26L,27L,28L,29L},
        int64[]{30L,31L,32L,33L,34L,35L,36L,37L,38L,39L},
        int64[]{40L,41L,42L,43L,44L,45L,46L,47L,48L,49L},
        int64[]{50L,51L,52L,53L,54L,55L,56L,57L,58L,59L},
        int64[]{60L,61L,62L,63L,64L,65L,66L,67L,68L,69L},
        int64[]{70L,71L,72L,73L,74L,75L,76L,77L,78L,79L},
        int64[]{80L,81L,82L,83L,84L,85L,86L,87L,88L,89L},
        int64[]{90L,91L,92L,93L,94L,95L,96L,97L,98L,99L}
    };


    debug::assert(len(global_int64_array_0)    == 10);
    debug::assert(len(global_int64_array_0[0]) == 10);
    debug::assert(len(global_int64_array_0[1]) == 10);
    debug::assert(len(global_int64_array_0[2]) == 10);
    debug::assert(len(global_int64_array_0[3]) == 10);
    debug::assert(len(global_int64_array_0[4]) == 10);
    debug::assert(len(global_int64_array_0[5]) == 10);
    debug::assert(len(global_int64_array_0[6]) == 10);
    debug::assert(len(global_int64_array_0[7]) == 10);
    debug::assert(len(global_int64_array_0[8]) == 10);
    debug::assert(len(global_int64_array_0[9]) == 10);

    var int i;
    var int j;
    var int num;

    for(i=0; i<len(global_int64_array_0); i=i+1) {
        for(j=0; j<len(global_int64_array_0[i]); j=j+1) {
            if(global_int64_array_0[i,j] != to_int64(num)){
                fmt::println_string("test failed");
            } 
            num++;
        }
    }

    debug::assert(num == 100);



}
