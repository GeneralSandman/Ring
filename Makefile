TARGET=ring
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  main.o\
  string.o\
  create_ast.o\
  eval_ast.o\
  interpreter.o\
  inner_func.o\
  utils.o\
  semantic_check.o

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

y.tab.o: y.tab.c
lex.yy.o: lex.yy.c ring.h
string.o: string.c
main.o: main.c ring.h
create_ast.o: create_ast.c ring.h
eval_ast.o: eval_ast.c ring.h
interpreter.o: interpreter.c ring.h inner_func.h
inner_func.o: inner_func.c ring.h inner_func.h
utils.o: utils.c ring.h
semantic_check.o: semantic_check.c ring.h
