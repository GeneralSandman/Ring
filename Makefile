TARGET=ring
CC=g++
OBJS = \
  lex.yy.o\
  y.tab.o\
  string.o\
  create_ast.o\
  fix_ast.o\
  generate.o\
  execute.o\
  compiler.o\
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


INSTALL_TOP= /usr/local
INSTALL_BIN= $(INSTALL_TOP)/bin
INSTALL_PACK= $(INSTALL_TOP)/ring
INSTALL_PACK_STD = $(INSTALL_TOP)/ring/std

CMD_INSTALL= install -p
CMD_INSTALL_EXEC= $(CMD_INSTALL) -m 0755
CMD_INSTALL_DATA= $(CMD_INSTALL) -m 0644

CMD_MKDIR= mkdir -p
CMD_RM= rm -rf

PLATS= linux macosx

T_BIN= ring
T_STD_PACKS= debug fmt math strings



.SUFFIXES: .cpp .c
.cpp.o:
	$(CC) $(CFLAGS) $<

$(TARGET):$(OBJS); $(shell if [ ! -e $(BIN) ];then mkdir -p $(BIN); fi)
	$(CC) $(OBJS) -lm -pthread -o $(BIN)/$@

install:
	$(CMD_INSTALL_EXEC) ./bin/ring $(INSTALL_BIN)
	$(call install_package_std)

uninstall:
	$(CMD_RM) $(INSTALL_BIN)/ring
	$(call uninstall_package_std)

clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h y.output *~

testall:
	sh ./automated-testing.sh
  

define func_install_package_std
	@echo "install package std:$(1)"
	$(CMD_MKDIR) $(INSTALL_PACK_STD)/$(1)
	$(CMD_INSTALL_DATA) std/$(1)/* $(INSTALL_PACK_STD)/$(1)
endef

define func_uninstall_package_std
	@echo "uninstall package std:$(1)"
	$(CMD_RM) $(INSTALL_PACK_STD)/$(1)
endef

define install_package_std
	$(call func_install_package_std,debug)
	$(call func_install_package_std,fmt)
	$(call func_install_package_std,math)
	$(call func_install_package_std,strings)
endef
	
define uninstall_package_std
	$(call func_uninstall_package_std,debug)
	$(call func_uninstall_package_std,fmt)
	$(call func_uninstall_package_std,math)
	$(call func_uninstall_package_std,strings)
endef


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
compiler.o: compiler.cpp ring.h
error_msg.o: error_msg.cpp ring.h
utils.o: utils.cpp ring.h
std_lib.o: std_lib.cpp ring.h
thread_pool.o: thread_pool.c ring.h
main.o: main.cpp ring.h
