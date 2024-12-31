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
      var bool    Running;
      var int     JobID;
      var double  Score;
  }

//TestDetail: 编译错误
@main
fn main() {
      // func_0() + func_1(); // 编译报错
      // func_1() + func_1(); // 正常
      // func_5() + func_5(); // 编译报错

      // fmt::println(1 + 1.1);

      // 2 + 2L;
      // 2 - 2L;
      2 * 2L;
      2 / 2L;
      2 % 2L;
}


fn func_0() {

}

fn func_1() -> (int) {
      
}

fn func_5() -> (Job) {
      
}