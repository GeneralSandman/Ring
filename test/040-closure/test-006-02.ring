//
// File:    std-debug-000.ring
// Author:  GeneralSandman - generalsandman@163.com
// Date:    2023-04-24
//

package main

import {
	os;
	debug;
	fmt;
	strings;
}


@main
function main() {
	var string[] string_array = string[]{"c", "b"};

	// res = strings::join(string_array, "-");
	// fmt::println(res);

	
	test(string_array);

	fmt::println("==============");
	strings_join(string_array, "-");
}

function test(var string[] aaa) {
	var string res;
	res = res .. "xx";
	// fmt::println(res);
}

function strings_join(var string[] a, var string sep) -> (string) {
	var string res;

	// res = "a";
	fmt::println(res);

	var int i = 0;
	for(i = 0; i < len(a); i++) {
		fmt::println(a[i]);
	
		res = res .. a[i];
		if (i != len(a)-1) {
			res = res .. sep;
		}

		fmt::println(res);
	}

	return res;
}
