//
// File:    std-fmt-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	fmt;
}

@main
fn main() {
	fmt::println_bool(true);
	fmt::println_int(123);
	fmt::println_double(123.456);
	fmt::println_string("hello world");
}