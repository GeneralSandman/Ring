#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ring.h"

void ring_compile(Ring_Interpreter *ring_interpreter, FILE *fp);
void ring_interpret(Ring_Interpreter *ring_interpreter);
void interpret_statement(Statement *statement);
void interpret_expression(Expression *expression);
void invoke_function(FunctionCallExpression *function_call_expression);
int  interpret_binary_expression(Expression *expression);
void assign(Expression *expression);

int main(int argc, char **argv) {
    Ring_Interpreter *ring_interpreter;
    char *            file_name;
    FILE *            fp;

    if (argc != 2) {
        fprintf(stderr, "usage:%s <filename>", argv[0]);
        exit(1);
    }

    if (!strcmp(argv[1], "--version")) {
        printf("Ring version: %s \n", RING_VERSION);
        return 0;
    }

    file_name = argv[1];

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", argv[1]);
        exit(1);
    }

    ring_interpreter = new_ring_interpreter(file_name);
    ring_compile(ring_interpreter, fp);
    ring_interpret(ring_interpreter);

    return 0;
}

void ring_compile(Ring_Interpreter *ring_interpreter, FILE *fp) {
    extern int   yyparse(void);
    extern FILE *yyin;

    yyin = fp;
    if (yyparse()) {
        /* BUGBUG */
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
}

void ring_interpret(Ring_Interpreter *ring_interpreter) {
#ifdef DEBUG
    printf("[DEBUG][main.c][function:interpret]\t interpret statement: statement_list_size(%d)\n", ring_interpreter->statement_list_size);
#endif

    Statement *p;
    for (p = ring_interpreter->statement_list; p != NULL; p = p->next) {
#ifdef DEBUG
        printf("[DEBUG][main.c][function:interpret]\t interpret statement: type(%d),line_number(%d)\n", p->type, p->line_number);
#endif
        interpret_statement(p);
    }
}

void interpret_statement(Statement *statement) {
    switch (statement->type) {
    case STATEMENT_TYPE_VARIABLE_DEFINITION:
        break;

    case STATEMENT_TYPE_EXPRESSION:
        interpret_expression(statement->u.expression);
        break;

    default:
        break;
    }
}

void interpret_expression(Expression *expression) {
    switch (expression->type) {
    case EXPRESSION_TYPE_FUNCTION_CALL:
        /* code */
        invoke_function(expression->u.function_call_expression);
        break;

    case EXPRESSION_TYPE_ASSIGN:
        assign(expression);
        break;

    case EXPRESSION_TYPE_ARITHMETIC_ADD:
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        interpret_binary_expression(expression);
        break;

    default:
        break;
    }
}

int interpret_binary_expression(Expression *expression) {
#ifdef DEBUG
    printf("[DEBUG][main.c][function:interpret_binary_expression]\t \n");
#endif

    int result;

    switch (expression->type) {
    case EXPRESSION_TYPE_LITERAL_INT:
        result = expression->u.int_literal;
        break;
    case EXPRESSION_TYPE_ARITHMETIC_ADD:
        result = interpret_binary_expression(expression->u.binary_expression->left_expression) + interpret_binary_expression(expression->u.binary_expression->right_expression);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_SUB:
        result = interpret_binary_expression(expression->u.binary_expression->left_expression) - interpret_binary_expression(expression->u.binary_expression->right_expression);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_MUL:
        result = interpret_binary_expression(expression->u.binary_expression->left_expression) * interpret_binary_expression(expression->u.binary_expression->right_expression);
        break;
    case EXPRESSION_TYPE_ARITHMETIC_DIV:
        result = interpret_binary_expression(expression->u.binary_expression->left_expression) / interpret_binary_expression(expression->u.binary_expression->right_expression);
        break;
    default:
        break;
    }

    return result;
}

void invoke_function(FunctionCallExpression *function_call_expression) {
    // search_funcaion
    Function *function = NULL;

    for (Function *pos = get_ring_interpreter()->function_list; pos != NULL; pos = function->next) {
        if (!strcmp(pos->function_name, function_call_expression->function_name)) {
            function = pos;
        }
    }

    if (function == NULL) {
        printf("findn't match function\n");
        return;
    }

    function->inner_func(1, function_call_expression->argument_list->u.ring_basic_value.string_value);

    // invoke
}

void assign(Expression *expression) {
    printf("-------------%d\n", interpret_binary_expression(expression->u.assign_expression->expression));
}