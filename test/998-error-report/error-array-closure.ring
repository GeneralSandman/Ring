//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
}

typedef Job = class {
	var bool     Bool;
    var int      Int;
    var int64    Int64;
    var double   Double;
    var string   String;
	var FuncType FuncField;
}

typedef FuncType0 = fn();
typedef FuncType = fn() -> (string);

//TestDetail: 对于item为 closure 的 array， 在初始化的时候强制检查类型
fn main() {

	// 报错测试 1
	// 最外层 的 assignment 类型不匹配
	// var FuncType0[] local_func0_array = FuncType[] {
	// };


	// 报错测试 2
	// itme 类型和 array 类型不匹配
	// var FuncType0[] local_func0_array = FuncType0[]{
	// 	fn() -> (string) {
	// 		fmt::println("fn 0");
	// 		return "tmp";
	// 	},
	// 	fn() {

	// 	}
	// };

	// 报错测试 3
	// 多维数组，数组的元素为 closure
	// var FuncType0[!2] local_func0_array = FuncType0[!2] {
	// 	FuncType[] {
	// 	}
	// };

	// 报错测试 4
	// var FuncType0[!2] local_func0_array = FuncType0[!2] {
	// 	return_array_closure()
	// };

    /*

	var FuncType tmp;

	tmp = local_func_array[0];
	tmp();

	*/

	// var FuncType0 tmp0;
	// tmp0 = local_func_array[0]; // 编译报错：类型不匹配
	// tmp0();
}


fn return_array_closure() -> (FuncType0[]) {
	return FuncType0[]{};
}

