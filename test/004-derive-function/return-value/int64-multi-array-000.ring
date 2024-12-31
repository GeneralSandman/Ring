package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递int64数组类型参数
// TestDetail: 分别传递1-8个int64数组类型参数
@main
fn main() {

	fmt::println(return_1_int64_array_1());

	fmt::println(return_1_int64_array_2());

	fmt::println(return_1_int64_array_3());

	fmt::println(return_1_int64_array_4());

}





fn return_1_int64_array_1() -> (int64[]) {
	return int64[]{1L};
}

fn return_1_int64_array_2() -> (int64[,]) {
	return int64[,]{
		int64[]{1L, 0L},
		int64[]{0L, 1L},
	};
}

fn return_1_int64_array_3() -> (int64[,,]) {
	return int64[,,]{
		int64[,]{
			int64[]{1L, 0L, 1L},
			int64[]{0L, 1L, 0L},
			int64[]{1L, 0L, 1L},
		},
		int64[,]{
			int64[]{1L, 0L, 1L},
			int64[]{0L, 1L, 0L},
			int64[]{1L, 0L, 1L},
		},
	};
}

fn return_1_int64_array_4() -> (int64[,,,]) {
	return int64[,,,]{
		int64[,,]{
			int64[,]{
				int64[]{1L, 0L, 1L},
				int64[]{0L, 1L, 0L},
				int64[]{1L, 0L, 1L},
			},
			int64[,]{
				int64[]{1L, 0L, 1L},
				int64[]{0L, 1L, 0L},
				int64[]{1L, 0L, 1L},
			},
		},
		int64[,,]{
			int64[,]{
				int64[]{1L, 0L, 1L},
				int64[]{0L, 1L, 0L},
				int64[]{1L, 0L, 1L},
			},
			int64[,]{
				int64[]{1L, 0L, 1L},
				int64[]{0L, 1L, 0L},
				int64[]{1L, 0L, 1L},
			},
		}
	};
}
