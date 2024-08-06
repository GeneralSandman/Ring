
package main

import {
    fmt;
    math;
}


// 测试 math abs() 函数
@main
function main() {
	


	fmt::printf("test [pow][0]----------\n");
	fmt::printf(" = {}\n", math::pow(1.0, 0.0));
	fmt::printf(" = {}\n", math::pow(1.0, 1.0));
	fmt::printf(" = {}\n", math::pow(1.0, 2.0));
	fmt::printf(" = {}\n", math::pow(1.0, 3.0));

	fmt::printf(" = {}\n", math::pow(2.0, 0.0));
	fmt::printf(" = {}\n", math::pow(2.0, 1.0));
	fmt::printf(" = {}\n", math::pow(2.0, 2.0));
	fmt::printf(" = {}\n", math::pow(2.0, 3.0));

	fmt::printf(" = {}\n", math::pow(3.0, 0.0));
	fmt::printf(" = {}\n", math::pow(3.0, 1.0));
	fmt::printf(" = {}\n", math::pow(3.0, 2.0));
	fmt::printf(" = {}\n", math::pow(3.0, 3.0));


	fmt::printf("\ntest [pow][1]----------\n");
	fmt::printf(" = {}\n", math::pow(-1.0, 0.0));
	fmt::printf(" = {}\n", math::pow(-1.0, 1.0));
	fmt::printf(" = {}\n", math::pow(-1.0, 2.0));
	fmt::printf(" = {}\n", math::pow(-1.0, 3.0));

	fmt::printf(" = {}\n", math::pow(-2.0, 0.0));
	fmt::printf(" = {}\n", math::pow(-2.0, 1.0));
	fmt::printf(" = {}\n", math::pow(-2.0, 2.0));
	fmt::printf(" = {}\n", math::pow(-2.0, 3.0));

	fmt::printf(" = {}\n", math::pow(-3.0, 0.0));
	fmt::printf(" = {}\n", math::pow(-3.0, 1.0));
	fmt::printf(" = {}\n", math::pow(-3.0, 2.0));
	fmt::printf(" = {}\n", math::pow(-3.0, 3.0));


	fmt::printf("\ntest [pow][2]----------\n");
	fmt::printf(" = {}\n", math::pow(1.0, -0.0));
	fmt::printf(" = {}\n", math::pow(1.0, -1.0));
	fmt::printf(" = {}\n", math::pow(1.0, -2.0));
	fmt::printf(" = {}\n", math::pow(1.0, -3.0));

	fmt::printf(" = {}\n", math::pow(2.0, -0.0));
	fmt::printf(" = {}\n", math::pow(2.0, -1.0));
	fmt::printf(" = {}\n", math::pow(2.0, -2.0));
	fmt::printf(" = {}\n", math::pow(2.0, -3.0));

	fmt::printf(" = {}\n", math::pow(3.0, -0.0));
	fmt::printf(" = {}\n", math::pow(3.0, -1.0));
	fmt::printf(" = {}\n", math::pow(3.0, -2.0));
	fmt::printf(" = {}\n", math::pow(3.0, -3.0));


	fmt::printf("\ntest [pow][3]----------\n");
	fmt::printf(" = {}\n", math::pow(-1.0, -0.0));
	fmt::printf(" = {}\n", math::pow(-1.0, -1.0));
	fmt::printf(" = {}\n", math::pow(-1.0, -2.0));
	fmt::printf(" = {}\n", math::pow(-1.0, -3.0));

	fmt::printf(" = {}\n", math::pow(-2.0, -0.0));
	fmt::printf(" = {}\n", math::pow(-2.0, -1.0));
	fmt::printf(" = {}\n", math::pow(-2.0, -2.0));
	fmt::printf(" = {}\n", math::pow(-2.0, -3.0));

	fmt::printf(" = {}\n", math::pow(-3.0, -0.0));
	fmt::printf(" = {}\n", math::pow(-3.0, -1.0));
	fmt::printf(" = {}\n", math::pow(-3.0, -2.0));
	fmt::printf(" = {}\n", math::pow(-3.0, -3.0));

}
