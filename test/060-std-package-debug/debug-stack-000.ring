//
// File:    debug-stack-003.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-12-13
//

package main

import {
	debug;
}

@main
function main() {
	test1(false);
}

function test1(var bool bool_value) {
  debug::print_call_stack();
}
