# Ring 虚拟机（Virtual Machine）

在 *Ring* 中的虚拟机设计和实现中，采用的是栈式虚拟机。




> [!TIP|style:flat|label:Register-Based VM]
> Stack Based vs Register Based Virtual Machine Architecture
> 
> https://www.codeproject.com/Articles/461052/Stack-Based-vs-Register-Based-Virtual-Machine-Arch


## 1. Ring Stacked-Based VM 指令集

| 指令                     | 操作数占用字节数 | 栈顶值变化                | 栈高度 | 含义                                   |
| ------------------------ | ---------------- | ------------------------- | ------ | -------------------------------------- |
| push_bool                | 1                | []-->[int]                | +1     | push constant bool value to stack      |
| push_int_1byte           | 1                | []-->[int]                | +1     | push 1byte int constant value to stack |
| push_int_2byte           | 2                | []-->[int]                | +1     | push 2byte int constant value to stack |
| push_int                 | 2                | []-->[int]                | +1     | push constant int value to stack       |
| push_double              | 2                | []-->[double]             | +1     | push constant double value to stack    |
| push_string              | 2                | []-->[object]             | +1     | push constant string value to stack    |
| pop_static_bool          | 2                |                           | -1     |                                        |
| pop_static_int           | 2                |                           | -1     |                                        |
| pop_static_double        | 2                |                           | -1     |                                        |
| pop_static_object        | 2                |                           | -1     |                                        |
| push_static_bool         | 2                |                           | +1     |                                        |
| push_static_int          | 2                |                           | +1     |                                        |
| push_static_double       | 2                |                           | +1     |                                        |
| push_static_object       | 2                |                           | +1     |                                        |
| pop_stack_bool           | 2                |                           | -1     |                                        |
| pop_stack_int            | 2                |                           | -1     |                                        |
| pop_stack_double         | 2                |                           | -1     |                                        |
| pop_stack_object         | 2                |                           | -1     |                                        |
| push_stack_bool          | 2                |                           | +1     |                                        |
| push_stack_int           | 2                |                           | +1     |                                        |
| push_stack_double        | 2                |                           | +1     |                                        |
| push_stack_object        | 2                |                           | +1     |                                        |
| push_array_bool          | 0                |                           | -1     |                                        |
| push_array_int           | 0                |                           | -1     |                                        |
| push_array_double        | 0                |                           | -1     |                                        |
| push_array_string        | 0                |                           | -1     |                                        |
| push_array_object        | 0                |                           | -1     |                                        |
| pop_array_bool           | 0                | [int,object,int]->[]      | -3     | assign to bool array by index          |
| pop_array_int            | 0                | [int,object,int]->[]      | -3     | assign to int array by index           |
| pop_array_double         | 0                | [int,object,int]->[]      | -3     | assign to double array by index        |
| pop_array_string         | 0                | [int,object,int]->[]      | -3     | assign to string array by index        |
| pop_array_object         | 0                | [int,object,int]->[]      | -3     | assign to object array by index        |
| array_append_bool        | 0                | [object,bool]->[]         | -2     | assign to object array by index        |
| array_append_int         | 0                | [object,int]->[]          | -2     | assign to object array by index        |
| array_append_double      | 0                | [object,double]->[]       | -2     | assign to object array by index        |
| array_append_string      | 0                | [object,string]->[]       | -2     | assign to object array by index        |
| array_append_object      | 0                | [object,object]->[]       | -2     | assign to object array by index        |
| array_pop_bool           | 0                | [object]->[bool]          | 0      | assign to object array by index        |
| array_pop_int            | 0                | [object]->[int]           | 0      | assign to object array by index        |
| array_pop_double         | 0                | [object]->[double]        | 0      | assign to object array by index        |
| array_pop_string         | 0                | [object]->[string]        | 0      | assign to object array by index        |
| array_pop_object         | 0                | [object]->[object]        | 0      | assign to object array by index        |
| pop_field_bool           | 2                | [bool,object]->[]         | -1     | assign to class field whith bool       |
| pop_field_int            | 2                | [int,object]->[]          | -1     |                                        |
| pop_field_double         | 2                | [double,object]->[]       | -1     |                                        |
| push_field_bool          | 2                | [object]->[bool]          | +1     |                                        |
| push_field_int           | 2                | [object]->[int]           | +1     |                                        |
| push_field_double        | 2                | [object]->[double]        | +1     |                                        |
| add_int                  | 0                | [int,int]->[int]          | -1     |                                        |
| add_double               | 0                | [double,double]->[double] | -1     |                                        |
| sub_int                  | 0                | [int,int]->[int]          | -1     |                                        |
| sub_double               | 0                | [double,double]->[double] | -1     |                                        |
| mul_int                  | 0                | [int,int]->[int]          | -1     |                                        |
| mul_double               | 0                | [double,double]->[double] | -1     |                                        |
| div_int                  | 0                | [int,int]->[int]          | -1     |                                        |
| div_double               | 0                | [double,double]->[double] | -1     |                                        |
| mod_int                  | 0                | [int,int]->[int]          | -1     |                                        |
| mod_double               | 0                | [double,double]->[double] | -1     |                                        |
| minus_int                | 0                | [int,int]->[int]          | 0      |                                        |
| minus_double             | 0                | [double,double]->[double] | 0      |                                        |
| increase_suffix          | 0                |                           | 0      |                                        |
| increase_prefix          | 0                |                           | 0      |                                        |
| decrease_suffix          | 0                |                           | 0      |                                        |
| decrease_prefix          | 0                |                           | 0      |                                        |
| concat                   | 0                |                           | -1     |                                        |
| cast_bool_to_int         | 0                |                           | 0      |                                        |
| cast_int_to_double       | 0                |                           | 0      |                                        |
| cast_int_to_bool         | 0                |                           | 0      |                                        |
| cast_double_to_int       | 0                |                           | 0      |                                        |
| logical_and              | 0                |                           | -1     |                                        |
| logical_or               | 0                |                           | -1     |                                        |
| logical_not              | 0                |                           | 0      |                                        |
| eq_int                   | 0                |                           | -1     |                                        |
| eq_double                | 0                |                           | -1     |                                        |
| eq_string                | 0                |                           | -1     |                                        |
| ne_int                   | 0                |                           | -1     |                                        |
| ne_double                | 0                |                           | -1     |                                        |
| ne_string                | 0                |                           | -1     |                                        |
| gt_int                   | 0                |                           | -1     |                                        |
| gt_double                | 0                |                           | -1     |                                        |
| gt_string                | 0                |                           | -1     |                                        |
| ge_int                   | 0                |                           | -1     |                                        |
| ge_double                | 0                |                           | -1     |                                        |
| ge_string                | 0                |                           | -1     |                                        |
| lt_int                   | 0                |                           | -1     |                                        |
| lt_double                | 0                |                           | -1     |                                        |
| lt_string                | 0                |                           | -1     |                                        |
| le_int                   | 0                |                           | -1     |                                        |
| le_double                | 0                |                           | -1     |                                        |
| le_string                | 0                |                           | -1     |                                        |
| jump                     | 2                |                           | 0      |                                        |
| jump_if_false            | 2                |                           | -1     |                                        |
| jump_if_true             | 2                |                           | -1     |                                        |
| duplicate                | 0                |                           | +1     |                                        |
| push_func                | 2                |                           | +1     |                                        |
| push_method              | 2                |                           | +1     |                                        |
| argument_num             | 1                |                           | 0      |                                        |
| invoke_func              | 0                |                           | -1     |                                        |
| invoke_method            | 0                |                           | -2     |                                        |
| return                   | 2                |                           | 0      |                                        |
| function_finish          | 0                |                           | 0      |                                        |
| exit                     | 1                |                           | 0      |                                        |
| new_array_bool           | 2                |                           | +1     |                                        |
| new_array_int            | 2                |                           | +1     |                                        |
| new_array_double         | 2                |                           | +1     |                                        |
| new_array_string         | 2                |                           | +1     |                                        |
| new_array_object         | 2                |                           | +1     |                                        |
| new_array_literal_bool   | 2                |                           | +1     |                                        |
| new_array_literal_int    | 2                |                           | +1     |                                        |
| new_array_literal_double | 2                |                           | +1     |                                        |
| new_array_literal_string | 2                |                           | +1     |                                        |
| new_array_literal_object | 2                |                           | +1     |                                        |
| push_array_len           | 0                |                           | 0      |                                        |
| push_array_capacity      | 0                |                           | 0      |                                        |
| push_string_len          | 0                |                           | 0      |                                        |
| push_string_capacity     | 0                |                           | 0      |                                        |
| new_class_object_literal | 2                |                           | +1     |                                        |
| range_array_bool         | 2                |                           | +1     | range bool value for array             |
| range_array_int          | 2                |                           | +1     | range int value for array              |
| range_array_double       | 2                |                           | +1     | range double value for array           |
| range_array_string       | 2                |                           | +1     | range string value for array           |
| range_array_object       | 2                |                           | +1     | range object value for array           |
| range_string             | 2                |                           | +1     | range char value for string            |
| for_range                | 2                |                           | 0      |                                        |
| for_range_finish         | 2                |                           | +1     |                                        |
| bool_2_string            | 0                | [bool]->[string]          | 0      | convert bool to string                 |
| int_2_string             | 0                | [int]->[string]           | 0      | convert int to string                  |
| double_2_string          | 0                | [double]->[string]        | 0      | convert double to string               |
|                          | 0                |                           | 0      |                                        |


