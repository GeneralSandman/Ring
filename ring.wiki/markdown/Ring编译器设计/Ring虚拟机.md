# Ring 虚拟机（Virtual Machine）

在 *Ring* 中的虚拟机设计和实现中，采用的是栈式虚拟机。




> [!TIP|style:flat|label:Register-Based VM]
> Stack Based vs Register Based Virtual Machine Architecture
> 
> https://www.codeproject.com/Articles/461052/Stack-Based-vs-Register-Based-Virtual-Machine-Arch



## 1. Ring Stacked-Based VM 指令集

| 指令               | 操作数占用字节数 | 栈顶值变化                  | 栈高度 | 含义                               |
| ------------------ | ---------------- | --------------------------- | ------ | ---------------------------------- |
| push_int_1byte     | 1                | ()-->(int)                  | +1     | 将1字节的int常量入栈               |
| push_int_2byte     | 2                | ()-->(int)                  | +1     | 将2字节的int常量入栈               |
| push_int           | 2                | ()-->(int)                  | +1     | 将大于2字节的int常量索引入栈       |
| push_double        | 2                | ()-->(int)                  | +1     | double常量索引入栈                 |
| push_string        | 2                | ()-->(int)                  | +1     | string常量索引入栈                 |
|                    |                  |                             |        |                                    |
|                    |                  |                             |        |                                    |
| pop_static_int     | 2                | (int)-->()                  | -1     | 全局变量int索引出栈，赋值运算。    |
| pop_static_double  | 2                | (double)-->()               | -1     | 全局变量double索引出栈，赋值运算。 |
| pop_static_object  | 2                | (object)-->()               | -1     | 全局变量object索引出栈，赋值运算。 |
| push_static_int    | 2                | ()-->(int)                  | +1     | 全局变量int索引入栈                |
| push_static_double | 2                | ()-->(double)               | +1     | 全局变量double索引入栈             |
| push_static_object | 2                | ()-->(object)               | +1     | 全局变量object索引入栈             |
|                    |                  |                             |        |                                    |
|                    |                  |                             |        |                                    |
| pop_stack_int      | 2                | (int)-->()                  | -1     | 局部变量int索引出栈，赋值运算。    |
| pop_stack_double   | 2                | (double)-->()               | -1     | 局部变量double索引出栈，赋值运算。 |
| pop_stack_object   | 2                | (object)-->()               | -1     | 局部变量object索引出栈，赋值运算。 |
| push_stack_int     | 2                | ()-->(int)                  | +1     | 局部变量int索引入栈                |
| push_stack_double  | 2                | ()-->(double)               | +1     | 局部变量double索引入栈             |
| push_stack_object  | 2                | ()-->(object)               | +1     | 局部变量object索引入栈             |
|                    |                  |                             |        |                                    |
|                    |                  |                             |        |                                    |
| add_int            | 0                | (int,int)-->(int)           | -1     | 算术 加法                          |
| add_double         | 0                | (double,double)-->(double)  | -1     | 算术 加法                          |
| add_string         | 0                |                             | -1     | 算术 加法                          |
|                    |                  |                             |        |                                    |
| sub_int            | 0                | (int,int)-->(int)           | -1     | 算术 减法                          |
| sub_double         | 0                | (double,double)-->(double)  | -1     | 算术 减法                          |
|                    |                  |                             |        |                                    |
| mul_int            | 0                | (int,int)-->(int)           | -1     | 算术 乘法                          |
| mul_double         | 0                | (double,double)-->(double)  | -1     | 算术 乘法                          |
|                    |                  |                             |        |                                    |
| div_int            | 0                | (int,int)-->(int)           | -1     | 算术 除法                          |
| div_double         | 0                | (double,double)-->(double)  | -1     | 算术 除法                          |
|                    |                  |                             |        |                                    |
| mod_int            | 0                | (int,int)-->(int)           | -1     | 算术 取模                          |
| mod_double         | 0                | (double,double)-->(double)  | -1     | 算术 取模                          |
|                    |                  |                             |        |                                    |
| minus_int          | 0                | (int)-->(int)               | 0      | 取负数                             |
| minus_double       | 0                | (double)-->(double)         | 0      | 取负数                             |
|                    |                  |                             |        |                                    |
| increase_suffix    | 0                | (int/double)-->(int/double) | 0      | 栈顶值后缀自增                     |
| increase_suffix    | 0                | (int/double)-->(int/double) | 0      | 栈顶值前缀自增                     |
| decrease_suffix    | 0                | (int/double)-->(int/double) | 0      | 栈顶值后缀自减                     |
| decrease_prefix    | 0                | (int/double)-->(int/double) | 0      | 栈顶值前缀自减                     |
|                    |                  |                             |        |                                    |
|                    |                  |                             |        |                                    |
| logical_and        | 0                | (int,int)-->(int)           | -1     | 逻辑 与                            |
| logical_or         | 0                | (int,int)-->(int)           | -1     | 逻辑 或                            |
| logical_not        | 0                | (int,int)-->(int)           | 0      | 逻辑 非                            |
|                    |                  |                             |        |                                    |
|                    |                  |                             |        |                                    |
| eq_int             | 0                | (int,int)-->(int)           | -1     | 关系运算 等于 =                    |
| eq_double          | 0                | (double,double)-->(int)     | -1     | 关系运算 等于 =                    |
| eq_string          | 0                |                             | -1     | 关系运算 等于 =                    |
|                    |                  |                             |        |                                    |
| ne_int             | 0                | (int,int)-->(int)           | -1     | 关系运算 不等于 !=                 |
| ne_double          | 0                | (double,double)-->(int)     | -1     | 关系运算 不等于 !=                 |
| ne_string          | 0                |                             | -1     | 关系运算 不等于 !=                 |
|                    |                  |                             |        |                                    |
| gt_int             | 0                |                             | -1     | 关系运算 大于 >                    |
| gt_double          | 0                | (double,double)-->(int)     | -1     | 关系运算 大于 >                    |
| gt_string          | 0                |                             | -1     | 关系运算 大于 >                    |
|                    |                  |                             |        |                                    |
| ge_int             | 0                | (int,int)-->(int)           | -1     | 关系运算 大于等于 >=               |
| ge_double          | 0                | (double,double)-->(int)     | -1     | 关系运算 大于等于 >=               |
| ge_string          | 0                |                             | -1     | 关系运算 大于等于 >=               |
|                    |                  |                             |        |                                    |
| lt_int             | 0                | (int,int)-->(int)           | -1     | 关系运算 小于 <                    |
| lt_double          | 0                | (double,double)-->(int)     | -1     | 关系运算 小于 <                    |
| lt_string          | 0                |                             | -1     | 关系运算 小于 <                    |
|                    |                  |                             |        |                                    |
| le_int             | 0                | (int,int)-->(int)           | -1     | 关系运算 小于 <=                   |
| le_double          | 0                | (double,double)-->(int)     | -1     | 关系运算 小于 <=                   |
| le_string          | 0                |                             | -1     | 关系运算 小于 <=                   |
|                    |                  |                             |        |                                    |
| jump               | 2                |                             | 0      | 无条件跳转                         |
| jump_if_false      | 2                | (int)-->()                  | -1     | 判断栈顶为false后跳转              |
| jump_if_true       | 2                | (int)-->()                  | -1     | 判断栈顶为true后跳转               |
|                    |                  |                             |        |                                    |
| duplicate          | 0                | (int)-->(int,int)           | 1      | 赋值栈顶值添加到栈顶               |
|                    |                  |                             |        |                                    |
| push_func          | 2                | ()-->(int)                  | 1      | 函数索引                           |
| invoke_func        | 0                | (int)-->()                  | -1     | 调用函数                           |
| return             | 2                |                             | 0      |                                    |
| function_finish    | 0                |                             | 0      |                                    |






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