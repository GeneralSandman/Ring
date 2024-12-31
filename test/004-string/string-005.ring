
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

// TestDetail: 测试多行字符串

@main
fn main() {
    var string string_value;

    string_value = `block begin
    <>
    <>
    <>
    block end`;
    fmt::println_string(string_value);

    string_value = `1
    2
    3
    4
    5
    6
    7\`
    8\`
9`;

    fmt::println_string(string_value);
}
