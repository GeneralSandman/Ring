#include <stdio.h>
#include <stdlib.h>
#include "ring.h"
#include "y.tab.h"

// 标识符合法性检查
// 其实这个用不到，flex是有优先级的，会有语法错误
// 检查变量是否重复定义
int identifier_check_valid(char *identifier) {
}

Variable *new_variable(VariableType type, char *identifier) {
    debug_log_with_yellow_coloar("\t type(%d),identifier(%s)", type, identifier);

    Variable *variable;
    variable = (Variable *)malloc(sizeof(Variable));

    variable->type               = type;
    variable->variable_identifer = identifier;
    variable->u.ring_basic_value = NULL;

    insert_identifier(IDENTIFIER_TYPE_VARIABLE, identifier);
    return variable;
}

// 定义一个变量、函数时 都要执行改操作
// 确保：
//   1. 名称不能重复
//   2. 不能给函数复制
//   3. 不能用变量去调用函数
void insert_identifier(IdentifierType type, char *name) {
    Identifier *identifier;
    identifier = new_identifier(type, name);

    identifier->next                        = get_ring_interpreter()->identifier_list;
    get_ring_interpreter()->identifier_list = identifier;
}

void check_identifier_valid(char *identifier_name) {
}
