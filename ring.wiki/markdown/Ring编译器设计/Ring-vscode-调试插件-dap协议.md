

## stoppedEvent


```json
{
  "type": "event",
  "event": "stopped",
  "body": {
    "reason": "entry",
    "threadId": 1,
    "allThreadsStopped": true,
    "preserveFocusHint": false,
    "text": "Paused at entry point",
    "description": "Program paused at the entry point before execution begins"
  },
  "seq": 123
}
```

type: 固定为 "event"，表示这是一个事件
event: 固定为 "stopped"，表示线程停止事件
body.reason: 值为 "entry"，表示停止原因是程序入口点
body.threadId: 停止的线程ID
body.allThreadsStopped: 布尔值，表示是否所有线程都停止了
body.preserveFocusHint: 可选，提示UI是否应保持当前焦点
body.text: 可选的简短描述文本
body.description: 可选的详细描述文本
seq: 序列号，用于协议通信的顺序标识


## stacktrace 的 request 和 response


StackTrace 请求 (Request)
客户端发送给调试器的请求格式：

```json
{
  "type": "request",
  "command": "stackTrace",
  "arguments": {
    "threadId": 1,
    "startFrame": 0,
    "levels": 20,
    "format": {
      "parameters": true,
      "parameterTypes": true,
      "parameterNames": true,
      "line": true,
      "module": true,
      "includeAll": false
    }
  },
  "seq": 42
}
```

请求参数说明:
threadId (必需): 要获取堆栈的线程ID
startFrame (可选): 从哪个帧开始获取(默认为0，即最顶层的帧)
levels (可选): 要获取的帧数量(默认为所有帧)
format (可选): 控制堆栈帧如何格式化
parameters: 是否包含参数值
parameterTypes: 是否包含参数类型
parameterNames: 是否包含参数名
line: 是否包含源代码行
module: 是否包含模块名
includeAll: 是否包含所有可能的信息



StackTrace 响应 (Response)
调试器返回的响应格式：


```json
{
  "type": "response",
  "command": "stackTrace",
  "success": true,
  "body": {
    "stackFrames": [
      {
        "id": 1000,
        "name": "main",
        "source": {
          "name": "app.js",
          "path": "/path/to/app.js",
          "sourceReference": 0
        },
        "line": 10,
        "column": 5,
        "endLine": 10,
        "endColumn": 15,
        "moduleId": "module1",
        "presentationHint": "normal"
      },
      {
        "id": 1001,
        "name": "calculate",
        "source": {
          "name": "math.js",
          "path": "/path/to/math.js",
          "sourceReference": 0
        },
        "line": 25,
        "column": 10,
        "endLine": 25,
        "endColumn": 20,
        "moduleId": "module2",
        "presentationHint": "label"
      }
    ],
    "totalFrames": 15
  },
  "seq": 42,
  "request_seq": 42
}
```

响应参数说明:
stackFrames (必需): 堆栈帧数组，按从顶部到底部的顺序排列
id: 帧的唯一标识符(用于后续的scopes请求)
name: 帧的名称(通常是函数名)
source: 源代码位置信息
line, column: 当前执行位置
endLine, endColumn: 可选，函数/块的结束位置
moduleId: 可选，模块标识符
presentationHint: 可选，显示提示("normal", "label", "subtle")
totalFrames (可选): 总帧数(如果levels参数限制了返回数量)

如果请求失败，响应可能如下：

```json
{
  "type": "response",
  "command": "stackTrace",
  "success": false,
  "message": "Thread not found",
  "seq": 42,
  "request_seq": 42
}
```



## threads 的 request和response


Threads 请求 (Request)
客户端发送给调试器的请求格式：

```json
{
  "type": "request",
  "command": "threads",
  "arguments": {},
  "seq": 123
}
```

请求说明:
这是最简单的 DAP 请求之一，通常不需要任何参数
当调试会话开始或线程状态改变时，客户端通常会发送此请求


Threads 响应 (Response)
调试器返回的响应格式：

```json
{
  "type": "response",
  "command": "threads",
  "success": true,
  "body": {
    "threads": [
      {
        "id": 1,
        "name": "main thread",
        "state": "stopped",
        "pauseReason": "entry"
      },
      {
        "id": 2,
        "name": "worker thread #1",
        "state": "running"
      },
      {
        "id": 3,
        "name": "background thread",
        "state": "stopped",
        "pauseReason": "breakpoint"
      }
    ]
  },
  "seq": 123,
  "request_seq": 123
}
```

响应参数说明:
threads 数组中的每个线程对象包含：
id (必需): 线程的唯一标识符
name (必需): 线程的名称(用于显示)
state (可选): 线程状态，通常是：
"running": 线程正在运行
"stopped": 线程已停止
"terminated": 线程已终止

pauseReason (可选): 如果线程停止，说明停止原因，常见值包括：
"entry": 在程序入口点停止
"breakpoint": 因断点停止
"exception": 因异常停止
"pause": 用户手动暂停
"step": 单步执行后停止
"debugger_stopped": 调试器停止



如果请求失败，响应可能如下：

```json
{
  "type": "response",
  "command": "threads",
  "success": false,
  "message": "Debug session not active",
  "seq": 123,
  "request_seq": 123
}
```


使用场景
调试会话初始化：当调试会话启动时，客户端通常会请求线程列表
线程状态变化：当收到stopped事件时，客户端可能会刷新线程列表
多线程调试：在多线程程序中，客户端需要定期更新线程状态

注意事项
线程ID在整个调试会话期间必须保持稳定
即使没有多线程，调试器也应返回至少一个线程(通常是主线程)
线程名称应尽可能具有描述性，便于用户识别



## continue 指令 的 request/response


Continue 请求 (Request)
客户端发送给调试器的请求格式：

```json
{
  "type": "request",
  "command": "continue",
  "arguments": {
    "threadId": 1,
    "singleThread": false
  },
  "seq": 456
}
```

请求参数说明:

threadId (必需): 要恢复执行的线程ID
singleThread (可选): 布尔值，表示是否只恢复指定线程(在多线程调试中)
  如果为 true，则只恢复指定线程
  如果为 false 或省略，则恢复所有暂停的线程


Continue 响应 (Response)
调试器返回的成功响应格式：

```json
{
  "type": "response",
  "command": "continue",
  "success": true,
  "body": {
    "allThreadsContinued": false
  },
  "seq": 456,
  "request_seq": 456
}
```

响应参数说明:

body.allThreadsContinued (可选): 布尔值，表示是否所有线程都被恢复了
如果为 true，表示所有线程都恢复了执行
如果为 false，表示只有请求中指定的线程恢复了执行


如果请求失败，响应可能如下：

```json
{
  "type": "response",
  "command": "continue",
  "success": false,
  "message": "Thread not found",
  "seq": 456,
  "request_seq": 456
}
```



## exited/terminated


程序正常结束：

```json
{
  "type": "event",
  "event": "exited",
  "body": {
    "exitCode": 0
  },
  "seq": 457
}
```


程序异常终止：

```json
{
  "type": "event",
  "event": "terminated",
  "body": {},
  "seq": 457
}
```