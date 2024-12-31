package main

import {
	fmt;
	debug;
}


// TestDetail: derive函数传递string数组类型参数
// TestDetail: 分别传递1-8个string数组类型参数
@main
fn main() {

	pass_1_string_array_1(string[]{"true"});

	pass_1_string_array_2(string[,]{
		string[]{"true", "false"},
		string[]{"false", "true"},
	});

	pass_1_string_array_3(
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
	);

	pass_1_string_array_4(
		string[,,,]{
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
		}
	);

}





fn pass_1_string_array_1(var string[] a) {
	fmt::println(a);
}

fn pass_1_string_array_2(var string[,] a) {
	fmt::println(a);
}

fn pass_1_string_array_3(var string[,,] a) {
	fmt::println(a);
}

fn pass_1_string_array_4(var string[,,,] a) {
	fmt::println(a);
}
