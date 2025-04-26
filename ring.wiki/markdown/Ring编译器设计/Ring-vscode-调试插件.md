


# vscode 实现一个调试器插件

关于vscode 的 debugger插件
https://code.visualstudio.com/api/extension-guides/debugger-extension


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