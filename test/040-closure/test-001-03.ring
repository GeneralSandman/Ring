//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	os;
	debug;
	fmt;
}


typedef FuncType0 = fn();
typedef FuncType1 = fn(int);
typedef FuncType2 = fn(int, int);
typedef FuncType3 = fn(int, int, int);

typedef FuncType4 = fn() -> (int);
typedef FuncType5 = fn(int) -> (int);
typedef FuncType6 = fn(int, int) -> (int);
typedef FuncType7 = fn(int, int, int) -> (int);


typedef FuncType8 = fn(bool, int, int64, double, string) -> (bool, int, int64, double, string);


fn main() {
	var FuncType0  local_func_var0;
	var FuncType1  local_func_var1;
	var FuncType2  local_func_var2;
	var FuncType3  local_func_var3;
	var FuncType4  local_func_var4;
	var FuncType5  local_func_var5;
	var FuncType6  local_func_var6;
	var FuncType7  local_func_var7;
	var FuncType8  local_func_var8;

	fmt::println("before init closure==========\n");
	fmt::println(reflect::typeof(local_func_var0));
	fmt::println(reflect::typeof(local_func_var1));
	fmt::println(reflect::typeof(local_func_var2));
	fmt::println(reflect::typeof(local_func_var3));
	fmt::println(reflect::typeof(local_func_var4));
	fmt::println(reflect::typeof(local_func_var5));
	fmt::println(reflect::typeof(local_func_var6));
	fmt::println(reflect::typeof(local_func_var7));
	fmt::println(reflect::typeof(local_func_var8));


	fmt::println("\nafter init closure===========\n");

	local_func_var0 = fn() {};
	local_func_var2 = fn(var int a, var int b) {};
	local_func_var1 = fn(var int a) {};
	local_func_var3 = fn(var int a, var int b, var int c) {};
	local_func_var4 = fn() -> (int) {};
	local_func_var5 = fn(var int a) -> (int) {};
	local_func_var6 = fn(var int a, var int b) -> (int) {};
	local_func_var7 = fn(var int a, var int b, var int c) -> (int) {};
	local_func_var8 = fn(var bool a, var int b, var int64 c, var double d, var string e) -> (bool, int, int64, double, string) {};

	fmt::println(reflect::typeof(local_func_var0));
	fmt::println(reflect::typeof(local_func_var1));
	fmt::println(reflect::typeof(local_func_var2));
	fmt::println(reflect::typeof(local_func_var3));
	fmt::println(reflect::typeof(local_func_var4));
	fmt::println(reflect::typeof(local_func_var5));
	fmt::println(reflect::typeof(local_func_var6));
	fmt::println(reflect::typeof(local_func_var7));
	fmt::println(reflect::typeof(local_func_var8));


}