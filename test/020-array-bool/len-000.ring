package main

import {
    fmt;
    debug;
}

global {
  var bool[] global_bool_array_0;
}

@main
function main() {
	global_bool_array_0 = new bool[200];
	
	fmt::println_int(len(global_bool_array_0));

}