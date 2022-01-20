#include <stdlib.h>
#include "ring.h"

Variable *new_variable(VariableType type, char *identifier) {
#ifdef DEBUG
    printf("[DEBUG][ring.c][function:new_variable]\ttype(%d),identifier(%s)\n", type, identifier);
#endif

    Variable *variable;
    variable = (Variable *)malloc(sizeof(Variable));

    variable->type               = type;
    variable->variable_identifer = identifier;
    variable->u.ring_basic_value = NULL;
    return variable;
}