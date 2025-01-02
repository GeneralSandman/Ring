
//
// File:    string-003.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-10-20
//

package main

import {
	fmt;
	debug;
  vm;
}

// TestDetail: 测试通过函数参数传递 string类型的参数
// TestDetail: 通过函数返回 string类型
fn main() {
    var string string_value;

    fmt::println(pass_to_string("1234567890"));


    string_value = "1234567890";
    fmt::println(pass_to_string(string_value));
}

fn pass_to_string(var string string_value) -> (string) {
    fmt::printf("string_value={}\n", string_value);
    return string_value;
}
