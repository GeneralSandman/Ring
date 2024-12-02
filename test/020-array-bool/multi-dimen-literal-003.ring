package main

import {
    fmt;
    debug;
}

global {
    var bool[,,] global_bool_array_0;
}


// TestDetail: 测试多维数组的初始化
// TestDetail: 三维数组的初始化

@main
function main() {
    global_bool_array_0 =  bool[,,]{
        bool[,]{
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
        },
        bool[,]{
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
        },
        bool[,]{
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
        },
        bool[,]{
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
            bool[]{true, false, true, false},
        },
    };


    debug::assert(len(global_bool_array_0)      == 4);
    debug::assert(len(global_bool_array_0[0])   == 4);
    debug::assert(len(global_bool_array_0[0,0]) == 4);

    var int i;
    var int j;
    var int k;
    var int num;
    var bool bool_value = true;

    // 偶数为 true, 奇数为 false
    for(i=0; i<len(global_bool_array_0); i=i+1) {
        for(j=0; j<len(global_bool_array_0[i]); j=j+1) {
            for(k=0; k<len(global_bool_array_0[i,j]); k=k+1) {
                if(global_bool_array_0[i,j,k] != bool_value){
                    fmt::println_string("test failed");
                } 
    
                bool_value = not bool_value;
                num++;
            }
        }
    }

    debug::assert(num == 64);

}
