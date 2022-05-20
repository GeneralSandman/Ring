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
    println_string("I'm function doit1, go go go!");
}

function doit2() {
    println_string("I'm function doit2, go go go!");
}

function doit3() {
    println_string("I'm function doit3, go go go!");
}


function doit4() {
    println_string("doit4 begin");

    doit1();
    doit2();
    doit3();

    println_string("doit4 end");
}

println_string("invoke doit1");
doit1();


println_string("");


println_string("invoke doit2");
doit2();


println_string("");


println_string("invoke doit3");
doit3();

println_string("");


println_string("invoke doit4");
doit4();



