//
// File:    debug-stack-003.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-12-13
//

package main

import {
	runtime;
}


fn main() {
	test1(false);
}

fn test1(var bool bool_value) {
  runtime::print_call_stack();
}
