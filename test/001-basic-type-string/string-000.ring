//
// File:    string-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-08-16
//

package main

import {
	fmt;
	debug;
}

@main
function main() {
  fmt::println_string("1");
  fmt::println_string("2");
  fmt::println_string("1" .. "2");

  
  fmt::println_string("123");
  fmt::println_string("456");
  fmt::println_string("123" .. "456");

}
