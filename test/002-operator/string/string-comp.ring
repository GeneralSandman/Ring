
package main

import {
	fmt;
	debug;
}

@main
function main() {

	fmt::printf("--------\n");

	var string local_string_value_0;
	var string local_string_value_1;

	fmt::printf("{}\n", local_string_value_0 == local_string_value_1);
	fmt::printf("{}\n", local_string_value_0 != local_string_value_1);

	local_string_value_0 = "a";
	local_string_value_1 = "b";
	fmt::printf("{}\n", local_string_value_0 < local_string_value_1);




	fmt::printf("--------\n");

	var string[] local_string_array_0 = string[]{"", ""};

	fmt::printf("{}\n", local_string_array_0[0] == local_string_array_0[1]);
	fmt::printf("{}\n", local_string_array_0[0] != local_string_array_0[1]);

	local_string_array_0[0] = "a";
	local_string_array_0[1] = "b";
	fmt::printf("{}\n", local_string_array_0[0] < local_string_array_0[1]);




	fmt::printf("--------\n");

	var string[,] local_string_array_1 = string[,]{
		string[]{"a", "b"},
		string[]{"c", "d"},
	};

	fmt::printf("{}\n", local_string_array_1[0,0] < local_string_array_1[1,1]);
	fmt::printf("{}\n", local_string_array_1[0,1] < local_string_array_1[1,0]);

	fmt::printf("{}\n", local_string_array_1[0,0] > to_string(1));


}