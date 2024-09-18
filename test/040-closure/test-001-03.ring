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


typedef function() FuncType0;
typedef function(var int a) FuncType1;
typedef function(var int a, var int b) FuncType2;
typedef function(var int a, var int b, var int c) FuncType3;

typedef function() -> (int) FuncType4;
typedef function(var int a) -> (int) FuncType5;
typedef function(var int a, var int b) -> (int) FuncType6;
typedef function(var int a, var int b, var int c) -> (int) FuncType7;


typedef function(var bool a, var int b, var int64 c, var double d, var string e) -> (bool, int, int64, double, string) FuncType8;


@main
function main() {
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

	local_func_var0 = function() {};
	local_func_var1 = function(var int a) {};
	local_func_var2 = function(var int a, var int b) {};
	local_func_var3 = function(var int a, var int b, var int c) {};
	local_func_var4 = function() -> (int) {};
	local_func_var5 = function(var int a) -> (int) {};
	local_func_var6 = function(var int a, var int b) -> (int) {};
	local_func_var7 = function(var int a, var int b, var int c) -> (int) {};
	local_func_var8 = function(var bool a, var int b, var int64 c, var double d, var string e) -> (bool, int, int64, double, string) {};

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