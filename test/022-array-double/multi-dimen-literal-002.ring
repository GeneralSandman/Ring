package main

import {
    fmt;
    debug;
}

global {
    var double[,] global_double_array_0;
}


// TestDetail: 测试多维数组的初始化
// TestDetail: 二维数组的初始化

@main
fn main() {
    global_double_array_0 =  double[,]{
        double[]{ 0.0,  1.0,  2.0,  3.0,  4.0,  5.0,  6.0,  7.0,  8.0,  9.0},
        double[]{10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0},
        double[]{20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0},
        double[]{30.0, 31.0, 32.0, 33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0},
        double[]{40.0, 41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0, 48.0, 49.0},
        double[]{50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0},
        double[]{60.0, 61.0, 62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0, 69.0},
        double[]{70.0, 71.0, 72.0, 73.0, 74.0, 75.0, 76.0, 77.0, 78.0, 79.0},
        double[]{80.0, 81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0, 88.0, 89.0},
        double[]{90.0, 91.0, 92.0, 93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0}

    };


    debug::assert(len(global_double_array_0)    == 10);
    debug::assert(len(global_double_array_0[0]) == 10);
    debug::assert(len(global_double_array_0[1]) == 10);
    debug::assert(len(global_double_array_0[2]) == 10);
    debug::assert(len(global_double_array_0[3]) == 10);
    debug::assert(len(global_double_array_0[4]) == 10);
    debug::assert(len(global_double_array_0[5]) == 10);
    debug::assert(len(global_double_array_0[6]) == 10);
    debug::assert(len(global_double_array_0[7]) == 10);
    debug::assert(len(global_double_array_0[8]) == 10);
    debug::assert(len(global_double_array_0[9]) == 10);

    var int i;
    var int j;
    var int num;
    var double double_value = 0.0;

    // 偶数为 true, 奇数为 false
    for(i=0; i<len(global_double_array_0); i=i+1) {
        for(j=0; j<len(global_double_array_0[i]); j=j+1) {
            if(global_double_array_0[i,j] != double_value){
                fmt::println_string("test failed");
            } 

            double_value = double_value + 1.0;
            num++;
        }
    }

    debug::assert(num == 100);


}
