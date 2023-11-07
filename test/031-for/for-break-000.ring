
import {
	fmt;
	debug;
}

@main
function main() {
    var int int_value_1;
    var int int_value_2;

    var int int_sum;

    for(int_value_1 = 0; int_value_1 < 10; int_value_1 = int_value_1 + 1) {
      for(int_value_2 = 0; int_value_2 < 10; int_value_2 = int_value_2 + 1) {
        if(int_value_2 >= 5) {
          break;
        }
        int_sum = int_sum + 1;
      }
    }

    debug::debug_assert(int_value_1 == 10);
    fmt::println_int(int_value_1);

    debug::debug_assert(int_value_2 == 5);
    fmt::println_int(int_value_2);

    debug::debug_assert(int_sum == 50);
    fmt::println_int(int_sum);

}
