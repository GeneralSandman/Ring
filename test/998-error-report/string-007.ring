//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-08-16
//

package main

import {
	fmt;
	debug;
}

//TestDetail: 编译错误
@main
function main() {
      var string string_value;

      string_value = string_value .. "a";
      string_value = string_value .. "b";
      string_value = string_value .. "c";
      string_value = string_value .. 1;

      fmt::println(string_value);

      
}
