package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递bool数组类型参数
// TestDetail: 分别传递1-8个bool数组类型参数
@main
function main() {

	pass_1_bool_array_1(bool[]{true});

	pass_1_bool_array_2(bool[,]{
		bool[]{true, false},
		bool[]{false, true},
	});

	pass_1_bool_array_3(
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
	);

	pass_1_bool_array_4(
		bool[,,,]{
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
		}
	);

}





function pass_1_bool_array_1(var bool[] a) {
	fmt::println(a);
}

function pass_1_bool_array_2(var bool[,] a) {
	fmt::println(a);
}

function pass_1_bool_array_3(var bool[,,] a) {
	fmt::println(a);
}

function pass_1_bool_array_4(var bool[,,,] a) {
	fmt::println(a);
}
