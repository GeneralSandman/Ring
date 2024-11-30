package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递double数组类型参数
// TestDetail: 分别传递1-8个double数组类型参数
@main
function main() {

	pass_1_double_array_1(double[]{1.0});

	pass_1_double_array_2(double[,]{
		double[]{1.0, 0.0},
		double[]{0.0, 1.0},
	});

	pass_1_double_array_3(
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
	);

	pass_1_double_array_4(
		double[,,,]{
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
		}
	);

}





function pass_1_double_array_1(var double[] a) {
	fmt::println(a);
}

function pass_1_double_array_2(var double[,] a) {
	fmt::println(a);
}

function pass_1_double_array_3(var double[,,] a) {
	fmt::println(a);
}

function pass_1_double_array_4(var double[,,,] a) {
	fmt::println(a);
}
