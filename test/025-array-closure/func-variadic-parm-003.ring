package main

import {
    fmt;
    debug;
    reflect;
}

typedef FuncType = fn();

global {
}

// TestDetail: 测试可变参数
// TestDetail: 可变参数为 FuncType[]... 类型
// TestDetail: TODO: 四维以上的测试用例还没有覆盖
fn main() {

    fmt::printf("\ntest case 1--------\n");
    func_variadic_parameter_dimension_1(
        fn(){
            fmt::printf("func 1\n");
        }, 
        fn(){
            fmt::printf("func 2\n");
        }, 
        fn(){
            fmt::printf("func 3\n");
        }
    );


    fmt::printf("\ntest case 2--------\n");
    func_variadic_parameter_dimension_2(
        FuncType[]{
            fn(){
                fmt::printf("func 1,1\n");
            }, 
            fn(){
                fmt::printf("func 1,2\n");
            }, 
            fn(){
                fmt::printf("func 1,3\n");
            }
        },
        FuncType[]{
            fn(){
                fmt::printf("func 2,1\n");
            }, 
            fn(){
                fmt::printf("func 2,2\n");
            }, 
            fn(){
                fmt::printf("func 2,3\n");
            }
        }
    );


    fmt::printf("\ntest case 3--------\n");
    func_variadic_parameter_dimension_3(
        FuncType[!2]{
            FuncType[]{
                fn(){
                    fmt::printf("func 1,1,1\n");
                }, 
                fn(){
                    fmt::printf("func 1,1,2\n");
                }, 
            },
            FuncType[]{
                fn(){
                    fmt::printf("func 1,2,1\n");
                }, 
                fn(){
                    fmt::printf("func 1,2,2\n");
                }, 
            },
        },
        FuncType[!2]{
            FuncType[]{
                fn(){
                    fmt::printf("func 2,1,1\n");
                }, 
                fn(){
                    fmt::printf("func 2,1,2\n");
                }, 
            },
            FuncType[]{
                fn(){
                    fmt::printf("func 2,2,1\n");
                }, 
                fn(){
                    fmt::printf("func 2,2,2\n");
                }, 
            },
        }
    );


}

fn func_variadic_parameter_dimension_1(var FuncType... array_value) {
    fmt::printf("func_variadic_parameter_dimension_1========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));

    // 这里是指针，不好测试，先忽略
    // 输出 [closure(0x7fdc157ac280) closure(0x7fdc157ac2b0) closure(0x7fdc157ac2e0)]
    // fmt::printf("array_value           ={}\n", array_value);

    var FuncType local_func_value_0;
    for(local_func_value_0 = range array_value) {
        local_func_value_0();
    }
}

fn func_variadic_parameter_dimension_2(var FuncType[]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_2========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));

    // 这里是指针，不好测试，先忽略
    // 输出 [closure(0x7fdc157ac280) closure(0x7fdc157ac2b0) closure(0x7fdc157ac2e0)]
    // fmt::printf("array_value           ={}\n", array_value);

    var FuncType[] array_tmp_1;
    var FuncType local_func_value_0;
    for(array_tmp_1 = range array_value) {
        for(local_func_value_0 = range array_tmp_1) {
            local_func_value_0();
        }
    }
    
}

fn func_variadic_parameter_dimension_3(var FuncType[!2]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_3========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));

    // 这里是指针，不好测试，先忽略
    // 输出 [closure(0x7fdc157ac280) closure(0x7fdc157ac2b0) closure(0x7fdc157ac2e0)]
    // fmt::printf("array_value           ={}\n", array_value);

    var FuncType[!2] array_tmp_2;
    var FuncType[] array_tmp_1;
    var FuncType local_func_value_0;
    for(array_tmp_2 = range array_value) {
        for(array_tmp_1 = range array_tmp_2) {
            for(local_func_value_0 = range array_tmp_1) {
                local_func_value_0();
            }
        }
    }
}

fn func_variadic_parameter_dimension_4(var FuncType[!3]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_4========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value); 
}

fn func_variadic_parameter_dimension_5(var FuncType[!4]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_5========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_6(var FuncType[!5]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_6========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_7(var FuncType[!6]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_7========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

fn func_variadic_parameter_dimension_8(var FuncType[!7]... array_value) {
    fmt::printf("func_variadic_parameter_dimension_8========\n");
    fmt::printf("array_value  type     = {}\n", reflect::typeof(array_value));
    fmt::printf("len(array_value)      = {}\n", len(array_value));
    fmt::printf("cap(array_value) = {}\n", cap(array_value));
    fmt::printf("array_value           ={}\n", array_value);
}

