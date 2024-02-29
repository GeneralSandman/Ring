package main

import {
    fmt;
    debug;
}

global {
    var int[,,] global_int_array_0;
}


// TestDetail: 测试多维数组的初始化
// TestDetail: 三维数组的初始化

@main
function main() {
    global_int_array_0 =  int[,,]{
        int[,]{
            int[]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
            int[]{10,11,12,13,14,15,16,17,18,19},
            int[]{20,21,22,23,24,25,26,27,28,29},
            int[]{30,31,32,33,34,35,36,37,38,39},
            int[]{40,41,42,43,44,45,46,47,48,49},
            int[]{50,51,52,53,54,55,56,57,58,59},
            int[]{60,61,62,63,64,65,66,67,68,69},
            int[]{70,71,72,73,74,75,76,77,78,79},
            int[]{80,81,82,83,84,85,86,87,88,89},
            int[]{90,91,92,93,94,95,96,97,98,99}
        },
        int[,]{
            int[]{100,101,102,103,104,105,106,107,108,109},
            int[]{110,111,112,113,114,115,116,117,118,119},
            int[]{120,121,122,123,124,125,126,127,128,129},
            int[]{130,131,132,133,134,135,136,137,138,139},
            int[]{140,141,142,143,144,145,146,147,148,149},
            int[]{150,151,152,153,154,155,156,157,158,159},
            int[]{160,161,162,163,164,165,166,167,168,169},
            int[]{170,171,172,173,174,175,176,177,178,179},
            int[]{180,181,182,183,184,185,186,187,188,189},
            int[]{190,191,192,193,194,195,196,197,198,199}
        },
        int[,]{
            int[]{200,201,202,203,204,205,206,207,208,209},
            int[]{210,211,212,213,214,215,216,217,218,219},
            int[]{220,221,222,223,224,225,226,227,228,229},
            int[]{230,231,232,233,234,235,236,237,238,239},
            int[]{240,241,242,243,244,245,246,247,248,249},
            int[]{250,251,252,253,254,255,256,257,258,259},
            int[]{260,261,262,263,264,265,266,267,268,269},
            int[]{270,271,272,273,274,275,276,277,278,279},
            int[]{280,281,282,283,284,285,286,287,288,289},
            int[]{290,291,292,293,294,295,296,297,298,299}
        }
    };

    


    fmt::println_string("test cast 1 ------------------------");
    debug::debug_assert(len(global_int_array_0)    == 3);
    debug::debug_assert(len(global_int_array_0[0]) == 10);
    debug::debug_assert(len(global_int_array_0[1]) == 10);
    debug::debug_assert(len(global_int_array_0[2]) == 10);

    debug::debug_assert(len(global_int_array_0[0,0]) == 10);
    debug::debug_assert(len(global_int_array_0[1,9]) == 10);
    debug::debug_assert(len(global_int_array_0[2,9]) == 10);



    var int i;
    var int j;
    var int k;
    var int num;

    fmt::println_string("\ntest cast 2 ------------------------");

    for(i=0; i<len(global_int_array_0); i=i+1) {
        for(j=0; j<len(global_int_array_0[i]); j=j+1) {
            for(k=0; k<len(global_int_array_0[i,j]); k=k+1) {
                if(global_int_array_0[i,j,k] != i*100+j*10+k) {
                    fmt::println_string("test failed");
                }
                if(global_int_array_0[i,j,k] != num) {
                    fmt::println_string("test failed");
                }
                num++;
            } 
        }
    }

    debug::debug_assert(num == 300);

}
