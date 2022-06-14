//
// File:    function-020.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-06-14
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------


function fibonacci_1(var int num) -> (int) {
    if(num == 1 or num == 2) {
        return 1;
    } else {
        return fibonacci_1(num-1) + fibonacci_1(num-2);
    }
}

function fibonacci_2(var int num) -> (int) {
    if(num < 3) {
        return 1;
    }


    var int a, b = 1, 1;
    var int i;
    var int tmp;
    for(i = 3; i <= num; i++){
        tmp = a + b;
        a = b;
        b = tmp;
    }
    return tmp;

}



println_string("\ntest case 1");
println_int(fibonacci_1(1));
println_int(fibonacci_1(2));
println_int(fibonacci_1(3));
println_int(fibonacci_1(4));
println_int(fibonacci_1(5));
println_int(fibonacci_1(6));
println_int(fibonacci_1(7));
println_int(fibonacci_1(8));
println_int(fibonacci_1(9));
println_int(fibonacci_1(10));



println_string("\ntest case 2");
println_int(fibonacci_2(1));
println_int(fibonacci_2(2));
println_int(fibonacci_2(3));
println_int(fibonacci_2(4));
println_int(fibonacci_2(5));
println_int(fibonacci_2(6));
println_int(fibonacci_2(7));
println_int(fibonacci_2(8));
println_int(fibonacci_2(9));
println_int(fibonacci_2(10));


println_string("\ntest case 3");
debug_assert(fibonacci_1(1) == fibonacci_2(1));
debug_assert(fibonacci_1(2) == fibonacci_2(2));
debug_assert(fibonacci_1(3) == fibonacci_2(3));
debug_assert(fibonacci_1(4) == fibonacci_2(4));
debug_assert(fibonacci_1(5) == fibonacci_2(5));
debug_assert(fibonacci_1(6) == fibonacci_2(6));
debug_assert(fibonacci_1(7) == fibonacci_2(7));
debug_assert(fibonacci_1(8) == fibonacci_2(8));
debug_assert(fibonacci_1(9) == fibonacci_2(9));
debug_assert(fibonacci_1(10) == fibonacci_2(10));
debug_assert(fibonacci_1(11) == fibonacci_2(11));
debug_assert(fibonacci_1(12) == fibonacci_2(12));
debug_assert(fibonacci_1(13) == fibonacci_2(13));
debug_assert(fibonacci_1(14) == fibonacci_2(14));
debug_assert(fibonacci_1(15) == fibonacci_2(15));
debug_assert(fibonacci_1(16) == fibonacci_2(16));
debug_assert(fibonacci_1(17) == fibonacci_2(17));
debug_assert(fibonacci_1(18) == fibonacci_2(18));
debug_assert(fibonacci_1(19) == fibonacci_2(19));
debug_assert(fibonacci_1(20) == fibonacci_2(20));
debug_assert(fibonacci_1(21) == fibonacci_2(21));
debug_assert(fibonacci_1(22) == fibonacci_2(22));
debug_assert(fibonacci_1(23) == fibonacci_2(23));
debug_assert(fibonacci_1(24) == fibonacci_2(24));
debug_assert(fibonacci_1(25) == fibonacci_2(25));


