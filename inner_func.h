#ifndef INNER_FUNC_INCLUDE_H
#define INNER_FUNC_INCLUDE_H

#include <stdio.h>
#include "ring.h"

void register_inner_func(Ring_Compiler *ring_compiler);
void ring_inner_func_print(int argc, Ring_BasicValue **value);

#endif
