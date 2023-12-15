#include "ring.hpp"

extern RVM_Opcode_Info
            RVM_Opcode_Infos[];


std::string title = "## 1. Ring Stacked-Based VM 指令集";

// tool
int main() {
    printf("\n\n\n");
    printf("%s\n\n", title.c_str());


    printf("|            指令               | 操作数占用字节数 | 栈顶值变化                  | 栈高度 | 含义                               |\n");
    printf("| ---------------------------- | -------- | ---------------------------- | ---------------------------- | ------------------------------------------------ |\n");

    for (RVM_Byte vmcode = RVM_CODE_PUSH_BOOL; vmcode <= RVM_CODES_NUM; vmcode++) {
        RVM_Opcode_Info opcode_info                 = RVM_Opcode_Infos[vmcode];

        std::string     vmcode_name                 = opcode_info.name;
        int             operand_type                = int(opcode_info.operand_type);

        std::string     runtime_stack_increment_str = std::to_string(opcode_info.runtime_stack_increment);
        if (opcode_info.runtime_stack_increment > 0) {
            runtime_stack_increment_str = "+" + std::to_string(opcode_info.runtime_stack_increment);
        }

        printf("|%30s|%10d|%30s|%30s|%50s|\n", vmcode_name.c_str(),
               operand_type,
               opcode_info.stack_top_change.c_str(),
               runtime_stack_increment_str.c_str(),
               opcode_info.usage_comment.c_str());
    }

    return 0;
}
