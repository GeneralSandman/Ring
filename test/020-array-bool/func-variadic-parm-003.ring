package main

import {
    fmt;
    debug;
    reflect;
}


global {
}

// TestDetail: 测试可变参数
// TestDetail: 可变参数为 bool[]... 类型
// TestDetail: TODO: 四维以上的测试用例还没有覆盖
fn main() {

    fmt::printf("\ntest case 1--------\n");
    func_variadic_parameter_dimension_1(
        true, 
        false,
        true
    );

    fmt::printf("\ntest case 2--------\n");
    func_variadic_parameter_dimension_2(
        bool[]{false},
        bool[]{true},
        bool[]{false, true},
        bool[]{true, true, true}
    );

    fmt::printf("\ntest case 3--------\n");
    func_variadic_parameter_dimension_3(
        bool[!2]{
            bool[]{false}, 
            bool[]{true},
        },
        bool[!2]{
            bool[]{false}, 
            bool[]{true},
        }
    );

    fmt::printf("\ntest case 4--------\n");
    func_variadic_parameter_dimension_4(
        bool[!3]{
            bool[!2]{
                bool[]{false}, 
                bool[]{true},
            },
            bool[!2]{
                bool[]{false}, 
                bool[]{true},
            }
        }
    );

}

fn func_variadic_parameter_dimension_1(var bool... array_value) {
    fmt::printf("func_variadic_parameter_dimension_1========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_2(var bool[]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_2========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_3(var bool[!2]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_3========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_4(var bool[!3]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_4========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value); 
}

fn func_variadic_parameter_dimension_5(var bool[!4]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_5========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_6(var bool[!5]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_6========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_7(var bool[!6]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_7========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_8(var bool[!7]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_8========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

