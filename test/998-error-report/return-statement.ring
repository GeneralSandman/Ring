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

fn main() {

}


fn test0() {
	return;
}

fn test1() {
	// return 1; // 编译错误：
}

fn test2() -> (bool, int, string) {
	// return true, true, "hello"; // 编译错误：
}


fn test3() -> (bool) {
	// TODO:
	// 缺少return 语句，应该报错
}


fn test4() -> (bool) {
	var bool a;
	var bool b;
	var bool c;
	var int local_int_value_0;

	if(a) {
		return true;
	} else {
		// return 5L; // 编译报错
		// return 2; // 编译报错
	}


	if(a) {
		if(b) {
			if(c) {
				// return 1; // 编译报错
			}
		}
	}


	for(local_int_value_0 = 0; local_int_value_0 < 10; local_int_value_0++) {
		// return 1; // 编译报错
	}



	return true;
}


typedef FuncType = fn() -> (int, int, int);
fn test5() -> (bool, int, int64) {
	var FuncType local_func_var;

	local_func_var = fn() -> (int, int, int) {
		// return 1, 2, 3L; // 编译报错
	};
}