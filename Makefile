TARGET=ring
CC=g++
OBJS = \
  lex.yy.o\
  y.tab.o\
  string.o\
  create_ast.o\
  semantic_check.o\
  fix_ast.o\
  generate.o\
  execute.o\
  bytecode.o\
  compiler.o\
  inner_func.o\
  interactive.o\
  error_msg.o\
  utils.o\
  std_lib.o\
  main.o

# CFLAGS -g 打开调试信息
# CFLAGS -DDEBUG 开启 debug 编译信息
# CFLAGS -DDEBUG_RVM 开启 debug ring virtual machine 信息
# -lm for fmod function
# -lncurses for tigetnum tigetnum
CFLAGS = -c -std=c++11 -Wall -Wno-gnu-zero-variadic-macro-arguments -Wno-unused-function -Wno-pedantic # -g -DDEBUG1 -DDEBUG_RVM1
BIN = ./bin
INCLUDES = \

.SUFFIXES: .cpp .c
.cpp.o:
	$(CC) $(CFLAGS) $<

$(TARGET):$(OBJS); $(shell if [ ! -e $(BIN) ];then mkdir -p $(BIN); fi)
	$(CC) $(OBJS) -lm -pthread -o $(BIN)/$@

install:
	install -p -m 0755 ./bin/ring /usr/local/bin
uninstall:
	cd /usr/local/bin && rm ring
clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h y.output *~

testall:
	sh ./automated-testing.sh
  
y.tab.h : ring.bison.y
	bison --yacc -dv ring.bison.y
y.tab.c : ring.bison.y
	bison --yacc -dv ring.bison.y
lex.yy.c : ring.flex.l ring.bison.y y.tab.h
	flex ring.flex.l


# 构建 compile_commands.json 供 vim-lsp
compile_commands.json : Makefile
	compiledb -n make


lex.yy.o: lex.yy.c ring.h
y.tab.o: y.tab.c
string.o: string.cpp
create_ast.o: create_ast.cpp ring.h
semantic_check.o: semantic_check.cpp ring.h
fix_ast.o: fix_ast.cpp ring.h
generate.o: generate.cpp ring.h
execute.o: execute.cpp ring.h
bytecode.o: bytecode.cpp ring.h
compiler.o: compiler.cpp ring.h inner_func.h
inner_func.o: inner_func.cpp ring.h inner_func.h
interactive.o: interactive.cpp ring.h
error_msg.o: error_msg.cpp ring.h
utils.o: utils.cpp ring.h
std_lib.o: std_lib.cpp ring.h
thread_pool.o: thread_pool.c ring.h
main.o: main.cpp ring.h
