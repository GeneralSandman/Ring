package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递double数组类型参数
// TestDetail: 分别传递1-8个double数组类型参数
@main
fn main() {

	fmt::println(return_1_double_array_1());

	fmt::println(return_1_double_array_2());

	fmt::println(return_1_double_array_3());

	fmt::println(return_1_double_array_4());

}





fn return_1_double_array_1() -> (double[]) {
	return double[]{1.0};
}

fn return_1_double_array_2() -> (double[,]) {
	return double[,]{
		double[]{1.0, 0.0},
		double[]{0.0, 1.0},
	};
}

fn return_1_double_array_3() -> (double[,,]) {
	return double[,,]{
		double[,]{
			double[]{1.0, 0.0, 1.0},
			double[]{0.0, 1.0, 0.0},
			double[]{1.0, 0.0, 1.0},
		},
		double[,]{
			double[]{1.0, 0.0, 1.0},
			double[]{0.0, 1.0, 0.0},
			double[]{1.0, 0.0, 1.0},
		},
	};
}

fn return_1_double_array_4() -> (double[,,,]) {
	return double[,,,]{
		double[,,]{
			double[,]{
				double[]{1.0, 0.0, 1.0},
				double[]{0.0, 1.0, 0.0},
				double[]{1.0, 0.0, 1.0},
			},
			double[,]{
				double[]{1.0, 0.0, 1.0},
				double[]{0.0, 1.0, 0.0},
				double[]{1.0, 0.0, 1.0},
			},
		},
		double[,,]{
			double[,]{
				double[]{1.0, 0.0, 1.0},
				double[]{0.0, 1.0, 0.0},
				double[]{1.0, 0.0, 1.0},
			},
			double[,]{
				double[]{1.0, 0.0, 1.0},
				double[]{0.0, 1.0, 0.0},
				double[]{1.0, 0.0, 1.0},
			},
		}
	};
}
