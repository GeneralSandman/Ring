package main

import {
    fmt;
    debug;
}

global {
    var bool[] global_bool_array_0;
}

fn main() {
    global_bool_array_0 = new bool[200];

    var int index = 0;
    var bool local_bool_value_0;

    global_bool_array_0[index] = true;
    for(local_bool_value_0 = range global_bool_array_0) {
        debug::assert(local_bool_value_0 == true);

        // 提前把 in-range 下一个要访问的 数值通过数组索引进行修改
        index ++;
        if(index < len(global_bool_array_0)) {
          global_bool_array_0[index] = true;
        }
    }
}
