# ```Ring```虚拟机（Virtual Machine）```RVM```

在```Ring```中的虚拟机设计和实现中，采用的是栈式虚拟机。


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
