package main

import {
	fmt;
	debug;
}

// TestDetail: 递归法计算 fibonacci
fn main() {
	fmt::printf("fibonacci(0) = {}\n", fibonacci(0));
	fmt::printf("fibonacci(1) = {}\n", fibonacci(1));
	fmt::printf("fibonacci(2) = {}\n", fibonacci(2));
	fmt::printf("fibonacci(3) = {}\n", fibonacci(3));
	fmt::printf("fibonacci(4) = {}\n", fibonacci(4));
	fmt::printf("fibonacci(5) = {}\n", fibonacci(5));
	fmt::printf("fibonacci(6) = {}\n", fibonacci(6));
	fmt::printf("fibonacci(7) = {}\n", fibonacci(7));
	fmt::printf("fibonacci(8) = {}\n", fibonacci(8));
	fmt::printf("fibonacci(9) = {}\n", fibonacci(9));
	fmt::printf("fibonacci(10) = {}\n", fibonacci(10));
}


fn fibonacci(var int n) -> (int) {
	if (n <= 0) {
		return 0;
	} elseif (n == 1) {
		return 1;
	} 
	return fibonacci(n - 1) + fibonacci(n - 2);
}