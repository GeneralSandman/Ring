
import {
	fmt;
	debug;
}

@main
function main() {
    var int int_value_1;

    int_value_1 = 1;

    debug::debug_assert(int_value_1 == 1);
    fmt::println_int(int_value_1);


    jump #JUMP_TAG;

    int_value_1 = 2;

    #JUMP_TAG;

    debug::debug_assert(int_value_1 == 1);
    fmt::println_int(int_value_1);
}
