Q: lua coroutine 使用什么数据结构表示的

Lua 中的 coroutine 使用 C 语言内部的 `lua_State` 数据结构来表示。每个 coroutine 都有自己独立的 `lua_State`，用于保存该 coroutine 的所有状态信息。

具体来说:

1. 每个 coroutine 都有一个独立的 `lua_State`，用于存储它自己的调用栈、局部变量、upvalues 等信息。
2. 当一个 coroutine 被暂停时，其 `lua_State` 会被保存下来。当该 coroutine 被恢复时，这个 `lua_State` 会被重新载入。
3. Lua 为 coroutine 提供了一组专门的 C 函数, 如 `lua_yieldk`、`lua_resume` 等, 用于控制 coroutine 的挂起和恢复。这些函数都是基于 `lua_State` 数据结构实现的。

总之, Lua 中的 coroutine 机制是建立在 `lua_State` 基础之上的, 每个 coroutine 都有自己独立的 `lua_State` 来保存状态信息, 从而实现了 coroutine 的功能。








--------------


Q: quickjs coroutine 使用什么数据结构表示的

QuickJS 使用协程来实现并发和异步操作。在 QuickJS 中,协程是通过以下数据结构来表示的:

1. **JSValue**：这是 QuickJS 中的核心数据类型,表示一个 JavaScript 值。协程的状态就存储在 JSValue 中。

2. **JSContext**：这个是 QuickJS 的执行环境,表示一个独立的 JavaScript 上下文。每个协程都有自己的 JSContext。

3. **JSObject**：这个是 QuickJS 的对象类型,用于表示 JavaScript 对象。协程的函数调用栈等信息就存储在 JSObject 中。

4. **JSStackFrame**：这个结构表示一个函数调用帧,用于记录函数调用的状态信息,如变量、返回地址等。协程切换时需要保存和恢复这些信息。

5. **JSRuntime**：这个是 QuickJS 的运行时,管理整个 JavaScript 执行环境,包括内存分配、垃圾回收等功能。协程的切换操作都由 JSRuntime 来完成。

总的来说,QuickJS 使用 JSValue、JSContext、JSObject 和 JSStackFrame 这些数据结构来表示和管理协程的状态和执行流程。这些数据结构相互配合,共同实现了 QuickJS 的协程功能。




--------------


