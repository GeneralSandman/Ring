# Ring VitrualMachine Instruction Set

## 1. Ring Stacked-Based VM 指令集

| Num    |            指令               | 操作数类型 | 栈顶值变化                  | 栈高度 | 含义                               |  公式描述 |
| ------ | ---------------------------- | -------- | ---------------------------- | ---------------------------- | ------------------------------------------------ |  ---- |
|    1|                     push_bool|   1Byte_A|                    []-->[int]|                            +1|                 push constant bool value to stack|So(0).bool = A.bool|
|    2|                push_int_1byte|   1Byte_A|                    []-->[int]|                            +1|            push 1byte int constant value to stack|So(0).int = A.int|
|    3|                push_int_2byte|  2Byte_As|                    []-->[int]|                            +1|            push 2byte int constant value to stack|So(0).int = As.int|
|    4|                      push_int|  2Byte_As|                    []-->[int]|                            +1|                  push constant int value to stack|So(0).int = C(As).int|
|    5|                    push_int64|  2Byte_As|                    []-->[int]|                            +1|                push constant int64 value to stack|So(0).int64 = C(As).int64|
|    6|                   push_double|  2Byte_As|                 []-->[double]|                            +1|               push constant double value to stack|So(0).double = C(As).double|
|    7|                   push_string|  2Byte_As|                 []-->[string]|                            +1|               push constant string value to stack|So(0).string = C(As).string|
|    8|               pop_static_bool|  2Byte_As|                   [bool]-->[]|                            -1|                    bool assign to global-variable|K(As) = So(-1).bool|
|    9|                pop_static_int|  2Byte_As|                    [int]-->[]|                            -1|                     int assign to global-variable|K(As) = So(-1).int|
|   10|              pop_static_int64|  2Byte_As|                  [int64]-->[]|                            -1|                   int64 assign to global-variable|K(As) = So(-1).int64|
|   11|             pop_static_double|  2Byte_As|                 [double]-->[]|                            -1|                  double assign to global-variable|K(As) = So(-1).double|
|   12|             pop_static_string|  2Byte_As|                 [string]-->[]|                            -1|                  string assign to global-variable|K(As) = So(-1).string|
|   13|           pop_static_class_ob|  2Byte_As|                 [object]-->[]|                            -1|            class-object assign to global-variable|K(As) = So(-1).object|
|   14|              pop_static_array|  2Byte_As|                  [array]-->[]|                            -1|                   array assign to global-variable|K(As) = So(-1).array|
|   15|              push_static_bool|  2Byte_As|                   []-->[bool]|                            +1|              push global-variable's bool to stack|So(0).bool = K(As)|
|   16|               push_static_int|  2Byte_As|                    []-->[int]|                            +1|               push global-variable's int to stack|So(0).int = K(As)|
|   17|             push_static_int64|  2Byte_As|                  []-->[int64]|                            +1|             push global-variable's int64 to stack|So(0).int64 = K(As)|
|   18|            push_static_double|  2Byte_As|                 []-->[double]|                            +1|            push global-variable's double to stack|So(0).double = K(As)|
|   19|            push_static_string|  2Byte_As|                 []-->[string]|                            +1|            push global-variable's string to stack|So(0).string = K(As)|
|   20|          push_static_class_ob|  2Byte_As|                 []-->[object]|                            +1|      push global-variable's class-object to stack|So(0).object = K(As)|
|   21|             push_static_array|  2Byte_As|                  []-->[array]|                            +1|             push global-variable's array to stack|So(0).array = K(As)|
|   22|                pop_stack_bool|  2Byte_As|                              |                            -1|                     bool assign to local-variable|Si(FSB+As).bool = S(-1).bool|
|   23|                 pop_stack_int|  2Byte_As|                              |                            -1|                      int assign to local-variable|Si(FSB+As).int = S(-1).int|
|   24|               pop_stack_int64|  2Byte_As|                              |                            -1|                    int64 assign to local-variable|Si(FSB+As).int64 = S(-1).int64|
|   25|              pop_stack_double|  2Byte_As|                              |                            -1|                   double assign to local-variable|Si(FSB+As).double = S(-1).double|
|   26|              pop_stack_string|  2Byte_As|                              |                            -1|                   string assign to local-variable|Si(FSB+As).string = S(-1).string|
|   27|            pop_stack_class_ob|  2Byte_As|                              |                            -1|             class-object assign to local-variable|Si(FSB+As).object = S(-1).object|
|   28|               pop_stack_array|  2Byte_As|                              |                            -1|                    array assign to local-variable|Si(FSB+As).array = S(-1).array|
|   29|               push_stack_bool|  2Byte_As|                              |                            +1|               push local-variable's bool to stack|So(0).bool = Si(FSB+As).bool|
|   30|                push_stack_int|  2Byte_As|                              |                            +1|                push local-variable's int to stack|So(0).int = Si(FSB+As).int|
|   31|              push_stack_int64|  2Byte_As|                              |                            +1|              push local-variable's int64 to stack|So(0).int64 = Si(FSB+As).int64|
|   32|             push_stack_double|  2Byte_As|                              |                            +1|             push local-variable's double to stack|So(0).double = Si(FSB+As).double|
|   33|             push_stack_string|  2Byte_As|                              |                            +1|             push local-variable's string to stack|So(0).string = Si(FSB+As).string|
|   34|           push_stack_class_ob|  2Byte_As|                              |                            +1|       push local-variable's class-object to stack|So(0).object = Si(FSB+As).object|
|   35|              push_stack_array|  2Byte_As|                              |                            +1|              push local-variable's array to stack|So(0).array = Si(FSB+As).array|
|   36|                  push_array_a|     0Byte|                              |                            -1|                                                  ||
|   37|               push_array_bool|     0Byte|                              |                            -1|                                                  ||
|   38|                push_array_int|     0Byte|                              |                            -1|                                                  ||
|   39|              push_array_int64|     0Byte|                              |                            -1|                                                  ||
|   40|             push_array_double|     0Byte|                              |                            -1|                                                  ||
|   41|             push_array_string|     0Byte|                              |                            -1|                                                  ||
|   42|           push_array_class_ob|     0Byte|                              |                            -1|                                                  ||
|   43|                   pop_array_a|     0Byte|                              |                            -3|                                                  ||
|   44|                pop_array_bool|     0Byte|          [int,object,int]->[]|                            -3|                     assign to bool array by index||
|   45|                 pop_array_int|     0Byte|          [int,object,int]->[]|                            -3|                      assign to int array by index||
|   46|               pop_array_int64|     0Byte|          [int,object,int]->[]|                            -3|                    assign to int64 array by index||
|   47|              pop_array_double|     0Byte|          [int,object,int]->[]|                            -3|                   assign to double array by index||
|   48|              pop_array_string|     0Byte|          [int,object,int]->[]|                            -3|                   assign to string array by index||
|   49|            pop_array_class_ob|     0Byte|          [int,object,int]->[]|                            -3|                   assign to object array by index||
|   50|             array_append_bool|     0Byte|             [object,bool]->[]|                            -2|                   assign to object array by index||
|   51|              array_append_int|     0Byte|              [object,int]->[]|                            -2|                   assign to object array by index||
|   52|            array_append_int64|     0Byte|            [object,int64]->[]|                            -2|                   assign to object array by index||
|   53|           array_append_double|     0Byte|           [object,double]->[]|                            -2|                   assign to object array by index||
|   54|           array_append_string|     0Byte|           [object,string]->[]|                            -2|                   assign to object array by index||
|   55|         array_append_class_ob|     0Byte|           [object,object]->[]|                            -2|                   assign to object array by index||
|   56|                array_pop_bool|     0Byte|              [object]->[bool]|                             0|                   assign to object array by index||
|   57|                 array_pop_int|     0Byte|               [object]->[int]|                             0|                   assign to object array by index||
|   58|               array_pop_int64|     0Byte|             [object]->[int64]|                             0|                   assign to object array by index||
|   59|              array_pop_double|     0Byte|            [object]->[double]|                             0|                   assign to object array by index||
|   60|              array_pop_string|     0Byte|            [object]->[string]|                             0|                   assign to object array by index||
|   61|            array_pop_class_ob|     0Byte|            [object]->[object]|                             0|                   assign to object array by index||
|   62|                pop_field_bool|  2Byte_As|             [bool,object]->[]|                            -2|                  assign to class field whith bool|Field(So(-1).object, As).bool = So(-2).bool|
|   63|                 pop_field_int|  2Byte_As|              [int,object]->[]|                            -2|                                                  |Field(So(-1).object, As).int = So(-2).int|
|   64|               pop_field_int64|  2Byte_As|            [int64,object]->[]|                            -2|                                                  |Field(So(-1).object, As).int64 = So(-2).int64|
|   65|              pop_field_double|  2Byte_As|           [double,object]->[]|                            -2|                                                  |Field(So(-1).object, As).double = So(-2).double|
|   66|              pop_field_string|  2Byte_As|           [string,object]->[]|                            -2|                                                  |Field(So(-1).object, As).string = So(-2).string|
|   67|            pop_field_class_ob|  2Byte_As|           [object,object]->[]|                            -2|                                                  |Field(So(-1).object, As).object = So(-2).object|
|   68|               pop_field_array|  2Byte_As|            [array,object]->[]|                            -2|                                                  |Field(So(-1).object, As).array = So(-2).array|
|   69|               push_field_bool|  2Byte_As|              [object]->[bool]|                             0|                                                  |S(-1).bool = Field(So(-1).object, As).bool|
|   70|                push_field_int|  2Byte_As|               [object]->[int]|                             0|                                                  |S(-1).int = Field(So(-1).object, As).int|
|   71|              push_field_int64|  2Byte_As|             [object]->[int64]|                             0|                                                  |S(-1).int64 = Field(So(-1).object, As).int64|
|   72|             push_field_double|  2Byte_As|            [object]->[double]|                             0|                                                  |S(-1).double = Field(So(-1).object, As).double|
|   73|             push_field_string|  2Byte_As|            [object]->[string]|                             0|                                                  |S(-1).string = Field(So(-1).object, As).string|
|   74|           push_field_class_ob|  2Byte_As|            [object]->[object]|                             0|                                                  |S(-1).object = Field(So(-1).object, As).object|
|   75|              push_field_array|  2Byte_As|             [object]->[array]|                             0|                                                  |S(-1).array = Field(So(-1).object, As).array|
|   76|                       add_int|     0Byte|              [int,int]->[int]|                            -1|                                                  ||
|   77|                     add_int64|     0Byte|        [int64,int64]->[int64]|                            -1|                                                  ||
|   78|                    add_double|     0Byte|     [double,double]->[double]|                            -1|                                                  ||
|   79|                       sub_int|     0Byte|              [int,int]->[int]|                            -1|                                                  ||
|   80|                     sub_int64|     0Byte|        [int64,int64]->[int64]|                            -1|                                                  ||
|   81|                    sub_double|     0Byte|     [double,double]->[double]|                            -1|                                                  ||
|   82|                       mul_int|     0Byte|              [int,int]->[int]|                            -1|                                                  ||
|   83|                     mul_int64|     0Byte|        [int64,int64]->[int64]|                            -1|                                                  ||
|   84|                    mul_double|     0Byte|     [double,double]->[double]|                            -1|                                                  ||
|   85|                       div_int|     0Byte|              [int,int]->[int]|                            -1|                                                  ||
|   86|                     div_int64|     0Byte|        [int64,int64]->[int64]|                            -1|                                                  ||
|   87|                    div_double|     0Byte|     [double,double]->[double]|                            -1|                                                  ||
|   88|                       mod_int|     0Byte|              [int,int]->[int]|                            -1|                                                  ||
|   89|                     mod_int64|     0Byte|        [int64,int64]->[int64]|                            -1|                                                  ||
|   90|                    mod_double|     0Byte|     [double,double]->[double]|                            -1|                                                  ||
|   91|                     minus_int|     0Byte|              [int,int]->[int]|                             0|                                                  ||
|   92|                   minus_int64|     0Byte|        [int64,int64]->[int64]|                             0|                                                  ||
|   93|                  minus_double|     0Byte|     [double,double]->[double]|                             0|                                                  ||
|   94|                 self_increase|     0Byte|                              |                             0|                                                  ||
|   95|                 self_decrease|     0Byte|                              |                             0|                                                  ||
|   96|                        concat|     0Byte|                              |                            -1|                                                  ||
|   97|              cast_bool_to_int|     0Byte|                              |                             0|                                                  ||
|   98|            cast_int_to_double|     0Byte|                              |                             0|                                                  ||
|   99|              cast_int_to_bool|     0Byte|                              |                             0|                                                  ||
|  100|            cast_double_to_int|     0Byte|                              |                             0|                                                  ||
|  101|                   logical_and|     0Byte|           [bool,bool]->[bool]|                            -1|                                                  ||
|  102|                    logical_or|     0Byte|           [bool,bool]->[bool]|                            -1|                                                  ||
|  103|                   logical_not|     0Byte|           [bool,bool]->[bool]|                             0|                                                  ||
|  104|                        eq_int|     0Byte|             [int,int]->[bool]|                            -1|                                                  ||
|  105|                      eq_int64|     0Byte|         [int64,int64]->[bool]|                            -1|                                                  ||
|  106|                     eq_double|     0Byte|       [double,double]->[bool]|                            -1|                                                  ||
|  107|                     eq_string|     0Byte|       [string,string]->[bool]|                            -1|                                                  ||
|  108|                        ne_int|     0Byte|             [int,int]->[bool]|                            -1|                                                  ||
|  109|                      ne_int64|     0Byte|         [int64,int64]->[bool]|                            -1|                                                  ||
|  110|                     ne_double|     0Byte|       [double,double]->[bool]|                            -1|                                                  ||
|  111|                     ne_string|     0Byte|       [string,string]->[bool]|                            -1|                                                  ||
|  112|                        gt_int|     0Byte|             [int,int]->[bool]|                            -1|                                                  ||
|  113|                      gt_int64|     0Byte|         [int64,int64]->[bool]|                            -1|                                                  ||
|  114|                     gt_double|     0Byte|       [double,double]->[bool]|                            -1|                                                  ||
|  115|                     gt_string|     0Byte|       [string,string]->[bool]|                            -1|                                                  ||
|  116|                        ge_int|     0Byte|             [int,int]->[bool]|                            -1|                                                  ||
|  117|                      ge_int64|     0Byte|         [int64,int64]->[bool]|                            -1|                                                  ||
|  118|                     ge_double|     0Byte|       [double,double]->[bool]|                            -1|                                                  ||
|  119|                     ge_string|     0Byte|       [string,string]->[bool]|                            -1|                                                  ||
|  120|                        lt_int|     0Byte|             [int,int]->[bool]|                            -1|                                                  ||
|  121|                      lt_int64|     0Byte|         [int64,int64]->[bool]|                            -1|                                                  ||
|  122|                     lt_double|     0Byte|       [double,double]->[bool]|                            -1|                                                  ||
|  123|                     lt_string|     0Byte|       [string,string]->[bool]|                            -1|                                                  ||
|  124|                        le_int|     0Byte|             [int,int]->[bool]|                            -1|                                                  ||
|  125|                      le_int64|     0Byte|         [int64,int64]->[bool]|                            -1|                                                  ||
|  126|                     le_double|     0Byte|       [double,double]->[bool]|                            -1|                                                  ||
|  127|                     le_string|     0Byte|       [string,string]->[bool]|                            -1|                                                  ||
|  128|                          jump|  2Byte_As|                              |                             0|                                                  ||
|  129|                 jump_if_false|  2Byte_As|                              |                            -1|                                                  ||
|  130|                  jump_if_true|  2Byte_As|                              |                            -1|                                                  ||
|  131|                     duplicate|  2Byte_AB|shallow copy value from B to A.|                            +1|                                                  ||
|  132|                     deep_copy|  2Byte_AB|  deep copy value from B to A.|                            +1|                                                  ||
|  133|                  argument_num|   1Byte_A|                              |                            +1|                                                  ||
|  134|                     push_func|  2Byte_As|                              |                            +1|                                                  ||
|  135|                   push_method|  2Byte_As|                              |                            +1|                                                  ||
|  136|            invoke_func_native|     0Byte|                              |                            -1|                                                  ||
|  137|                   invoke_func|     0Byte|                              |                            -1|                                                  ||
|  138|                 invoke_method|     0Byte|                              |                            -2|                                                  ||
|  139|                        return|  2Byte_As|                              |                             0|                                                  ||
|  140|               function_finish|     0Byte|                              |                             0|                                                  ||
|  141|                          exit|   1Byte_A|                              |                             0|                                                  ||
|  142|                new_array_bool|   1Byte_A|                              |                            +1|            create an array of bool with dimension||
|  143|                 new_array_int|   1Byte_A|                              |                            +1|             create an array of int with dimension||
|  144|               new_array_int64|   1Byte_A|                              |                            +1|           create an array of int64 with dimension||
|  145|              new_array_double|   1Byte_A|                              |                            +1|          create an array of double with dimension||
|  146|              new_array_string|   1Byte_A|                              |                            +1|          create an array of string with dimension||
|  147|            new_array_class_ob|  2Byte_AB|                              |                            +1|          create an array of object with dimension||
|  148|        new_array_literal_bool|  2Byte_As|                              |                            +1|              create an array of bool with literal||
|  149|         new_array_literal_int|  2Byte_As|                              |                            +1|               create an array of int with literal||
|  150|       new_array_literal_int64|  2Byte_As|                              |                            +1|             create an array of int64 with literal||
|  151|      new_array_literal_double|  2Byte_As|                              |                            +1|            create an array of double with literal||
|  152|      new_array_literal_string|  2Byte_As|                              |                            +1|            create an array of string with literal||
|  153|    new_array_literal_class_ob| 3Byte_ABs|                              |                            +1|            create an array of object with literal||
|  154|           new_array_literal_a| 3Byte_ABs|                              |                            +1|                                                  ||
|  155|                push_array_len|     0Byte|                              |                             0|                                                  ||
|  156|           push_array_capacity|     0Byte|                              |                             0|                                                  ||
|  157|               push_string_len|     0Byte|                              |                             0|                                                  ||
|  158|          push_string_capacity|     0Byte|                              |                             0|                                                  ||
|  159|          new_class_ob_literal|   1Byte_A|                              |                            +1|                                                  ||
|  160|              range_array_bool|  2Byte_As|                              |                            +1|                        range bool value for array||
|  161|               range_array_int|  2Byte_As|                              |                            +1|                         range int value for array||
|  162|             range_array_int64|  2Byte_As|                              |                            +1|                       range int64 value for array||
|  163|            range_array_double|  2Byte_As|                              |                            +1|                      range double value for array||
|  164|            range_array_string|  2Byte_As|                              |                            +1|                      range string value for array||
|  165|          range_array_class_ob|  2Byte_As|                              |                            +1|                      range object value for array||
|  166|                  range_string|  2Byte_As|                              |                            +1|                       range char value for string||
|  167|              for_range_finish|  2Byte_As|                              |                            +1|                                                  ||
|  168|                 bool_2_string|     0Byte|              [bool]->[string]|                             0|                            convert bool to string|So(-1).string = So(-1).bool|
|  169|                  int_2_string|     0Byte|               [int]->[string]|                             0|                             convert int to string|So(-1).string = So(-1).int|
|  170|                int64_2_string|     0Byte|               [int]->[string]|                             0|                           convert int64 to string|So(-1).string = So(-1).int64|
|  171|               double_2_string|     0Byte|            [double]->[string]|                             0|                          convert double to string|So(-1).string = So(-1).double|
|  172|                           num|     0Byte|                              |                             0|                                                  ||


### 操作数类型说明

- 0Byte: 无操作数

- 1Byte_A: 1字节操作数A

- 2Byte_As: 2字节操作数A

- 2Byte_AB: 1字节操作数A和1字节操作数B

- 3Byte_ABs: 1字节操作数A和2字节操作数B



### 操作数公式说明

```

math_formula 字段是如何通过数学公式描述一个字节码所对应的 VirtualMachine 操作行为

K(1)  通过index 1 , 来操作 static 空间
Si(1) 通过 index 1 , 来操作 stack 空间
So(1) 通过 offset 1 , 来操作 stack 空间
C(1)  通过index 1, 从ConstantPool  Constant

Field(object, As).int 将object的第As个Field作为int赋值

A As AB Bs 分别代表字节码后边的操作数
FSB 代表 FunctionStackBase

```
