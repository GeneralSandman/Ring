#include "ring.h"
#include <stdlib.h>

Ring_VirtualMachine *new_ring_virtualmachine() {
    Ring_VirtualMachine *vm = malloc(sizeof(Ring_VirtualMachine));
    vm->executer            = NULL;
    return vm;
}

void ring_execute_vm_code(Ring_Compiler *ring_compiler) {
}
