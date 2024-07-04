
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

// TestDetail: 测试string的GC算法

@main
function main() {
    var string string_value_0;
    var string string_value_1;
    var string string_value_2;

    string_value_0 = "123456789_123456";
    string_value_0 = "123456789_123456";
    string_value_0 = "123456789_123456";

    string_value_1 = "123456789_123456";


    
    debug::debug_assert(vm::heap_size() == 88); // 8*3+16*4
    vm::garbage_collect();
    debug::debug_assert(vm::heap_size() == 40); // 16 + 16 + 8


    string_value_2 = string_value_0 .. string_value_1;


    debug::debug_assert(vm::heap_size() == 72); // 16 + 16 + 8 + 32
    vm::garbage_collect();
    debug::debug_assert(vm::heap_size() == 64); // 16 + 16 + 32

}
