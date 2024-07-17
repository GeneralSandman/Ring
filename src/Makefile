TARGET = ring
VERSION= ring-v0.2.14-beta
CC     = g++
OBJS   = \
	lex.yy.o\
	y.tab.o\
	string.o\
	create_ast.o\
	semantic_check.o\
	fix_ast.o\
	crop_ast.o\
	vm.o\
	buildin.o\
	generate.o\
	execute.o\
	compiler.o\
	error_msg.o\
	utils.o\
	man_help.o\
	std_lib.o\
	mem_pool.o\
	gc.o\
	debug.o\
	vm-debug.o\
	../deps/linenoise/linenoise.o\
	fmt.o\
	main.o

# bison 可执行文件路径
# bison >= 3.8.2
BisonBin     =  /usr/local/Cellar/bison/3.8.2/bin/bison
BisonRequire = 3.8.2
BisonVersion =  $(shell $(BisonBin) --version | grep 'bison' | awk '{print $$4}')

# flex 可执行文件路径
# flex >= 2.6.4
FlexBin      = flex
FlexRequire  = 2.6.4
FlexVersion  =  $(shell $(FlexBin) --version | grep 'flex' | awk '{print $$2}')

# echo 宏
SuccMsg = ""\033[32m[+]]:\033[0m""
ErrMsg  = ""\033[31mERR:\033[0m""
TipMsg  = ""\033[33mTIP:\033[0m""


TOOL_GEN_VMCODE_DOC_TARGET= tool_gen_vmcode_doc
TOOL_GEN_VMCODE_DOC_OBJS  = vm.o tool_gen_vmcode_doc.o

# CFLAGS -g 打开调试信息
# CFLAGS -DDEBUG 开启 debug 编译信息
# CFLAGS -DDEBUG_RVM_INTERACTIVE 开启 debug ring virtual machine 信息
# -lm for fmod function
# -lncurses for tigetnum tigetnum

# DEBUG_XX 来控制不同阶段的debug日志
#  DEBUG_FLEX 					     控制flex工具日志
#  DEBUG_BISON 					     控制bison工具日志，一般来说与DEBUG_FLEX 一块效果比较好，能看到解析到哪一行
#  DEUBG_CREATE_AST 			     控制生成AST日志
#  DEBUG_STD_LIB 				     控制 std lib 的 debug 路径
#  DEBUG_COMPILER_SUMMARY 		     控制编译阶段的信息：词法分析、语法分析、语意分析
#  DEBUG_COMPILER_DETAIL 		     控制编译阶段的信息：词法分析、语法分析、语意分析
#  DEBUG_GENERATE_SUMMARY 		     代码生成阶段 概要: 只会打印出相关的package package_unit信息
#  DEBUG_GENERATE_DETAIL 		     代码生成阶段 详情: 会打印出package对应的字节码
#  DEBUG_GENERATE_OUTPUT_VMCODE      代码生成节点： 只打印出相应的字节码
#  DEBUG_EXEC_VM  				     vm运行阶段的调试信息
#  DEBUG_RVM_INTERACTIVE 		     控制调试RVM
#  DDEBUG_RVM_MEM_POOL_DETAIL 	     展示 Memory Pool 内存分配的详情
#  DEBUG_RVM_GC_DETAIL 			     展示 Garbage Collect 的详情
#  DEBUG_RDB_TRACE_DISPATH_DETAIL    调试开发Ring-Debugger: 展示 rdb trace_dispath 的详情, 可以展示每一次回掉到debugger的详情
CFLAGS = -c -static -O2 -std=c++17 \
				-Wall \
				-Wextra \
				-Wno-sign-compare \
				-Wno-unused-parameter \
				-Wno-unused-function \
				  -g \
				 -DDEBUG \
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
				 -DDEBUG_RVM_INTERACTIVE \
				 -DDEBUG_RVM_MEM_POOL_DETAIL1 \
				 -DDEBUG_RVM_GC_DETAIL1 \
				 -DDEBUG_RDB_TRACE_DISPATH_DETAIL1

CFLAGS+= -I../deps/linenoise
CFLAGS+= -I../deps/clipp
BIN = ../bin
INCLUDES = \


DEPENDENCY_TARGETS=linenoise

persist-settings: cleandeps
	-(cd ../deps && $(MAKE) $(DEPENDENCY_TARGETS))

.PHONY: persist-settings



.SUFFIXES: .cpp .c
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

$(TARGET):$(OBJS); $(shell if [ ! -e $(BIN) ];then mkdir -p $(BIN); fi)
	$(CC) $(OBJS) -lm -pthread -o $(BIN)/$@
	@echo "\033[32mBuild Ring SUCCESS:" $(BIN)/$@ "\033[0m"

$(TOOL_GEN_VMCODE_DOC_TARGET):$(TOOL_GEN_VMCODE_DOC_OBJS); $(shell if [ ! -e $(BIN) ];then mkdir -p $(BIN); fi)
	$(CC) $(TOOL_GEN_VMCODE_DOC_OBJS) -lm -pthread -o $(BIN)/$@
	@echo "\033[32mBuild Tool Generate Vmcode Doc SUCCESS:" $(BIN)/$@ "\033[0m"



# 验证编译工具链是否符合要求
# linux macos : command -v 
# windows : where
check:
	@command -v $(BisonBin) > /dev/null || { \
		echo "$(ErrMsg) Not found '$(BisonBin)', please install 'bison'."; \
		echo "$(TipMsg) Specify the path to the 'bison' executable use src/Makefile:25 @BisonBin" ; \
		exit 1; \
	}
	@command -v $(FlexBin) > /dev/null || { \
		echo "$(ErrMsg) Not found '$(FlexBin)', please install 'flex'."; \
		echo "$(TipMsg) Specify the path to the 'flex' executable use src/Makefile:31 @FlexBin" ; \
		exit 1; \
	}

	@echo "[+]bison version= \033[32m$(BisonVersion)\033[0m"
	@echo "[+]flex  version= \033[32m$(FlexVersion)\033[0m"



echo:
	@echo "[+]bison path       = \033[32m$(BisonBin)\033[0m"
	@echo "[+]bison version    = \033[32m$(BisonVersion)\033[0m"

	@echo "[+]flex  path       = \033[32m$(FlexBin)\033[0m"
	@echo "[+]flex  version    = \033[32m$(FlexVersion)\033[0m"

	@echo "[+]ring  version    = \033[32m$(VERSION)\033[0m"


clean:
	rm -f *.o lex.yy.cpp y.tab.cpp y.tab.hpp y.output *~
	@echo "\033[32mClean SUCCESS\033[0m"

.PHONY: clean

cleandeps: clean
	-(cd ../deps && $(MAKE) cleandeps)

.PHONY: cleandeps


# 输出 y.output y.tab.cpp y.tab.hpp
# -t :                诊断模式
# -dv :               输出详细信息
# -Wcounterexamples : generate conflict counterexamples
y.tab.hpp y.tab.cpp : ring.bison.y
	$(BisonBin) -o y.tab.cpp -dv ring.bison.y  
#	$(BisonBin) -o y.tab.cpp -dv -Wcounterexamples ring.bison.y  

# 输出 lex.yy.cpp
lex.yy.cpp : ring.flex.l ring.bison.y y.tab.hpp
	$(FlexBin) -o lex.yy.cpp ring.flex.l


lex.yy.o: lex.yy.cpp ring.hpp
y.tab.o: y.tab.cpp
string.o: string.cpp
create_ast.o: create_ast.cpp ring.hpp
semantic_check.o: semantic_check.cpp ring.hpp
fix_ast.o: fix_ast.cpp ring.hpp
crop_ast.o: crop_ast.cpp ring.hpp
vm.o: vm.cpp ring.hpp
buildin.o: buildin.cpp ring.hpp
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
debug.o: debug.cpp ring.hpp
vm-debug.o: vm-debug.cpp ring.hpp
thread_pool.o: thread_pool.c ring.hpp
main.o: main.cpp ring.hpp
tool_gen_vmcode_doc.o: tool_gen_vmcode_doc.cpp ring.hpp
fmt.o: fmt.cpp ring.hpp
