package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递bool数组类型参数
// TestDetail: 分别传递1-8个bool数组类型参数
@main
fn main() {

	fmt::println(return_1_bool_array_1());

	fmt::println(return_1_bool_array_2());

	fmt::println(return_1_bool_array_3());

	fmt::println(return_1_bool_array_4());

}





fn return_1_bool_array_1() -> (bool[]) {
	return bool[]{true};
}

fn return_1_bool_array_2() -> (bool[,]) {
	return bool[,]{
		bool[]{true, false},
		bool[]{false, true},
	};
}

fn return_1_bool_array_3() -> (bool[,,]) {
	return bool[,,]{
		bool[,]{
			bool[]{true, false, true},
			bool[]{false, true, false},
			bool[]{true, false, true},
		},
		bool[,]{
			bool[]{true, false, true},
			bool[]{false, true, false},
			bool[]{true, false, true},
		},
	};
}

fn return_1_bool_array_4() -> (bool[,,,]) {
	return bool[,,,]{
		bool[,,]{
			bool[,]{
				bool[]{true, false, true},
				bool[]{false, true, false},
				bool[]{true, false, true},
			},
			bool[,]{
				bool[]{true, false, true},
				bool[]{false, true, false},
				bool[]{true, false, true},
			},
		}
	};
}
