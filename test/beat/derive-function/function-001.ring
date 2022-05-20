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


function doit1() {
    println_string("function doit1 BEGIN");
    println_string("function doit1 END");
}

function doit2() {
    println_string("function doit2 BEGIN");

    doit1();

    println_string("function doit2 END");
}

function doit3() {
    println_string("function doit3 BEGIN");

    doit2();

    println_string("function doit3 END");
}

function doit4() {
    println_string("function doit4 BEGIN");

    doit3();
    
    println_string("function doit4 END");
}

function doit5() {
    println_string("function doit5 BEGIN");

    doit4();
    
    println_string("function doit5 END");
}

function doit6() {
    println_string("function doit6 BEGIN");

    doit5();

    println_string("function doit6 END");
}


doit6();