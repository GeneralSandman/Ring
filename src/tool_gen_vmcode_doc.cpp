#include "ring.hpp"


extern std::string     operand_desc;
extern std::string     math_formula_desc;

extern RVM_Opcode_Info RVM_Opcode_Infos[];

std::string            title = "## 1. Ring Stacked-Based VM 指令集";


// tool
int main() {
    printf("\n\n\n");
    printf("%s\n\n", title.c_str());


    printf("| Num    |            指令               | 操作数类型 | 栈顶值变化                  | 栈高度 | 含义                               |\n");
    printf("| ------ | ---------------------------- | -------- | ---------------------------- | ---------------------------- | ------------------------------------------------ |\n");

    for (RVM_Byte vmcode = RVM_CODE_PUSH_BOOL; vmcode <= RVM_CODES_NUM; vmcode++) {
        RVM_Opcode_Info opcode_info  = RVM_Opcode_Infos[vmcode];

        std::string     vmcode_name  = opcode_info.name;
        std::string     operand_type = "";
        switch (opcode_info.operand_type) {
        case OPCODE_OPERAND_TYPE_0BYTE: operand_type = "0Byte"; break;
        case OPCODE_OPERAND_TYPE_1BYTE_A: operand_type = "1Byte_A"; break;
        case OPCODE_OPERAND_TYPE_2BYTE_As: operand_type = "2Byte_As"; break;
        case OPCODE_OPERAND_TYPE_2BYTE_AB: operand_type = "2Byte_AB"; break;
        case OPCODE_OPERAND_TYPE_3BYTE_ABs: operand_type = "3Byte_ABs"; break;
        }


        std::string runtime_stack_increment_str = std::to_string(opcode_info.runtime_stack_increment);
        if (opcode_info.runtime_stack_increment > 0) {
            runtime_stack_increment_str = "+" + std::to_string(opcode_info.runtime_stack_increment);
        }

        printf("|%5d|%30s|%10s|%30s|%30s|%50s|\n",
               int(vmcode),
               vmcode_name.c_str(),
               operand_type.c_str(),
               opcode_info.stack_top_change.c_str(),
               runtime_stack_increment_str.c_str(),
               opcode_info.usage_comment.c_str());
    }


    printf("\n\n");
    printf("### 操作数类型说明\n\n");
    printf("%s", operand_desc.c_str());

    printf("\n\n");
    printf("### 操作数公式说明\n\n");
    printf("```\n");
    printf("%s", math_formula_desc.c_str());
    printf("```\n");

    return 0;
}
