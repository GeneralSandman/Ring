
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

// TestDetail: 测试string的GC算法

@main
function main() {
    var string string_value;

    string_value = "123456789_123456";
    string_value = "123456789_123456";
    string_value = "123456789_123456";

    debug::debug_assert(len(string_value) == 16);


    
    // string_value = "123456789_";
    // fmt::println_int(len(string_value));
    // debug::debug_assert(len(string_value) == 10100);


    debug::debug_assert(vm::heap_size() == 56); // 16*3 + 8
    vm::garbage_collect();
    debug::debug_assert(vm::heap_size() == 16); // 16

}
