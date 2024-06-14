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
      true == true; // success
      // true == 1; // failed

      // true > true; // failed

      1 > 1;
      fmt::println(1 > 1);

}


function func_0() {

}

function func_1() -> (int) {
      
}

function func_5() -> (Job) {
      
}