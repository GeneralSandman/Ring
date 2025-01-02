
package main

import {
    fmt;
    debug;
    vm;
    os;
}

global {
  var int int_value;
  var int[] int_array;

  var int heap_size;
}

fn main() {
    var string env_name  = "RING_TEST_ENV";
	var string env_value = "";
	var string tmp       = "";


    fmt::printf("test case [0][getenv]----------\n");
	env_value = os::getenv(env_name);
	fmt::printf("env value: {}={}\n", env_name, env_value);
	debug::assert(env_value == "");


    fmt::printf("\ntest case [1][setenv]----------\n");
	tmp = "VALUE_1_2_3";
	os::setenv(env_name, tmp);


    fmt::printf("\ntest case [1][getenv]----------\n");
	env_value = os::getenv(env_name);
	fmt::printf("env value: {}={}\n", env_name, env_value);
	debug::assert(env_value == tmp);
}
