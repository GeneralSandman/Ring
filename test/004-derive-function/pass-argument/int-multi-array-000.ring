package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递int数组类型参数
// TestDetail: 分别传递1-8个int数组类型参数
@main
function main() {

	pass_1_int_array_1(int[]{1});

	pass_1_int_array_2(int[,]{
		int[]{1, 0},
		int[]{0, 1},
	});

	pass_1_int_array_3(
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
		}
	);

	pass_1_int_array_4(
		int[,,,]{
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
		}
	);

}





function pass_1_int_array_1(var int[] a) {
	fmt::println(a);
}

function pass_1_int_array_2(var int[,] a) {
	fmt::println(a);
}

function pass_1_int_array_3(var int[,,] a) {
	fmt::println(a);
}

function pass_1_int_array_4(var int[,,,] a) {
	fmt::println(a);
}
