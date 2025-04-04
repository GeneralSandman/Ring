package main

import {
    fmt;
    debug;
    reflect;
}


typedef Job = class {
    var bool    Bool;
    var int     Int;
    var int64   Int64;
    var double  Double;
    var string  String;
}

global {
}

// TestDetail: 测试可变参数
// TestDetail: 可变参数为 Job[]... 类型
// TestDetail: TODO: 四维以上的测试用例还没有覆盖
fn main() {
    var Job local_job_value_0 = Job{
        Bool: false,
        Int: 123,
        Int64: 123456789L,
        Double: 123.456789,
        String: "hello world"
    };

    fmt::printf("\ntest case 1--------\n");
    func_variadic_parameter_dimension_1(
        local_job_value_0,
        local_job_value_0,
        local_job_value_0
    );

    fmt::printf("\ntest case 2--------\n");
    func_variadic_parameter_dimension_2(
        Job[]{local_job_value_0},
        Job[]{local_job_value_0, local_job_value_0},
        Job[]{local_job_value_0, local_job_value_0, local_job_value_0},
        Job[]{local_job_value_0, local_job_value_0, local_job_value_0, local_job_value_0}
    );

    fmt::printf("\ntest case 3--------\n");
    func_variadic_parameter_dimension_3(
        Job[!2]{
            Job[]{local_job_value_0},
            Job[]{local_job_value_0, local_job_value_0},
            Job[]{local_job_value_0, local_job_value_0, local_job_value_0},
            Job[]{local_job_value_0, local_job_value_0, local_job_value_0, local_job_value_0}
        },
        Job[!2]{
            Job[]{local_job_value_0},
            Job[]{local_job_value_0, local_job_value_0},
            Job[]{local_job_value_0, local_job_value_0, local_job_value_0},
            Job[]{local_job_value_0, local_job_value_0, local_job_value_0, local_job_value_0}
        }
    );

    fmt::printf("\ntest case 4--------\n");
    func_variadic_parameter_dimension_4(
        Job[!3]{
            Job[!2]{
                Job[]{local_job_value_0},
                Job[]{local_job_value_0, local_job_value_0},
                Job[]{local_job_value_0, local_job_value_0, local_job_value_0},
                Job[]{local_job_value_0, local_job_value_0, local_job_value_0, local_job_value_0}
            },
            Job[!2]{
                Job[]{local_job_value_0},
                Job[]{local_job_value_0, local_job_value_0},
                Job[]{local_job_value_0, local_job_value_0, local_job_value_0},
                Job[]{local_job_value_0, local_job_value_0, local_job_value_0, local_job_value_0}
            }
        }
    );

}

fn func_variadic_parameter_dimension_1(var Job... array_value) {
    fmt::printf("func_variadic_parameter_dimension_1========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_2(var Job[]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_2========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_3(var Job[!2]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_3========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_4(var Job[!3]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_4========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value); 
}

fn func_variadic_parameter_dimension_5(var Job[!4]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_5========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_6(var Job[!5]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_6========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_7(var Job[!6]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_7========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_8(var Job[!7]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_8========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

