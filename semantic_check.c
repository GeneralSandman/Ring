// 语义检查
// 上下文语义分析
#include "ring.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// 语义检查
// 上下文语义分析
int ring_semantic_check(Ring_Compiler* ring_compiler) {
    assert(ring_compiler != NULL);

    int result = 0;

    if (result != 0) {
        fprintf(stderr, "semantic_check error\n");
        exit(ERROR_CODE_SEMANTIC_CHECH_ERROR);
    }

    // exit(1);
    return 0;
}
