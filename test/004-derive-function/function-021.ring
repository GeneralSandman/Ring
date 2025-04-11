
package main

import {
	fmt;
	debug;
  reflect;
}



fn test(var int... int_value_list) {
    var int int_value;
    for(int_value = range int_value_list) {
        fmt::println(int_value);
    }
}


// TestDetail: 测试一下函数的可变参数

fn main() {
    var int int_value_0;
    var int int_value_1;

    int_value_0 = 1;
    int_value_1 = 2;

    test(int_value_0, int_value_1);
}