## 2. 虚拟机指令集翻译示例
如Ring代码：

```ring

1+2*3*4*5-6*7+8*9;


```

会被翻译成如下栈式虚拟机代码：

```s

[opcode]          0        push_int          1
[opcode]          2        push_int          2
[opcode]          4        push_int          3
[opcode]          6         mul_int          0
[opcode]          8        push_int          4
[opcode]         10         mul_int          0
[opcode]         12        push_int          5
[opcode]         14         mul_int          0
[opcode]         16         add_int          0
[opcode]         18        push_int          6
[opcode]         20        push_int          7
[opcode]         22         mul_int          0
[opcode]         24         sub_int          0
[opcode]         26        push_int          8
[opcode]         28        push_int          9
[opcode]         30         mul_int          0
[opcode]         32         add_int          0
[opcode]         34        push_int          2
[opcode]         36        push_int          3
[opcode]         38         mod_int          0
[opcode]         40        push_int          6
[opcode]         42        push_int          2
[opcode]         44         mod_int          0

```


## 3. 如何调试栈虚拟机

编译 Ring 时，在makefile中添加 -DDEBUG -DDEBUG_RVM_INTERACTIVE，开起debug模式，开始debug虚拟机模式


编辑如下 Ring 源码：

```ring

1+2*3*4*5-6*7+8*9;

```

Debug 虚拟机演示：


演示图：