TARGET= ring
VERSION= ring-v0.2.8-beta
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
	compiler.o\
	error_msg.o\
	utils.o\
	man_help.o\
	std_lib.o\
	main.o

# CFLAGS -g 打开调试信息
# CFLAGS -DDEBUG 开启 debug 编译信息
# CFLAGS -DDEBUG_RVM_INTERACTIVE 开启 debug ring virtual machine 信息
# -lm for fmod function
# -lncurses for tigetnum tigetnum

# DEBUG_XX 来控制不同阶段的debug日志
# DEBUG_COMPILER 控制编译阶段的信息：词法分析、语法分析、语意分析
# DEBUG_GENERATE_DETAIL 代码生成阶段 详情
# DEBUG_GENERATE_SUMMARY 代码生成阶段 概要
# DEBUG_STD_LIB 控制 std lib 的 debug 路径
# DEBUG_RVM_INTERACTIVE 控制调试RVM
CFLAGS = -c -std=c++11 -Wall -Wno-unused-function -Wno-unneeded-internal-declaration \
				 # -g \
				 -DDEBUG \
				 -DDEBUG_FLEX_BISON \
				 -DDEBUG_STD_LIB \
				 -DDEBUG_COMPILER_SUMMARY1 \
				 -DDEBUG_COMPILER_DETAIL1 \
				 -DDEBUG_GENERATE_SUMMARY1 \
				 -DDEBUG_GENERATE_DETAIL1 \
				 -DDEBUG_RVM_INTERACTIVE
BIN = ./bin
INCLUDES = \


INSTALL_TOP= /usr/local
INSTALL_BIN= $(INSTALL_TOP)/bin
INSTALL_PACK= $(INSTALL_TOP)/lib/ring
INSTALL_PACK_STD = $(INSTALL_TOP)/lib/ring/std

CMD_INSTALL= install -p
CMD_INSTALL_EXEC= $(CMD_INSTALL) -m 0755
CMD_INSTALL_DATA= $(CMD_INSTALL) -m 0644

CMD_MKDIR= mkdir -p
CMD_RM= rm -rf

PLATS= linux macosx

T_BIN= ring
T_STD_PACKS= debug fmt math strings


UNAME= uname


.SUFFIXES: .cpp .c
.cpp.o:
	$(CC) $(CFLAGS) $<

$(TARGET):$(OBJS); $(shell if [ ! -e $(BIN) ];then mkdir -p $(BIN); fi)
	$(CC) $(OBJS) -lm -pthread -o $(BIN)/$@
	@echo "\033[32mBuild Ring SUCCESS:" $(BIN)/$@ "\033[0m"

install:
	@echo "\033[34m[+]Install Bin\033[0m"
	$(CMD_INSTALL_EXEC) ./bin/ring $(INSTALL_BIN)
	@echo "\033[32m[+]Install Bin  SUCCESS\033[0m"
	@echo ""

	$(call install_package_std)

uninstall:
	@echo "\033[34m[-]Uninstall Bin\033[0m"
	$(CMD_RM) $(INSTALL_BIN)/ring
	@echo "\033[32m[-]Uninstall Bin  SUCCESS\033[0m"
	@echo ""

	$(call uninstall_package_std)

clean:
	rm -f *.o lex.yy.cpp y.tab.cpp y.tab.hpp y.output *~
	@echo "\033[32mClean SUCCESS\033[0m"

testall:
	sh ./automated-testing.sh
  

echo:
	@echo "[Echo Build Info]"
	@echo "[+]g++ Version= \033[32m`g++ --version`\033[0m" # >= 2.6.4
	@echo "[+]Flex Version= \033[32m`flex --version`\033[0m" # >= 2.6.4
	@echo "[+]Bison Version= \033[32m`bison --version`\033[0m" # >= 2.3
	@echo "[+]PLATS= \033[32m$(PLATS)\033[0m"
	@echo "[+]PLAT=" "\033[32m" `$(UNAME)` "\033[0m"
	@echo "[+]VERSION= \033[32m$(VERSION)\033[0m"
	@echo "[+]T_STD_PACKS= \033[32m$(T_STD_PACKS)\033[0m"

define func_install_package_std
	@echo "\033[34m[+]Install Package: Std/$(1)\033[0m"
	$(CMD_MKDIR) $(INSTALL_PACK_STD)/$(1)
	$(CMD_INSTALL_DATA) std/$(1)/* $(INSTALL_PACK_STD)/$(1)
	@echo "\033[32m[+]Install Package: Std/$(1)  SUCCESS\033[0m"
	@echo ""

endef

define func_uninstall_package_std
	@echo "\033[34m[-]Uninstall Package: Std/$(1)\033[0m"
	$(CMD_RM) $(INSTALL_PACK_STD)/$(1)
	@echo "\033[32m[-]Uninstall Package: Std/$(1)  SUCCESS\033[0m"
	@echo ""

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


y.tab.hpp : ring.bison.y
	bison -o y.tab.cpp --yacc -dv ring.bison.y
y.tab.cpp : ring.bison.y
	bison -o y.tab.cpp --yacc -dv ring.bison.y  # -t 诊断模式
lex.yy.cpp : ring.flex.l ring.bison.y y.tab.hpp
	flex -o lex.yy.cpp ring.flex.l


# 构建 compile_commands.json 供 vim-lsp
compile_commands.json : Makefile
	compiledb -n make


lex.yy.o: lex.yy.cpp ring.h
y.tab.o: y.tab.cpp
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
man_help.o: man_help.cpp ring.h
std_lib.o: std_lib.cpp ring.h
thread_pool.o: thread_pool.c ring.h
main.o: main.cpp ring.h

