
package main

import {
	fmt;
	debug;
  reflect;
}

typedef class Job1 {
  var bool    Bool;
  var int     Int;
  var double  Double;
  var string  String;

  fn printInfo() {
      fmt::printf("Job1({}, {}, {}, {})\n", self.Bool, self.Int, self.Double, self.String);
  }
  fn returnSelf() -> (Job1) {
      return self;
  }
  fn method_return_0() -> (string, int) {
  }
}

fn func_return_0() -> (bool, int) {
    return true, 1;
}


// TestDetail: 函数调用 返回参数的强制校验
// TestDetail: 不能贬义通过, function_call 不能应用到多项赋值中
// TestDetail: 

fn main() {
    var bool   local_bool_value_0;
    var int    local_int_value_0;
    var double local_double_value_0;
    var string local_string_value_0;
    var Job1   local_job1_value_0;


    local_bool_value_0, local_string_value_0 = func_return_0();
    // 编译不通过, 类型不匹配

    fmt::printf("local_bool_value_0:{}, local_int_value_0:{}\n", local_bool_value_0, local_int_value_0);
}
