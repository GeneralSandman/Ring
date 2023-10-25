TARGET= ring
VERSION= ring-v0.2.10-beta
CC=g++
OBJS = \
	lex.yy.o\
	y.tab.o\
	string.o\
	create_ast.o\
	semantic_check.o\
	fix_ast.o\
	vm.o\
	generate.o\
	execute.o\
	compiler.o\
	error_msg.o\
	utils.o\
	man_help.o\
	std_lib.o\
	gc.o\
	main.o

# 生成一个脚本用于 将 Ring 虚拟机指令集生成一个 markdown表格
# Usage:
# 	  make tool_gen_vmcode_doc && ./bin/tool_gen_vmcode_doc
TOOL_GEN_VMCODE_DOC_TARGET=tool_gen_vmcode_doc
TOOL_GEN_VMCODE_DOC_OBJS = \
														vm.o\
														tool_gen_vmcode_doc.o

# CFLAGS -g 打开调试信息
# CFLAGS -DDEBUG 开启 debug 编译信息
# CFLAGS -DDEBUG_RVM_INTERACTIVE 开启 debug ring virtual machine 信息
# -lm for fmod function
# -lncurses for tigetnum tigetnum

# DEBUG_XX 来控制不同阶段的debug日志
# DEBUG_FLEX 控制flex工具日志
# DEBUG_BISON 控制bison工具日志，一般来说与DEBUG_FLEX 一块效果比较好，能看到哪一行
# DEUBG_CREATE_AST 控制生成AST日志
# DEBUG_STD_LIB 控制 std lib 的 debug 路径
# DEBUG_COMPILER_SUMMARY 控制编译阶段的信息：词法分析、语法分析、语意分析
# DEBUG_COMPILER_DETAIL 控制编译阶段的信息：词法分析、语法分析、语意分析
# DEBUG_GENERATE_SUMMARY 代码生成阶段 概要: 只会打印出相关的package package_unit信息
# DEBUG_GENERATE_DETAIL 代码生成阶段 详情: 会打印出package对应的字节码
# DEBUG_EXEC_VM  vm运行阶段的调试信息
# DEBUG_RVM_INTERACTIVE 控制调试RVM
CFLAGS = -c -std=c++11 -Wall -Wno-unused-function -Wno-unneeded-internal-declaration \
				 # -g \
				 -DDEBUG_FLEX1 \
				 -DDEBUG_BISON1 \
				 -DDEBUG_CREATE_AST1 \
				 -DDEBUG_STD_LIB1 \
				 -DDEBUG_COMPILER_SUMMARY1 \
				 -DDEBUG_COMPILER_DETAIL1 \
				 -DDEBUG_GENERATE_SUMMARY1 \
				 -DDEBUG_GENERATE_DETAIL1 \
				 -DDEBUG_EXEC_VM1 \
				 -DDEBUG_RVM_INTERACTIVE1
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

PLATS= linux macosx windows Darwim

T_BIN= ring
T_STD_PACKS= os io debug fmt math strings reflect


UNAME= uname


.SUFFIXES: .cpp .c
.cpp.o:
	$(CC) $(CFLAGS) $<

$(TARGET):$(OBJS); $(shell if [ ! -e $(BIN) ];then mkdir -p $(BIN); fi)
	$(CC) $(OBJS) -lm -pthread -o $(BIN)/$@
	@echo "\033[32mBuild Ring SUCCESS:" $(BIN)/$@ "\033[0m"

$(TOOL_GEN_VMCODE_DOC_TARGET):$(TOOL_GEN_VMCODE_DOC_OBJS); $(shell if [ ! -e $(BIN) ];then mkdir -p $(BIN); fi)
	$(CC) $(TOOL_GEN_VMCODE_DOC_OBJS) -lm -pthread -o $(BIN)/$@
	@echo "\033[32mBuild Tool Generate Vmcode Doc SUCCESS:" $(BIN)/$@ "\033[0m"

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
	$(call func_install_package_std,os)
	$(call func_install_package_std,io)
	$(call func_install_package_std,debug)
	$(call func_install_package_std,fmt)
	$(call func_install_package_std,vm)
	$(call func_install_package_std,math)
	$(call func_install_package_std,strings)
	$(call func_install_package_std,reflect)
endef
	
define uninstall_package_std
	$(call func_uninstall_package_std,os)
	$(call func_uninstall_package_std,io)
	$(call func_uninstall_package_std,debug)
	$(call func_uninstall_package_std,fmt)
	$(call func_install_package_std,vm)
	$(call func_uninstall_package_std,math)
	$(call func_uninstall_package_std,strings)
	$(call func_uninstall_package_std,reflect)
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
vm.o: vm.cpp ring.h
generate.o: generate.cpp ring.h
execute.o: execute.cpp ring.h
bytecode.o: bytecode.cpp ring.h
compiler.o: compiler.cpp ring.h
error_msg.o: error_msg.cpp ring.h
utils.o: utils.cpp ring.h
man_help.o: man_help.cpp ring.h
std_lib.o: std_lib.cpp ring.h
gc.o: gc.cpp ring.h
thread_pool.o: thread_pool.c ring.h
main.o: main.cpp ring.h
tool_gen_vmcode_doc.o: tool_gen_vmcode_doc.cpp ring.h

