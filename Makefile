TARGET=ring
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  main.o\
  ring.o\
  string.o
CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
BIN = ./bin
INCLUDES = \

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(BIN)/$@

clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h y.output *~
  
y.tab.h : ring.bison.y
	bison --yacc -dv ring.bison.y
y.tab.c : ring.bison.y
	bison --yacc -dv ring.bison.y
lex.yy.c : ring.flex.l ring.bison.y y.tab.h
	flex ring.flex.l

y.tab.o: y.tab.c
	$(CC) -c -g $*.c
lex.yy.o: lex.yy.c ring.h
	$(CC) -c -g $*.c $(INCLUDES)
ring.o: ring.c
	$(CC) -c -g $*.c
string.o: string.c
	$(CC) -c -g $*.c

main.o: main.c ring.h
