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

//TestDetail: 编译错误
@main
function main() {
      // true and true; // 编译成功

      // true and 1; // 编译错误
      // 1 and true; // 编译错误

      true or 1;

}


function func_0() {

}

function func_1() -> (int) {
      
}

function func_5() -> (Job) {
      
}