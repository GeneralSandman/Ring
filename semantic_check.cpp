// 语义检查
// 上下文语义分析
#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void ring_compiler_semantic_analysis(Package* package) {
    for (Declaration* decl : package->global_declaration_list) {
    }
    for (ClassDefinition* pos : package->class_definition_list) {
    }
    for (Function* pos : package->function_list) {
    }
}
