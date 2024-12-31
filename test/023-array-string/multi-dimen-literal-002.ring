package main

import {
    fmt;
    debug;
}

global {
    var string[,] global_string_array_0;
}


// TestDetail: 测试多维数组的初始化
// TestDetail: 二维数组的初始化

@main
fn main() {
    global_string_array_0 =  string[,]{
        string[]{ "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9"},
        string[]{"10", "11", "12", "13", "14", "15", "16", "17", "18", "19"},
        string[]{"20", "21", "22", "23", "24", "25", "26", "27", "28", "29"},
        string[]{"30", "31", "32", "33", "34", "35", "36", "37", "38", "39"},
        string[]{"40", "41", "42", "43", "44", "45", "46", "47", "48", "49"},
        string[]{"50", "51", "52", "53", "54", "55", "56", "57", "58", "59"},
        string[]{"60", "61", "62", "63", "64", "65", "66", "67", "68", "69"},
        string[]{"70", "71", "72", "73", "74", "75", "76", "77", "78", "79"},
        string[]{"80", "81", "82", "83", "84", "85", "86", "87", "88", "89"},
        string[]{"90", "91", "92", "93", "94", "95", "96", "97", "98", "99"}
    };


    debug::assert(len(global_string_array_0)    == 10);
    debug::assert(len(global_string_array_0[0]) == 10);
    debug::assert(len(global_string_array_0[1]) == 10);
    debug::assert(len(global_string_array_0[2]) == 10);
    debug::assert(len(global_string_array_0[3]) == 10);
    debug::assert(len(global_string_array_0[4]) == 10);
    debug::assert(len(global_string_array_0[5]) == 10);
    debug::assert(len(global_string_array_0[6]) == 10);
    debug::assert(len(global_string_array_0[7]) == 10);
    debug::assert(len(global_string_array_0[8]) == 10);
    debug::assert(len(global_string_array_0[9]) == 10);

    var int i;
    var int j;
    var int num;

    for(i=0; i<len(global_string_array_0); i=i+1) {
        for(j=0; j<len(global_string_array_0[i]); j=j+1) {
            num++;
        }
    }

    debug::assert(num == 100);


}
