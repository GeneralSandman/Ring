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

typedef class Job {
      field bool    Running;
      field int     JobID;
      field double  Score;
  }

@main
function main() {
      var bool bool_value;

      bool_value = not bool_value;

      fmt::println(bool_value);

}

function test() -> (bool) {
      return false;
}
