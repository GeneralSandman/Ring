package main

import {
    fmt;
    debug;
    runtime;
}


// 默认空间 1+4+8+8=21
typedef Job0 = class {
    var bool    Bool;
    var int     Int;
    var int64   Int64;
    var double  Double;
}

// 默认空间 1+4+8+8+8=29
typedef Job1 = class {
//   var bool    Bool;
//   var int     Int;
//   var int64   Int64;
//   var double  Double;
  var string  String;
}

typedef Job2 = class {
    // var bool    Bool;
    // var int     Int;
    // var int64   Int64;
    // var double  Double;
    // var string  String;
    var bool[]   BoolArray;
    var int[]    IntArray;
    var int64[]  Int64Array;
    var double[] DoubleArray;
}

typedef FuncType = fn();

global {
}

fn main() {
    test_funcvar_0();
    // runtime::gc();
}

fn test_array_int() {
    var int[] local_int_array_0;
    local_int_array_0 = new int[8];
    runtime::gc();
}

fn test_array_int_2_dimension() {
    var int[,] local_int_array_0;
    local_int_array_0 = new int[1,8];
    local_int_array_0 = new int[2,8];
    runtime::gc();
}

fn test_array_int_3_dimension() {
    var int[,,] local_int_array_0;
    local_int_array_0 = new int[8,8,8];
    runtime::gc();
}


fn test_array_int64() {
    var int64[] local_int64_array_0;
    local_int64_array_0 = new int64[8];
    runtime::gc();
}

fn test_array_string() {
    string[]{"1", "2", "3", "4", "5", "6", "7", "8"};
    runtime::gc();
}

fn test_array_string_1() {
    var string[] local_string_array_0;
    
    // ----------------
    local_string_array_0 = string[]{"1", "2", "3", "4", "5", "6", "7", "8"};
    runtime::gc();
    fmt::println(local_string_array_0);


    // ----------------
    local_string_array_0 = string[]{"1", "2", "3", "4", "5", "6", "7", "8"};
    runtime::gc();
    fmt::println(local_string_array_0);
}


fn test_class_job0() {
    var Job0 local_job_value_0;
    runtime::gc();
}
fn test_class_job0_array_0() {
    var Job0[] local_job_value_0;
    runtime::gc();
}
fn test_class_job0_array_1() {
    var Job0[] local_job_value_0 = new Job0[8];
    runtime::gc();
}
fn test_class_job0_array_2() {
    var Job0[] local_job_value_0 = new Job0[8];

    local_job_value_0 = new Job0[8];

    runtime::gc();
}
fn test_class_job0_array_3() {
    var Job0[] local_job_value_0 = new Job0[8];

    local_job_value_0 = Job0[]{
        Job0{
            Int: 1,
        },
    };
    runtime::gc();
}
fn test_class_job0_array_4() {
    var Job0[] local_job_value_0 = new Job0[8];

    local_job_value_0 = Job0[]{
        Job0{
            Int: 1,
        },
        Job0{
            Int: 2,
        },
        Job0{
            Int: 3,
        },
        Job0{
            Int: 4,
        },
        Job0{
            Int: 5,
        },
        Job0{
            Int: 6,
        },
        Job0{
            Int: 7,
        },
        Job0{
            Int: 8,
        },
    };
    runtime::gc();
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

fn test_class_job1_0() {
    var Job1 local_job_value_0;
    
    runtime::gc();
}
fn test_class_job1_1() {
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
fn test_class_job1_array_0() {
    var Job1[] local_job1_array_0;

    runtime::gc();
}
fn test_class_job1_array_1() {
    var Job1[] local_job1_array_0 = new Job1[8];

    runtime::gc();
}
fn test_class_job1_array_2() {
    var Job1[] local_job1_array_0 = new Job1[8];
    var Job1[] local_job2_array_0 = new Job1[8];
    local_job1_array_0 = new Job1[8];
    local_job1_array_0 = new Job1[8];
    local_job1_array_0 = Job1[]{
        Job1{
            String: "1234567890123456",
        },
    };

    runtime::gc();
}


fn test_class_job2() {
    var Job2 local_job2_value_0;

    local_job2_value_0 = Job2{
        IntArray: new int[8],
    };

    local_job2_value_0 = Job2{
        BoolArray:   new bool[8],
        IntArray:    new int[8],
        Int64Array:  new int64[8],
        DoubleArray: new double[8],
    };



    runtime::gc();

}

fn test_class_2() {
    var Job2 local_job2_value_0;


    var int[] local_int_array_0 = new int[8];
    local_job2_value_0.IntArray = local_int_array_0;
    runtime::gc();

    // 指向同一块内存
    fmt::println_pointer(local_int_array_0);
    fmt::println_pointer(local_job2_value_0.IntArray);
    local_int_array_0[0] = 1; // 修改会同时修改 local_job2_value_0.IntArray
    fmt::println(local_int_array_0);
    fmt::println(local_job2_value_0.IntArray);

}

fn test_array_class() {
    var Job1[] local_class_array_0;

    // ----------------
    local_class_array_0 = new Job1[8];
    runtime::gc();
    fmt::println(local_class_array_0);
}




fn test_funcvar_0() {
    var FuncType local_func_value_0;

    runtime::gc();
}

fn test_funcvar_1() {
    var FuncType local_func_value_0;

    local_func_value_0 = fn() {
        fmt::println("fn 1");
    };

    runtime::gc();

    local_func_value_0();
}

fn test_funcvar_array_0() {
    var FuncType[] local_func_value_0;
    local_func_value_0 = new FuncType[8];

    local_func_value_0[0] = fn() {
        fmt::println("fn 1");
    };
    local_func_value_0[0] = fn() {
        fmt::println("fn 11");
    };

    runtime::gc();

    local_func_value_0[0]();
    local_func_value_0[1]();
}