package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递int数组类型参数
// TestDetail: 分别传递1-8个int数组类型参数
@main
function main() {

	fmt::println(return_1_int_array_1());

	fmt::println(return_1_int_array_2());

	fmt::println(return_1_int_array_3());

	fmt::println(return_1_int_array_4());

}





function return_1_int_array_1() -> (int[]) {
	return int[]{1};
}

function return_1_int_array_2() -> (int[,]) {
	return int[,]{
		int[]{1, 0},
		int[]{0, 1},
	};
}

function return_1_int_array_3() -> (int[,,]) {
	return int[,,]{
		int[,]{
			int[]{1, 0, 1},
			int[]{0, 1, 0},
			int[]{1, 0, 1},
		},
		int[,]{
			int[]{1, 0, 1},
			int[]{0, 1, 0},
			int[]{1, 0, 1},
		},
	};
}

function return_1_int_array_4() -> (int[,,,]) {
	return int[,,,]{
		int[,,]{
			int[,]{
				int[]{1, 0, 1},
				int[]{0, 1, 0},
				int[]{1, 0, 1},
			},
			int[,]{
				int[]{1, 0, 1},
				int[]{0, 1, 0},
				int[]{1, 0, 1},
			},
		},
		int[,,]{
			int[,]{
				int[]{1, 0, 1},
				int[]{0, 1, 0},
				int[]{1, 0, 1},
			},
			int[,]{
				int[]{1, 0, 1},
				int[]{0, 1, 0},
				int[]{1, 0, 1},
			},
		},
	};
}
