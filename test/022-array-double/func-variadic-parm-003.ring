package main

import {
    fmt;
    debug;
    reflect;
}


global {
}

// TestDetail: 测试可变参数
// TestDetail: 可变参数为 double[]... 类型
// TestDetail: TODO: 四维以上的测试用例还没有覆盖
fn main() {

    fmt::printf("\ntest case 1--------\n");
    func_variadic_parameter_dimension_1(
        1.1, 
        0.1,
        1.1
    );

    fmt::printf("\ntest case 2--------\n");
    func_variadic_parameter_dimension_2(
        double[]{0.1},
        double[]{1.1},
        double[]{0.1, 1.1},
        double[]{1.1, 1.1, 1.1}
    );

    fmt::printf("\ntest case 3--------\n");
    func_variadic_parameter_dimension_3(
        double[!2]{
            double[]{0.1}, 
            double[]{1.1},
        },
        double[!2]{
            double[]{0.1}, 
            double[]{1.1},
        }
    );

    fmt::printf("\ntest case 4--------\n");
    func_variadic_parameter_dimension_4(
        double[!3]{
            double[!2]{
                double[]{0.1}, 
                double[]{1.1},
            },
            double[!2]{
                double[]{0.1}, 
                double[]{1.1},
            }
        }
    );

}

fn func_variadic_parameter_dimension_1(var double... array_value) {
    fmt::printf("func_variadic_parameter_dimension_1========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_2(var double[]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_2========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_3(var double[!2]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_3========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_4(var double[!3]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_4========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
    fmt::printf("array_value           ={}\n", array_value); 
}

fn func_variadic_parameter_dimension_5(var double[!4]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_5========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_6(var double[!5]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_6========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_7(var double[!6]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_7========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_8(var double[!7]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_8========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("capacity(array_value) = {}\n", capacity(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

