
//
// File:    string-003.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-10-20
//

package main

import {
	fmt;
	debug;
  vm;
}

// TestDetail: 测试通过函数参数传递 string类型的参数
@main
function main() {
    var string string_value;
    string_value = "1234567890";

    pass_to_string(string_value);
    pass_to_string("1234567890");
}

function pass_to_string(var string string_value) {
    fmt::printf("string_value={}\n", string_value);
}
