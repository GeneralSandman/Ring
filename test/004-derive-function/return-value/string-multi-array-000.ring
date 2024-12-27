package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递string数组类型参数
// TestDetail: 分别传递1-8个string数组类型参数
@main
function main() {

	fmt::println(pass_1_string_array_1());

	fmt::println(pass_1_string_array_2());

	fmt::println(pass_1_string_array_3());

	fmt::println(pass_1_string_array_4());

}


function pass_1_string_array_1() -> (string[]) {
	return string[]{"true"};
}

function pass_1_string_array_2() -> (string[,]) {
	return string[,]{
		string[]{"true", "false"},
		string[]{"false", "true"},
	};
}

function pass_1_string_array_3() -> (string[,,]) {
	return string[,,]{
            string[,]{
                string[]{"true", "false", "true"},
                string[]{"false", "true", "false"},
                string[]{"true", "false", "true"},
            },
            string[,]{
                string[]{"true", "false", "true"},
                string[]{"false", "true", "false"},
                string[]{"true", "false", "true"},
            },
		};
}

function pass_1_string_array_4() -> (string[,,,]) {
	return string[,,,]{
			string[,,]{
				string[,]{
					string[]{"true", "false", "true"},
					string[]{"false", "true", "false"},
					string[]{"true", "false", "true"},
				},
				string[,]{
					string[]{"true", "false", "true"},
					string[]{"false", "true", "false"},
					string[]{"true", "false", "true"},
				},
			}
		};
}
