TARGET=ring
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  string.o\
  create_ast.o\
  semantic_check.o\
  fix.o\
  eval_ast.o\
  generate.o\
  execute.o\
  interpreter.o\
  inner_func.o\
  utils.o\
  main.o

CFLAGS = -c -g -std=c99 -Wall -Wno-gnu-zero-variadic-macro-arguments -Wno-unused-function  -pedantic
BIN = ./bin
INCLUDES = \

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(BIN)/$@

install:
	install -p -m 0755 ./bin/ring /usr/local/bin
uninstall:
	cd /usr/local/bin && rm ring
clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h y.output *~
  
y.tab.h : ring.bison.y
	bison --yacc -dv ring.bison.y
y.tab.c : ring.bison.y
	bison --yacc -dv ring.bison.y
lex.yy.c : ring.flex.l ring.bison.y y.tab.h
	flex ring.flex.l


lex.yy.o: lex.yy.c ring.h
y.tab.o: y.tab.c
string.o: string.c
create_ast.o: create_ast.c ring.h
semantic_check.o: semantic_check.c ring.h
fix.o: fix.c ring.h
eval_ast.o: eval_ast.c ring.h
generate.o: generate.c ring.h
execute.o: execute.c ring.h
interpreter.o: interpreter.c ring.h inner_func.h
inner_func.o: inner_func.c ring.h inner_func.h
utils.o: utils.c ring.h
main.o: main.c ring.h
