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

typedef class Job {
      field bool    Running;
      field int     JobID;
      field double  Score;
  }

//TestDetail: 编译错误
@main
function main() {
      // func_0() + func_1(); // 编译报错
      // func_1() + func_1(); // 正常
      // func_5() + func_5(); // 编译报错

      // fmt::println(1 + 1.1);

      2 + 2L;
}


function func_0() {

}

function func_1() -> (int) {
      
}

function func_5() -> (Job) {
      
}