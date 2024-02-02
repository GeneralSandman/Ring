TARGET= ring
TOOL_GEN_VMCODE_DOC_TARGET=tool_gen_vmcode_doc

INSTALL_TOP= /usr/local
INSTALL_BIN= $(INSTALL_TOP)/bin
INSTALL_PACK= $(INSTALL_TOP)/lib/ring
INSTALL_PACK_STD = $(INSTALL_TOP)/lib/ring/std

CMD_INSTALL= install -p
CMD_INSTALL_EXEC= $(CMD_INSTALL) -m 0755
CMD_INSTALL_DATA= $(CMD_INSTALL) -m 0644

CMD_MKDIR= mkdir -p
CMD_RM= rm -rf

T_STD_PACKS= os io debug fmt vm math strings reflect


# 编译工具要求
# bison >= 3.8.2
# flex >= 2.6.4


# 生成 Ring可执行文件
# 最后在 src/Makefile
# -j10 10进程并发编译
all:
	@cd src && $(MAKE) $(TARGET) -j20

# 生成一个脚本用于 将 Ring 虚拟机指令集生成一个 markdown表格
# Usage:
# 	  make tool_gen_vmcode_doc && ./bin/tool_gen_vmcode_doc
$(TOOL_GEN_VMCODE_DOC_TARGET):
	@cd src && $(MAKE) $@

clean:
	@cd src && $(MAKE) $@

testall:
	bash ./test/automated-testing.sh
  
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

echo:
	@echo "[Echo Build Info]"
	@echo "[+]g++ Version= \033[32m`g++ --version`\033[0m" # >= 2.6.4
	@echo "[+]Flex Version= \033[32m`flex --version`\033[0m" # >= 2.6.4
	@echo "[+]Bison Version= \033[32m`bison --version`\033[0m" # >= 2.3
	@echo "[+]PLATS= \033[32m$(PLATS)\033[0m"
	@echo "[+]PLAT=" "\033[32m" `$(UNAME)` "\033[0m"
	@echo "[+]VERSION= \033[32m$(VERSION)\033[0m"
	@echo "[+]T_STD_PACKS= \033[32m$(T_STD_PACKS)\033[0m"

# 构建 compile_commands.json 供 vim-lsp
compile_commands.json: .git
	compiledb -n make


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
