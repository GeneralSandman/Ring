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



// TestDetail: 匿名函数
// TestDetail: 生命匿名函数直接调用
// TestDetail: Immediately invoked function expression
@main
function main() {

	function() {
		fmt::println("closure block");
	}();

	function(var bool bool_value) {
		fmt::printf("closure bool_value: {}\n", bool_value);
	}(true);

	function(var int int_value) {
		fmt::printf("closure int_value: {}\n", int_value);
	}(123);

	function(var int64 int64_value) {
		fmt::printf("closure int64_value: {}\n", int64_value);
	}(456L);

	function(var double double_value) {
		fmt::printf("closure double_value: {}\n", double_value);
	}(3.1415);

	function(var string string_value) {
		fmt::printf("closure string_value: {}\n", string_value);
	}("ring-hello-world");



	

	var bool bool_value;
	var int int_value;
	var int64 int64_value;
    var double double_value;
    var string string_value;

	
	fmt::printf("\n");

    // 闭包返回值
	bool_value = function() -> (bool) {
		fmt::printf("invoke closure 1\n");
		return true;
	}();
	int_value = function() -> (int) {
		fmt::printf("invoke closure 2\n");
        return 2;
    }();
	int64_value = function() -> (int64) {
		fmt::printf("invoke closure 3\n");
        return 6L;
    }();
	double_value = function() -> (double) {
		fmt::printf("invoke closure 4\n");
        return 66.66;
    }();
    string_value = function() -> (string) {
		fmt::printf("invoke closure 5\n");
		return "ring-compiler";
	}();

	fmt::printf("main bool_value: {}\n", bool_value);
	fmt::printf("main int_value: {}\n", int_value);
    fmt::printf("main int64_value: {}\n", int64_value);
	fmt::printf("main double_value: {}\n", double_value);
    fmt::printf("main string_value: {}\n", string_value);
	
}

