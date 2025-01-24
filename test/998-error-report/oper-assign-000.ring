//
// File:    string-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2022-05-19
//


package main

import {
	fmt;
	os;
	debug;
}

typedef Job = class {
	var int a;
	var int b;
}

typedef FuncType = fn()->(string);

fn test1(var Job a) {

}

fn test2(var FuncType func_var) {

}

// ring dump 报错
// fn test3(var Job[] a) {

// }

fn test4() -> (Job[]) {
	return Job[]{};
}


fn main() {
	var int[] int_array = new int[0];

	push(int_array, false);
	fmt::println(int_array);


	// var int[!2] int_array_2 = int[!2]{
	// 	int[]{1, 2, 3, 4, 5},
	// 	int[]{6, 7, 8, 9, 10},
	// };

	// push(int_array_2, int_array);
	// fmt::println(int_array_2);


}
