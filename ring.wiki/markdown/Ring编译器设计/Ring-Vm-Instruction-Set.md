# Ring VitrualMachine Instruction Set

## 1. Ring Stacked-Based VM 指令集

| Num | 指令                       | 操作数类型 | 栈顶值变化                | 栈高度 | 含义                                         | 公式描述                                          |
| --- | -------------------------- | ---------- | ------------------------- | ------ | -------------------------------------------- | ------------------------------------------------- |
| 1   | push_bool                  | 1Byte_A    | []-->[int]                | +1     | push constant bool value to stack            | So(0).bool = A.bool                               |
| 2   | push_int_1byte             | 1Byte_A    | []-->[int]                | +1     | push 1byte int constant value to stack       | So(0).int = A.int                                 |
| 3   | push_int_2byte             | 2Byte_As   | []-->[int]                | +1     | push 2byte int constant value to stack       | So(0).int = As.int                                |
| 4   | push_int                   | 2Byte_As   | []-->[int]                | +1     | push constant int value to stack             | So(0).int = C(As).int                             |
| 5   | push_int64                 | 2Byte_As   | []-->[int]                | +1     | push constant int64 value to stack           | So(0).int64 = C(As).int64                         |
| 6   | push_double                | 2Byte_As   | []-->[double]             | +1     | push constant double value to stack          | So(0).double = C(As).double                       |
| 7   | push_string                | 2Byte_As   | []-->[string]             | +1     | push constant string value to stack          | So(0).string = C(As).string                       |
| 8   | pop_static_bool            | 2Byte_As   | [bool]-->[]               | -1     | bool assign to global-variable               | K(As) = So(-1).bool                               |
| 9   | pop_static_int             | 2Byte_As   | [int]-->[]                | -1     | int assign to global-variable                | K(As) = So(-1).int                                |
| 10  | pop_static_int64           | 2Byte_As   | [int64]-->[]              | -1     | int64 assign to global-variable              | K(As) = So(-1).int64                              |
| 11  | pop_static_double          | 2Byte_As   | [double]-->[]             | -1     | double assign to global-variable             | K(As) = So(-1).double                             |
| 12  | pop_static_string          | 2Byte_As   | [string]-->[]             | -1     | string assign to global-variable             | K(As) = So(-1).string                             |
| 13  | pop_static_class_ob        | 2Byte_As   | [object]-->[]             | -1     | class-object assign to global-variable       | K(As) = So(-1).object                             |
| 14  | pop_static_array           | 2Byte_As   | [array]-->[]              | -1     | array assign to global-variable              | K(As) = So(-1).array                              |
| 15  | push_static_bool           | 2Byte_As   | []-->[bool]               | +1     | push global-variable's bool to stack         | So(0).bool = K(As)                                |
| 16  | push_static_int            | 2Byte_As   | []-->[int]                | +1     | push global-variable's int to stack          | So(0).int = K(As)                                 |
| 17  | push_static_int64          | 2Byte_As   | []-->[int64]              | +1     | push global-variable's int64 to stack        | So(0).int64 = K(As)                               |
| 18  | push_static_double         | 2Byte_As   | []-->[double]             | +1     | push global-variable's double to stack       | So(0).double = K(As)                              |
| 19  | push_static_string         | 2Byte_As   | []-->[string]             | +1     | push global-variable's string to stack       | So(0).string = K(As)                              |
| 20  | push_static_class_ob       | 2Byte_As   | []-->[object]             | +1     | push global-variable's class-object to stack | So(0).object = K(As)                              |
| 21  | push_static_array          | 2Byte_As   | []-->[array]              | +1     | push global-variable's array to stack        | So(0).array = K(As)                               |
| 22  | pop_stack_bool             | 2Byte_As   |                           | -1     | bool assign to local-variable                | Si(FSB+As).bool = S(-1).bool                      |
| 23  | pop_stack_int              | 2Byte_As   |                           | -1     | int assign to local-variable                 | Si(FSB+As).int = S(-1).int                        |
| 24  | pop_stack_int64            | 2Byte_As   |                           | -1     | int64 assign to local-variable               | Si(FSB+As).int64 = S(-1).int64                    |
| 25  | pop_stack_double           | 2Byte_As   |                           | -1     | double assign to local-variable              | Si(FSB+As).double = S(-1).double                  |
| 26  | pop_stack_string           | 2Byte_As   |                           | -1     | string assign to local-variable              | Si(FSB+As).string = S(-1).string                  |
| 27  | pop_stack_class_ob         | 2Byte_As   |                           | -1     | class-object assign to local-variable        | Si(FSB+As).object = S(-1).object                  |
| 28  | pop_stack_array            | 2Byte_As   |                           | -1     | array assign to local-variable               | Si(FSB+As).array = S(-1).array                    |
| 29  | pop_stack_closure          | 2Byte_As   |                           | -1     | closure assign to local-variable             | Si(FSB+As).func = S(-1).func                      |
| 30  | push_stack_bool            | 2Byte_As   |                           | +1     | push local-variable's bool to stack          | So(0).bool = Si(FSB+As).bool                      |
| 31  | push_stack_int             | 2Byte_As   |                           | +1     | push local-variable's int to stack           | So(0).int = Si(FSB+As).int                        |
| 32  | push_stack_int64           | 2Byte_As   |                           | +1     | push local-variable's int64 to stack         | So(0).int64 = Si(FSB+As).int64                    |
| 33  | push_stack_double          | 2Byte_As   |                           | +1     | push local-variable's double to stack        | So(0).double = Si(FSB+As).double                  |
| 34  | push_stack_string          | 2Byte_As   |                           | +1     | push local-variable's string to stack        | So(0).string = Si(FSB+As).string                  |
| 35  | push_stack_class_ob        | 2Byte_As   |                           | +1     | push local-variable's class-object to stack  | So(0).object = Si(FSB+As).object                  |
| 36  | push_stack_array           | 2Byte_As   |                           | +1     | push local-variable's array to stack         | So(0).array = Si(FSB+As).array                    |
| 37  | push_stack_closure         | 2Byte_As   |                           | +1     | push local-variable's closure to stack       | So(0).closure = Si(FSB+As).closure                |
| 38  | pop_free_bool              | 2Byte_As   |                           | -1     | bool assign to local-variable                | Fi(FSB+As).bool = S(-1).bool                      |
| 39  | pop_free_int               | 2Byte_As   |                           | -1     | int assign to local-variable                 | Fi(FSB+As).int = S(-1).int                        |
| 40  | pop_free_int64             | 2Byte_As   |                           | -1     | int64 assign to local-variable               | Fi(FSB+As).int64 = S(-1).int64                    |
| 41  | pop_free_double            | 2Byte_As   |                           | -1     | double assign to local-variable              | Fi(FSB+As).double = S(-1).double                  |
| 42  | pop_free_string            | 2Byte_As   |                           | -1     | string assign to local-variable              | Fi(FSB+As).string = S(-1).string                  |
| 43  | pop_free_class_ob          | 2Byte_As   |                           | -1     | class-object assign to local-variable        | Fi(FSB+As).object = S(-1).object                  |
| 44  | pop_free_array             | 2Byte_As   |                           | -1     | array assign to local-variable               | Fi(FSB+As).array = S(-1).array                    |
| 45  | push_free_bool             | 2Byte_As   |                           | +1     | push local-variable's bool to stack          | So(0).bool = Fi(FSB+As).bool                      |
| 46  | push_free_int              | 2Byte_As   |                           | +1     | push local-variable's int to stack           | So(0).int = Fi(FSB+As).int                        |
| 47  | push_free_int64            | 2Byte_As   |                           | +1     | push local-variable's int64 to stack         | So(0).int64 = Fi(FSB+As).int64                    |
| 48  | push_free_double           | 2Byte_As   |                           | +1     | push local-variable's double to stack        | So(0).double = Fi(FSB+As).double                  |
| 49  | push_free_string           | 2Byte_As   |                           | +1     | push local-variable's string to stack        | So(0).string = Fi(FSB+As).string                  |
| 50  | push_free_class_ob         | 2Byte_As   |                           | +1     | push local-variable's class-object to stack  | So(0).object = Fi(FSB+As).object                  |
| 51  | push_free_array            | 2Byte_As   |                           | +1     | push local-variable's class-object to stack  | So(0).array = Fi(FSB+As).array                    |
| 52  | push_array_a               | 0Byte      |                           | -1     |                                              |                                                   |
| 53  | push_array_bool            | 0Byte      |                           | -1     |                                              |                                                   |
| 54  | push_array_int             | 0Byte      |                           | -1     |                                              |                                                   |
| 55  | push_array_int64           | 0Byte      |                           | -1     |                                              |                                                   |
| 56  | push_array_double          | 0Byte      |                           | -1     |                                              |                                                   |
| 57  | push_array_string          | 0Byte      |                           | -1     |                                              |                                                   |
| 58  | push_array_class_ob        | 0Byte      |                           | -1     |                                              |                                                   |
| 59  | push_array_closure         | 0Byte      |                           | -1     |                                              |                                                   |
| 60  | pop_array_a                | 0Byte      |                           | -3     |                                              |                                                   |
| 61  | pop_array_bool             | 0Byte      | [int,object,int]->[]      | -3     | assign to bool array by index                |                                                   |
| 62  | pop_array_int              | 0Byte      | [int,object,int]->[]      | -3     | assign to int array by index                 |                                                   |
| 63  | pop_array_int64            | 0Byte      | [int,object,int]->[]      | -3     | assign to int64 array by index               |                                                   |
| 64  | pop_array_double           | 0Byte      | [int,object,int]->[]      | -3     | assign to double array by index              |                                                   |
| 65  | pop_array_string           | 0Byte      | [int,object,int]->[]      | -3     | assign to string array by index              |                                                   |
| 66  | pop_array_class_ob         | 0Byte      | [int,object,int]->[]      | -3     | assign to object array by index              |                                                   |
| 67  | pop_array_closure          | 0Byte      | [int,object,int]->[]      | -3     | assign to object array by index              |                                                   |
| 68  | array_append_a             | 0Byte      | [array,array]->[]         | -2     | assign to object array by index              |                                                   |
| 69  | array_append_bool          | 0Byte      | [array,bool]->[]          | -2     | assign to object array by index              |                                                   |
| 70  | array_append_int           | 0Byte      | [array,int]->[]           | -2     | assign to object array by index              |                                                   |
| 71  | array_append_int64         | 0Byte      | [array,int64]->[]         | -2     | assign to object array by index              |                                                   |
| 72  | array_append_double        | 0Byte      | [array,double]->[]        | -2     | assign to object array by index              |                                                   |
| 73  | array_append_string        | 0Byte      | [array,string]->[]        | -2     | assign to object array by index              |                                                   |
| 74  | array_append_class_ob      | 0Byte      | [array,class-ob]->[]      | -2     | assign to object array by index              |                                                   |
| 75  | array_append_closure       | 0Byte      | [array,closure]->[]       | -2     | assign to object array by index              |                                                   |
| 76  | array_pop_a                | 0Byte      | [array]->[array]          | 0      | assign to object array by index              |                                                   |
| 77  | array_pop_bool             | 0Byte      | [array]->[bool]           | 0      | assign to object array by index              |                                                   |
| 78  | array_pop_int              | 0Byte      | [array]->[int]            | 0      | assign to object array by index              |                                                   |
| 79  | array_pop_int64            | 0Byte      | [array]->[int64]          | 0      | assign to object array by index              |                                                   |
| 80  | array_pop_double           | 0Byte      | [array]->[double]         | 0      | assign to object array by index              |                                                   |
| 81  | array_pop_string           | 0Byte      | [array]->[string]         | 0      | assign to object array by index              |                                                   |
| 82  | array_pop_class_ob         | 0Byte      | [array]->[class-ob]       | 0      | assign to object array by index              |                                                   |
| 83  | array_pop_closure          | 0Byte      | [array]->[closure]        | 0      | assign to object array by index              |                                                   |
| 84  | new_array_bool             | 1Byte_A    |                           | -A+1   | create an array of bool with dimension       |                                                   |
| 85  | new_array_int              | 1Byte_A    |                           | -A+1   | create an array of int with dimension        |                                                   |
| 86  | new_array_int64            | 1Byte_A    |                           | -A+1   | create an array of int64 with dimension      |                                                   |
| 87  | new_array_double           | 1Byte_A    |                           | -A+1   | create an array of double with dimension     |                                                   |
| 88  | new_array_string           | 1Byte_A    |                           | -A+1   | create an array of string with dimension     |                                                   |
| 89  | new_array_class_ob         | 2Byte_AB   |                           | -A+1   | create an array of object with dimension     |                                                   |
| 90  | new_array_closure          | 1Byte_A    |                           | -A+1   | create an array of closure with dimension    |                                                   |
| 91  | new_array_literal_bool     | 2Byte_As   |                           | -As+1  | create an array of bool with literal         |                                                   |
| 92  | new_array_literal_int      | 2Byte_As   |                           | -As+1  | create an array of int with literal          |                                                   |
| 93  | new_array_literal_int64    | 2Byte_As   |                           | -As+1  | create an array of int64 with literal        |                                                   |
| 94  | new_array_literal_double   | 2Byte_As   |                           | -As+1  | create an array of double with literal       |                                                   |
| 95  | new_array_literal_string   | 2Byte_As   |                           | -As+1  | create an array of string with literal       |                                                   |
| 96  | new_array_literal_class_ob | 3Byte_AsB  |                           | -As+1  | create an array of object with literal       |                                                   |
| 97  | new_array_literal_closure  | 2Byte_As   |                           | -As+1  | create an array of closure with literal      |                                                   |
| 98  | new_array_literal_a        | 4Byte_ABCs |                           | -Cs+1  |                                              |                                                   |
| 99  | range_array_a              | 2Byte_As   |                           | +1     | range array value for array                  |                                                   |
| 100 | range_array_bool           | 2Byte_As   |                           | +1     | range bool value for array                   |                                                   |
| 101 | range_array_int            | 2Byte_As   |                           | +1     | range int value for array                    |                                                   |
| 102 | range_array_int64          | 2Byte_As   |                           | +1     | range int64 value for array                  |                                                   |
| 103 | range_array_double         | 2Byte_As   |                           | +1     | range double value for array                 |                                                   |
| 104 | range_array_string         | 2Byte_As   |                           | +1     | range string value for array                 |                                                   |
| 105 | range_array_class_ob       | 2Byte_As   |                           | +1     | range object value for array                 |                                                   |
| 106 | range_array_closure        | 2Byte_As   |                           | +1     | range closure value for array                |                                                   |
| 107 | for_range_finish           | 2Byte_As   |                           | -2     |                                              |                                                   |
| 108 | new_class_ob_literal       | 1Byte_A    |                           | +1     |                                              |                                                   |
| 109 | pop_field_bool             | 2Byte_As   | [bool,object]->[]         | -2     | assign to class field whith bool             | Field(So(-1).object, As).bool = So(-2).bool       |
| 110 | pop_field_int              | 2Byte_As   | [int,object]->[]          | -2     |                                              | Field(So(-1).object, As).int = So(-2).int         |
| 111 | pop_field_int64            | 2Byte_As   | [int64,object]->[]        | -2     |                                              | Field(So(-1).object, As).int64 = So(-2).int64     |
| 112 | pop_field_double           | 2Byte_As   | [double,object]->[]       | -2     |                                              | Field(So(-1).object, As).double = So(-2).double   |
| 113 | pop_field_string           | 2Byte_As   | [string,object]->[]       | -2     |                                              | Field(So(-1).object, As).string = So(-2).string   |
| 114 | pop_field_class_ob         | 2Byte_As   | [object,object]->[]       | -2     |                                              | Field(So(-1).object, As).object = So(-2).object   |
| 115 | pop_field_array            | 2Byte_As   | [array,object]->[]        | -2     |                                              | Field(So(-1).object, As).array = So(-2).array     |
| 116 | pop_field_closure          | 2Byte_As   | [closure,object]->[]      | -2     |                                              | Field(So(-1).object, As).closure = So(-2).closure |
| 117 | push_field_bool            | 2Byte_As   | [object]->[bool]          | 0      |                                              | S(-1).bool = Field(So(-1).object, As).bool        |
| 118 | push_field_int             | 2Byte_As   | [object]->[int]           | 0      |                                              | S(-1).int = Field(So(-1).object, As).int          |
| 119 | push_field_int64           | 2Byte_As   | [object]->[int64]         | 0      |                                              | S(-1).int64 = Field(So(-1).object, As).int64      |
| 120 | push_field_double          | 2Byte_As   | [object]->[double]        | 0      |                                              | S(-1).double = Field(So(-1).object, As).double    |
| 121 | push_field_string          | 2Byte_As   | [object]->[string]        | 0      |                                              | S(-1).string = Field(So(-1).object, As).string    |
| 122 | push_field_class_ob        | 2Byte_As   | [object]->[object]        | 0      |                                              | S(-1).object = Field(So(-1).object, As).object    |
| 123 | push_field_array           | 2Byte_As   | [object]->[array]         | 0      |                                              | S(-1).array = Field(So(-1).object, As).array      |
| 124 | push_field_closure         | 2Byte_As   | [object]->[array]         | 0      |                                              | S(-1).closure = Field(So(-1).object, As).closure  |
| 125 | add_int                    | 0Byte      | [int,int]->[int]          | -1     |                                              |                                                   |
| 126 | add_int64                  | 0Byte      | [int64,int64]->[int64]    | -1     |                                              |                                                   |
| 127 | add_double                 | 0Byte      | [double,double]->[double] | -1     |                                              |                                                   |
| 128 | sub_int                    | 0Byte      | [int,int]->[int]          | -1     |                                              |                                                   |
| 129 | sub_int64                  | 0Byte      | [int64,int64]->[int64]    | -1     |                                              |                                                   |
| 130 | sub_double                 | 0Byte      | [double,double]->[double] | -1     |                                              |                                                   |
| 131 | mul_int                    | 0Byte      | [int,int]->[int]          | -1     |                                              |                                                   |
| 132 | mul_int64                  | 0Byte      | [int64,int64]->[int64]    | -1     |                                              |                                                   |
| 133 | mul_double                 | 0Byte      | [double,double]->[double] | -1     |                                              |                                                   |
| 134 | div_int                    | 0Byte      | [int,int]->[int]          | -1     |                                              |                                                   |
| 135 | div_int64                  | 0Byte      | [int64,int64]->[int64]    | -1     |                                              |                                                   |
| 136 | div_double                 | 0Byte      | [double,double]->[double] | -1     |                                              |                                                   |
| 137 | mod_int                    | 0Byte      | [int,int]->[int]          | -1     |                                              |                                                   |
| 138 | mod_int64                  | 0Byte      | [int64,int64]->[int64]    | -1     |                                              |                                                   |
| 139 | mod_double                 | 0Byte      | [double,double]->[double] | -1     |                                              |                                                   |
| 140 | minus_int                  | 0Byte      | [int,int]->[int]          | 0      |                                              |                                                   |
| 141 | minus_int64                | 0Byte      | [int64,int64]->[int64]    | 0      |                                              |                                                   |
| 142 | minus_double               | 0Byte      | [double,double]->[double] | 0      |                                              |                                                   |
| 143 | self_increase_int          | 0Byte      |                           | 0      |                                              |                                                   |
| 144 | self_increase_int64        | 0Byte      |                           | 0      |                                              |                                                   |
| 145 | self_increase_double       | 0Byte      |                           | 0      |                                              |                                                   |
| 146 | self_decrease_int          | 0Byte      |                           | 0      |                                              |                                                   |
| 147 | self_decrease_int64        | 0Byte      |                           | 0      |                                              |                                                   |
| 148 | self_decrease_double       | 0Byte      |                           | 0      |                                              |                                                   |
| 149 | concat                     | 0Byte      |                           | -1     |                                              |                                                   |
| 150 | push_array_len             | 0Byte      |                           | 0      |                                              |                                                   |
| 151 | push_array_capacity        | 0Byte      |                           | 0      |                                              |                                                   |
| 152 | push_string_len            | 0Byte      |                           | 0      |                                              |                                                   |
| 153 | push_string_capacity       | 0Byte      |                           | 0      |                                              |                                                   |
| 154 | cast_bool_to_int           | 0Byte      |                           | 0      |                                              |                                                   |
| 155 | cast_int_to_double         | 0Byte      |                           | 0      |                                              |                                                   |
| 156 | cast_int_to_bool           | 0Byte      |                           | 0      |                                              |                                                   |
| 157 | cast_double_to_int         | 0Byte      |                           | 0      |                                              |                                                   |
| 158 | bool_2_string              | 0Byte      | [bool]->[string]          | 0      | convert bool to string                       | So(-1).string = So(-1).bool                       |
| 159 | int_2_string               | 0Byte      | [int]->[string]           | 0      | convert int to string                        | So(-1).string = So(-1).int                        |
| 160 | int64_2_string             | 0Byte      | [int]->[string]           | 0      | convert int64 to string                      | So(-1).string = So(-1).int64                      |
| 161 | double_2_string            | 0Byte      | [double]->[string]        | 0      | convert double to string                     | So(-1).string = So(-1).double                     |
| 162 | int_2_int64                | 0Byte      | [int]->[int64]            | 0      | convert int to int64                         | So(-1).int64 = So(-1).int                         |
| 163 | logical_and                | 0Byte      | [bool,bool]->[bool]       | -1     |                                              |                                                   |
| 164 | logical_or                 | 0Byte      | [bool,bool]->[bool]       | -1     |                                              |                                                   |
| 165 | logical_not                | 0Byte      | [bool,bool]->[bool]       | 0      |                                              |                                                   |
| 166 | eq_int                     | 0Byte      | [int,int]->[bool]         | -1     |                                              |                                                   |
| 167 | eq_int64                   | 0Byte      | [int64,int64]->[bool]     | -1     |                                              |                                                   |
| 168 | eq_double                  | 0Byte      | [double,double]->[bool]   | -1     |                                              |                                                   |
| 169 | eq_string                  | 0Byte      | [string,string]->[bool]   | -1     |                                              |                                                   |
| 170 | ne_int                     | 0Byte      | [int,int]->[bool]         | -1     |                                              |                                                   |
| 171 | ne_int64                   | 0Byte      | [int64,int64]->[bool]     | -1     |                                              |                                                   |
| 172 | ne_double                  | 0Byte      | [double,double]->[bool]   | -1     |                                              |                                                   |
| 173 | ne_string                  | 0Byte      | [string,string]->[bool]   | -1     |                                              |                                                   |
| 174 | gt_int                     | 0Byte      | [int,int]->[bool]         | -1     |                                              |                                                   |
| 175 | gt_int64                   | 0Byte      | [int64,int64]->[bool]     | -1     |                                              |                                                   |
| 176 | gt_double                  | 0Byte      | [double,double]->[bool]   | -1     |                                              |                                                   |
| 177 | gt_string                  | 0Byte      | [string,string]->[bool]   | -1     |                                              |                                                   |
| 178 | ge_int                     | 0Byte      | [int,int]->[bool]         | -1     |                                              |                                                   |
| 179 | ge_int64                   | 0Byte      | [int64,int64]->[bool]     | -1     |                                              |                                                   |
| 180 | ge_double                  | 0Byte      | [double,double]->[bool]   | -1     |                                              |                                                   |
| 181 | ge_string                  | 0Byte      | [string,string]->[bool]   | -1     |                                              |                                                   |
| 182 | lt_int                     | 0Byte      | [int,int]->[bool]         | -1     |                                              |                                                   |
| 183 | lt_int64                   | 0Byte      | [int64,int64]->[bool]     | -1     |                                              |                                                   |
| 184 | lt_double                  | 0Byte      | [double,double]->[bool]   | -1     |                                              |                                                   |
| 185 | lt_string                  | 0Byte      | [string,string]->[bool]   | -1     |                                              |                                                   |
| 186 | le_int                     | 0Byte      | [int,int]->[bool]         | -1     |                                              |                                                   |
| 187 | le_int64                   | 0Byte      | [int64,int64]->[bool]     | -1     |                                              |                                                   |
| 188 | le_double                  | 0Byte      | [double,double]->[bool]   | -1     |                                              |                                                   |
| 189 | le_string                  | 0Byte      | [string,string]->[bool]   | -1     |                                              |                                                   |
| 190 | jump                       | 2Byte_As   |                           | 0      |                                              |                                                   |
| 191 | jump_if_false              | 2Byte_As   |                           | -1     |                                              |                                                   |
| 192 | jump_if_true               | 2Byte_As   |                           | -1     |                                              |                                                   |
| 193 | shallow_copy               | 2Byte_AB   |                           | +1     | shallow copy value from B to A               |                                                   |
| 194 | deep_copy_class_ob         | 2Byte_AB   |                           | +1     | deep copy class-object from B to A           |                                                   |
| 195 | deep_copy_array            | 2Byte_AB   |                           | +1     | deep copy array from B to A                  |                                                   |
| 196 | pop                        | 1Byte_A    | [...]->[]                 | -A     | pop num value from stack                     |                                                   |
| 197 | nop                        | 0Byte      | -                         | +1     | -                                            | -                                                 |
| 198 | push_func                  | 2Byte_AB   |                           | +1     |                                              |                                                   |
| 199 | push_method                | 2Byte_As   |                           | +1     |                                              |                                                   |
| 200 | invoke_func_native         | 1Byte_A    |                           | -1     |                                              |                                                   |
| 201 | invoke_func                | 1Byte_A    |                           | -1     |                                              |                                                   |
| 202 | invoke_closure             | 1Byte_A    |                           | -1     |                                              |                                                   |
| 203 | invoke_method              | 1Byte_A    |                           | -2     |                                              |                                                   |
| 204 | return                     | 1Byte_A    |                           | 0      |                                              |                                                   |
| 205 | function_finish            | 0Byte      |                           | 0      |                                              |                                                   |
| 206 | exit                       | 0Byte      |                           | -1     |                                              |                                                   |
| 207 | new_closure                | 2Byte_As   | stack_top_change          | +1     | instantiated a closure by anonymous function | math_formula                                      |
| 208 | push_defer                 | 1Byte_A    | -                         | -1     | -                                            | -                                                 |
| 209 | pop_defer                  | 0Byte      | -                         | 0      | -                                            | -                                                 |
| 210 | launch                     | 1Byte_A    | stack_top_change          | -2     | usage_comment                                | math_formula                                      |
| 211 | launch_closure             | 1Byte_A    | stack_top_change          | 0      | usage_comment                                | math_formula                                      |
| 212 | launch_method              | 1Byte_A    | stack_top_change          | 0      | usage_comment                                | math_formula                                      |
| 213 | resume                     | 0Byte      | stack_top_change          | -1     | usage_comment                                | math_formula                                      |
| 214 | yield                      | 0Byte      | stack_top_change          | 0      | usage_comment                                | math_formula                                      |
| 215 | num                        | 0Byte      | stack_top_change          | 0      | usage_comment                                | math_formula                                      |


### 操作数类型说明

- 0Byte: 无操作数

- 1Byte_A: 1字节操作数A

- 2Byte_As: 2字节操作数A

- 2Byte_AB: 1字节操作数A和1字节操作数B

- 3Byte_AsB: 1字节操作数A和2字节操作数B



### 操作数公式说明

```

math_formula 字段是如何通过数学公式描述一个字节码所对应的 VirtualMachine 操作行为

K(1)  通过index 1 , 来操作 static 空间
Si(1) 通过 index 1 , 来操作 stack 空间
So(1) 通过 offset 1 , 来操作 stack 空间
Fi(1) 通过 index 1 , 来操作 free-value 空间
C(1)  通过index 1, 从ConstantPool  Constant

Field(object, As).int 将object的第As个Field作为int

A As AB Bs 分别代表字节码后边的操作数
FSB 代表 FunctionStackBase

```
