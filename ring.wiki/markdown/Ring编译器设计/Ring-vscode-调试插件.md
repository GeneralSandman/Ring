


# vscode 实现一个调试器插件

关于vscode 的 debugger插件
https://code.visualstudio.com/api/extension-guides/debugger-extension

dlv lldb gdb 调试器






dap 协议常用的封装
CPP  https://github.com/google/cppdap



## 1. 更直观的了解一下 dap 协议是如何交互的

### Golang  
https://github.com/google/go-dap

这下边 有个 cmd/mockserver 可以参考一下

### 协议

dap 协议
https://microsoft.github.io/debug-adapter-protocol/overview

dap 协议报文格式细节
https://microsoft.github.io/debug-adapter-protocol/specification

dap-adapter 和 debugger 流程 交互细节
https://microsoft.github.io/debug-adapter-protocol/overview#How_it_works


## 2. 直观的了解一下，一个 lua 的 debugger 是如何实现的

一个基于 dap 实现的 vscode lua debugger 插件
https://github.com/sssooonnnggg/luau-debugger


一些 debugger 的实现
https://microsoft.github.io/debug-adapter-protocol/implementors/adapters/




----------------

将调试器作为独立进程（调试器进程）与虚拟机执行进程（目标进程）分离，通过进程间通信（IPC）协调工作，是一种 经典且安全 的调试架构设计（类似 GDB 与被调试程序的关系）。以下是具体实现方案和优势分析：

1. 架构设计

```
调试器进程（你的新命令）
  ←→ [IPC: TCP/管道/共享内存] 
  ←→ 虚拟机进程（原 while 循环执行字节码）
```

- 调试器进程：处理用户调试命令（如断点、单步），查询/修改虚拟机状态。
- 虚拟机进程：专注执行字节码，仅在收到调试指令时暂停或返回状态。

7. 注意事项
- 同步问题：确保调试命令和虚拟机执行线程安全（如避免竞态条件）。
- 超时处理：防止调试器无响应导致虚拟机死锁。
- 版本兼容性：调试器与虚拟机进程的协议版本需一致。
- 分离进程：调试器与虚拟机独立，通过 IPC 通信。
- 事件驱动：虚拟机仅在断点/命令时暂停，其余时间全速执行。
- 协议解耦：可灵活升级调试功能而不影响虚拟机核心。

```
# 启动虚拟机进程（正常执行）
./my-vm program.bytecode

# 在另一个终端启动调试器并附加
./my-vm-debugger --attach 12345  # 通过 PID 或端口附加
```

----------------

## DAP 如何与你的虚拟机交互？
- VSCode 调试 UI（如断点、变量查看、调用栈）通过 DAP 发送请求。
- 你的调试适配器（DebugAdapter）解析这些请求，并转换成你的虚拟机的调试命令。
- 你的虚拟机 执行调试操作（如暂停、单步执行），并通过 DAP 返回结果。


## DAP 核心消息类型
消息类型	用途
initialize	初始化调试会话，告诉 VSCode 调试器支持的功能（如 supportsStepBack）。
launch / attach	启动或附加到调试目标（你的虚拟机）。
setBreakpoints	设置/清除断点。
stackTrace	获取当前调用栈（用于“调用堆栈”面板）。
scopes	获取当前作用域（如全局变量、局部变量）。
variables	获取变量值（用于“变量”面板）。
continue	继续执行。
next / stepIn	单步执行（步过、步入）。
stopped	调试器暂停时通知 VSCode（如遇到断点）。


## 通过中间层（调试适配器）实现

如果你的虚拟机不支持 DAP，可以在 调试适配器（DebugAdapter）中转换协议：

VSCode (DAP) <--JSON-RPC--> DebugAdapter <--自定义协议--> 你的虚拟机

调试适配器 负责：
- 接收 DAP 请求（如 setBreakpoints）。
- 转换成你的虚拟机的调试命令（如 break line:10）。
- 返回 DAP 格式的响应。


## 调试流程示例

- 用户按 F5 → VSCode 发送 launch 请求。
- 调试适配器启动虚拟机 → 返回 initialized 事件。
- 用户设置断点 → VSCode 发送 setBreakpoints。
- 虚拟机遇到断点 → 发送 stopped 事件。
- 用户查看变量 → VSCode 发送 variables 请求。
- 虚拟机返回变量值 → 显示在调试面板。


## 通过调试适配器（Debug Adapter）将你的命令行调试接口桥接到 VSCode 的 DAP 协议

VSCode (DAP/JSON-RPC) ←→ Debug Adapter (Node.js/TypeScript) ←→ 你的虚拟机 (命令行/TCP/IP/Stdio)



## 

虚拟机支持 TCP/IP 或管道通信，可以直接让调试适配器与它交互，而不是通过 CLI。这样可以更稳定地捕获调试输出。