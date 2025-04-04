package main

import {
    fmt;
    debug;
    runtime;
}

typedef Job1 = class {
  // var bool    Bool;
  // var int     Int;
  // var int64   Int64;
  // var double  Double;
  var string  String;
}

typedef Job2 = class {
    var int[]  IntArray;
}

global {
}

fn main() {
    test_class_2();
    runtime::gc();
}

fn test_array_int() {
    var int[] global_int_array_0;
    global_int_array_0 = new int[8];
    runtime::gc();
}


fn test_array_int64() {
    var int64[] global_int64_array_0;
    global_int64_array_0 = new int64[8];
    runtime::gc();
}

fn test_array_string() {
    string[]{"1", "2", "3", "4", "5", "6", "7", "8"};
    runtime::gc();
}

fn test_array_string_1() {
    var string[] global_string_array_0;
    
    // ----------------
    global_string_array_0 = string[]{"1", "2", "3", "4", "5", "6", "7", "8"};
    runtime::gc();
    fmt::println(global_string_array_0);


    // ----------------
    global_string_array_0 = string[]{"1", "2", "3", "4", "5", "6", "7", "8"};
    runtime::gc();
    fmt::println(global_string_array_0);
}



fn test_class() {
    var Job1 local_job_value_0;

    // ----------------
    local_job_value_0.String = "1";
    runtime::gc();
    fmt::println(local_job_value_0);

    // ----------------
    local_job_value_0.String = "1234567890123456";
    runtime::gc();
    fmt::println(local_job_value_0);

}

fn test_class_1() {
    var Job1 local_job_value_0;

    var string local_string_value_0;
    local_string_value_0 = "12345678";

    local_job_value_0.String = local_string_value_0;
    runtime::gc();
    fmt::println(local_string_value_0);
    fmt::println(local_job_value_0);

    // 指向同一块内存
    fmt::println_pointer(local_string_value_0);
    fmt::println_pointer(local_job_value_0.String);
}

fn test_class_2() {
    var Job2 local_job2_value_0;

    fmt::println(len(local_job2_value_0.IntArray));
    runtime::gc();

}

fn test_array_class() {
    var Job1[] local_class_array_0;

    // ----------------
    local_class_array_0 = new Job1[8];
    runtime::gc();
    fmt::println(local_class_array_0);
}
