//
// File:    int-000.ring
// Author:  zhenhuli - generalsandman@163.com
// Date:    2022-05-19
//

function println_bool(var bool bool_value);
function println_int(var int int_value);
function println_double(var double double_value);
function println_string(var string string_value);
function debug_assert(var bool bool_value);
function exit(var int int_value);

// -----------------------------


if("a" == "a") {
    println_string("test pass");
} else {
    println_string("test failed");

}

if("a" != "a") {
    println_string("test failed");
} else {
    println_string("test pass");
}

if("a" > "a") {
    println_string("test failed");
} else {
    println_string("test pass");
}

if("a" >= "a") {
    println_string("test pass");
} else {
    println_string("test failed");
}

if("a" < "a") {
    println_string("test failed");
} else {
    println_string("test pass");
}

if("a" <= "a") {
    println_string("test pass");
} else {
    println_string("test failed");
}



println_string("----------------");

if("a" == "b") {
    println_string("test failed");
} else {
    println_string("test pass");
}

if("a" != "b") {
    println_string("test pass");
} else {
    println_string("test failed");
}

if("a" > "b") {
    println_string("test failed");
} else {
    println_string("test pass");
}

if("a" >= "b") {
    println_string("test failed");
} else {
    println_string("test pass");
}

if("a" < "b") {
    println_string("test pass");
} else {
    println_string("test failed");
}

if("a" <= "b") {
    println_string("test pass");
} else {
    println_string("test failed");
}





