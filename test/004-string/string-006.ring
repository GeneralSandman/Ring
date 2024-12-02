
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
function main() {
    var string string_value;

    // 100 行, 每行有101个字符(包含换行符), 100 * 101 = 10100
    string_value = 
    `123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
`;

    fmt::println_int(len(string_value));
    debug::assert(len(string_value) == 10100);


    
    // 100 行, 每行有101个字符(包含换行符), 100 * 101 = 10100
    string_value = 
    `123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_123456789_
`;

    fmt::println_int(len(string_value));
    debug::assert(len(string_value) == 10100);
}
