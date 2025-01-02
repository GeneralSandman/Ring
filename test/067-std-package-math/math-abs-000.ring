
package main

import {
    fmt;
    math;
}


// 测试 math abs() 函数
fn main() {
	

	fmt::printf("test [abs][0]----------\n");
	fmt::printf(" = {}\n", math::abs(-5.0));
	fmt::printf(" = {}\n", math::abs(-4.0));
	fmt::printf(" = {}\n", math::abs(-3.0));
	fmt::printf(" = {}\n", math::abs(-2.0));
	fmt::printf(" = {}\n", math::abs(-1.0));
	fmt::printf(" = {}\n", math::abs(-0.0));
	fmt::printf(" = {}\n", math::abs(0.0));
	fmt::printf(" = {}\n", math::abs(1.0));
	fmt::printf(" = {}\n", math::abs(2.0));
	fmt::printf(" = {}\n", math::abs(3.0));
	fmt::printf(" = {}\n", math::abs(4.0));
	fmt::printf(" = {}\n", math::abs(5.0));

	fmt::printf(" = {}\n", math::abs(-2147483648.0));
	fmt::printf(" = {}\n", math::abs(2147483648.0));


}
