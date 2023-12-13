TARGET = ring
VERSION= ring-v0.2.12-beta
CC     = g++
OBJS   = \
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
	mem_pool.o\
	gc.o\
	main.o


TOOL_GEN_VMCODE_DOC_TARGET= tool_gen_vmcode_doc
TOOL_GEN_VMCODE_DOC_OBJS  = vm.o tool_gen_vmcode_doc.o

# CFLAGS -g 打开调试信息
# CFLAGS -DDEBUG 开启 debug 编译信息
# CFLAGS -DDEBUG_RVM_INTERACTIVE 开启 debug ring virtual machine 信息
# -lm for fmod function
# -lncurses for tigetnum tigetnum

# DEBUG_XX 来控制不同阶段的debug日志
#  DEBUG_FLEX 						控制flex工具日志
#  DEBUG_BISON 						控制bison工具日志，一般来说与DEBUG_FLEX 一块效果比较好，能看到哪一行
#  DEUBG_CREATE_AST 					控制生成AST日志
#  DEBUG_STD_LIB 					控制 std lib 的 debug 路径
#  DEBUG_COMPILER_SUMMARY 			控制编译阶段的信息：词法分析、语法分析、语意分析
#  DEBUG_COMPILER_DETAIL 			控制编译阶段的信息：词法分析、语法分析、语意分析
#  DEBUG_GENERATE_SUMMARY 			代码生成阶段 概要: 只会打印出相关的package package_unit信息
#  DEBUG_GENERATE_DETAIL 			代码生成阶段 详情: 会打印出package对应的字节码
#  DEBUG_GENERATE_OUTPUT_VMCODE 		代码生成节点： 只打印出相应的字节码
#  DEBUG_EXEC_VM  					vm运行阶段的调试信息
#  DEBUG_RVM_INTERACTIVE 			控制调试RVM
#  DDEBUG_RVM_MEM_POOL_DETAIL 		展示 Memory Pool 内存分配的详情
#  DEBUG_RVM_GC_DETAIL 				展示 Garbage Collect 的详情
CFLAGS = -c -std=c++11 \
				-Wall \
				-Wextra \
				-Wno-sign-compare \
				-Wno-unused-parameter \
				-Wno-unused-function \
				# -g \
				 -DDEBUG_FLEX1 \
				 -DDEBUG_BISON1 \
				 -DDEBUG_CREATE_AST1 \
				 -DDEBUG_STD_LIB1 \
				 -DDEBUG_COMPILER_SUMMARY1 \
				 -DDEBUG_COMPILER_DETAIL1 \
				 -DDEBUG_GENERATE_SUMMARY1 \
				 -DDEBUG_GENERATE_DETAIL1 \
				 -DDEBUG_GENERATE_OUTPUT_VMCODE1 \
				 -DDEBUG_EXEC_VM1 \
				 -DDEBUG_RVM_INTERACTIVE1 \
				 -DDEBUG_RVM_MEM_POOL_DETAIL1 \
				 -DDEBUG_RVM_GC_DETAIL1
BIN = ../bin
INCLUDES = \


PLATS= linux macosx windows Darwim

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


clean:
	rm -f *.o lex.yy.cpp y.tab.cpp y.tab.hpp y.output *~
	@echo "\033[32mClean SUCCESS\033[0m"

y.tab.hpp : ring.bison.y
	bison -o y.tab.cpp -dv ring.bison.y
y.tab.cpp : ring.bison.y
	bison -o y.tab.cpp -dv ring.bison.y  # -t 诊断模式
lex.yy.cpp : ring.flex.l ring.bison.y y.tab.hpp
	flex -o lex.yy.cpp ring.flex.l


lex.yy.o: lex.yy.cpp ring.hpp
y.tab.o: y.tab.cpp
string.o: string.cpp
create_ast.o: create_ast.cpp ring.hpp
semantic_check.o: semantic_check.cpp ring.hpp
fix_ast.o: fix_ast.cpp ring.hpp
vm.o: vm.cpp ring.hpp
generate.o: generate.cpp ring.hpp
execute.o: execute.cpp ring.hpp
bytecode.o: bytecode.cpp ring.hpp
compiler.o: compiler.cpp ring.hpp
error_msg.o: error_msg.cpp ring.hpp
utils.o: utils.cpp ring.hpp
man_help.o: man_help.cpp ring.hpp
std_lib.o: std_lib.cpp ring.hpp
mem_pool.o: mem_pool.cpp ring.hpp
gc.o: gc.cpp ring.hpp
thread_pool.o: thread_pool.c ring.hpp
main.o: main.cpp ring.hpp
tool_gen_vmcode_doc.o: tool_gen_vmcode_doc.cpp ring.hpp

