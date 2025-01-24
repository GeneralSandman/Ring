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

typedef Job = class {
      var bool    Running;
      var int     JobID;
      var double  Score;
  }

//TestDetail: 编译错误
fn main() {
      true == true; // success
      // true == 1; // failed

      // true > true; // failed

      1 > 1;
      fmt::println(1 > 1);

}


fn func_0() {

}

fn func_1() -> (int) {
      
}

fn func_5() -> (Job) {
      
}