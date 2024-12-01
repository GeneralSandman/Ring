package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递int64数组类型参数
// TestDetail: 分别传递1-8个int64数组类型参数
@main
function main() {

	pass_1_int64_array_1(int64[]{1L});

	pass_1_int64_array_2(int64[,]{
		int64[]{1L, 0L},
		int64[]{0L, 1L},
	});

	pass_1_int64_array_3(
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
	);

	pass_1_int64_array_4(
		int64[,,,]{
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
		}
	);

}





function pass_1_int64_array_1(var int64[] a) {
	fmt::println(a);
}

function pass_1_int64_array_2(var int64[,] a) {
	fmt::println(a);
}

function pass_1_int64_array_3(var int64[,,] a) {
	fmt::println(a);
}

function pass_1_int64_array_4(var int64[,,,] a) {
	fmt::println(a);
}