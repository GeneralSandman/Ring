
package main

import {
  fmt;
  debug;
  runtime;
}

global {
  var string global_string_value_0;
}

fn main() {

    // --------- 测试 string 分配内存
    fmt::printf("global_string_value_0={}, cap={}", global_string_value_0, cap(global_string_value_0));
    fmt::println_string(global_string_value_0);

    // assign string
    global_string_value_0 = "1234567890";
    fmt::println_string(global_string_value_0);
    fmt::println(runtime::heap_size()); 
    /*
    * 内存分布
    * global_string_value_0(垃圾)   占用 8Byte
    * global_string_value_0  指向 常量，常量不占用空间
    */

    // gc
    runtime::gc();
    fmt::println_string(global_string_value_0);
    fmt::println(runtime::heap_size());
    /*
    * 内存分布
    * global_string_value_0  指向 常量，常量不占用空间
    */

}
