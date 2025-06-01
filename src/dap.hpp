#ifndef RING_DAP_INCLUDE_H
#define RING_DAP_INCLUDE_H

#include "json.hpp"
#include <cstdio>
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

using json = nlohmann::json;

// ------- 常量和枚举定义 --------
namespace dap {

enum class Command {
    Initialize,
    Launch,
    Attach,
    Disconnect,
    Terminate,
    Restart,
    SetBreakpoints,
    SetFunctionBreakpoints,
    SetExceptionBreakpoints,
    ConfigurationDone,
    Continue,
    Next,
    StepIn,
    StepOut,
    StepBack,
    ReverseContinue,
    RestartFrame,
    Goto,
    Pause,
    StackTrace,
    Scopes,
    Variables,
    SetVariable,
    Source,
    Threads,
    TerminateThreads,
    Modules,
    LoadedSources,
    Evaluate,
    SetExpression,
    StepInTargets,
    GotoTargets,
    Completions,
    ExceptionInfo,
    ReadMemory,
    WriteMemory,
    Disassemble,
    Cancel,
    BreakpointLocations,
    InvalidCommand
};
using CommandType                    = std::string;
const std::string Command_Initialize = "initialize";
const std::string Command_Launch     = "launch";
const std::string Command_Attach     = "attach";


enum class EventType {
    Initialized,
    Stopped,
    Continued,
    Exited,
    Terminated,
    Thread,
    Output,
    Breakpoint,
    Module,
    LoadedSource,
    Process,
    Capabilities,
    ProgressStart,
    ProgressUpdate,
    ProgressEnd,
    InvalidEvent
};

enum class ErrorCode {
    ParseError       = -32700,
    InvalidRequest   = -32600,
    MethodNotFound   = -32601,
    InvalidParams    = -32602,
    InternalError    = -32603,
    ServerErrorStart = -32099,
    ServerErrorEnd   = -32000,
    RequestCanceled  = -32800,
    ContentTooLarge  = -32801,
    UnknownError     = -1
};

// 辅助函数：枚举转字符串
std::string       commandToString(Command cmd);
std::string       eventTypeToString(EventType type);
Command           stringToCommand(const std::string& str);
EventType         stringToEventType(const std::string& str);


const std::string StoppedEvent_Reason_Step                  = "step";
const std::string StoppedEvent_Reason_Breakpoint            = "breakpoint";
const std::string StoppedEvent_Reason_Exception             = "exception";
const std::string StoppedEvent_Reason_Pause                 = "pause";
const std::string StoppedEvent_Reason_Entry                 = "entry";
const std::string StoppedEvent_Reason_Goto                  = "goto";
const std::string StoppedEvent_Reason_FunctionBreakpoint    = "functionBreakpoint";
const std::string StoppedEvent_Reason_DataBreakpoint        = "dataBreakpoint";
const std::string StoppedEvent_Reason_InstructionBreakpoint = "instructionBreakpoint";

} // namespace dap


// ------- 基础消息类型定义 --------
namespace dap {

// 公共消息头
struct DAPMessage {
    int         seq;
    std::string type;
    std::string command;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DAPMessage, seq, type, command);
};

// 通用响应结构
struct DAPResponse {
    int                        seq;
    int                        request_seq;
    std::string                type;
    std::string                command;
    bool                       success;
    std::optional<std::string> message;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DAPResponse, seq, request_seq, type, command, success, message);
};

// Source 类型
struct Source {
    std::string                name;
    std::optional<std::string> path;
    std::optional<int>         sourceReference;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Source, name, path, sourceReference);
};

// StackFrame 类型
struct StackFrame {
    int                        id;
    std::string                name;
    std::optional<Source>      source;
    int                        line;
    int                        column;
    std::optional<int>         endLine;
    std::optional<int>         endColumn;
    std::optional<std::string> moduleId;
    std::optional<std::string> presentationHint;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StackFrame,
                                   id, name, source, line, column,
                                   endLine, endColumn, moduleId, presentationHint);
};

// Thread 类型
struct Thread {
    int                        id;
    std::string                name;
    std::optional<std::string> state;       // TODO: 使用枚举类型代替
    std::optional<std::string> pauseReason; // TODO: 使用枚举类型代替
};
inline void to_json(nlohmann::json& j, const Thread& t) {
    j = nlohmann::json{
        {"id", t.id},
        {"name", t.name},
        {"state", t.state ? nlohmann::json(*t.state) : nlohmann::json()},
        {"pauseReason", t.pauseReason ? nlohmann::json(*t.pauseReason) : nlohmann::json()}};
}
inline void from_json(const nlohmann::json& j, Thread& t) {
    j.at("id").get_to(t.id);
    j.at("name").get_to(t.name);

    if (j.contains("state") && !j["state"].is_null()) {
        t.state = j["state"].get<std::string>();
    } else {
        t.state = std::nullopt;
    }

    if (j.contains("pauseReason") && !j["pauseReason"].is_null()) {
        t.pauseReason = j["pauseReason"].get<std::string>();
    } else {
        t.pauseReason = std::nullopt;
    }
}

} // namespace dap


// ------- request/response 定义 --------
// initialize
namespace dap {
struct InitializeRequestArguments {
    std::string clientID;
    std::string clientName;
    std::string adapterID;
    std::string locale;
    bool        linesStartAt1;
    bool        columnsStartAt1;
    std::string pathFormat;

    // 能力标志 (部分示例)
    bool supportsVariableType;
    bool supportsVariablePaging;
    bool supportsRunInTerminalRequest;
    bool supportsMemoryReferences;
    // ... 其他能力标志

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        InitializeRequestArguments,
        clientID, clientName, adapterID, locale,
        linesStartAt1, columnsStartAt1, pathFormat,
        supportsVariableType, supportsVariablePaging,
        supportsRunInTerminalRequest, supportsMemoryReferences)
};
// 异常断点过滤器
struct ExceptionBreakpointsFilter {
    std::string filter;
    std::string label;
    bool        default_;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        ExceptionBreakpointsFilter,
        filter, label, default_)
};

// Initialize 响应体
struct InitializeResponseBody {
    bool                                    supportsConfigurationDoneRequest;
    bool                                    supportsFunctionBreakpoints;
    bool                                    supportsConditionalBreakpoints;
    std::vector<ExceptionBreakpointsFilter> exceptionBreakpointFilters;
    bool                                    supportsSetVariable;
    bool                                    supportsStepBack;
    // ... 其他能力标志

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        InitializeResponseBody,
        supportsConfigurationDoneRequest,
        supportsFunctionBreakpoints,
        supportsConditionalBreakpoints,
        exceptionBreakpointFilters,
        supportsSetVariable,
        supportsStepBack)
};


struct InitializeRequest : DAPMessage {
    InitializeRequestArguments arguments;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(InitializeRequest, seq, type, command, arguments);
};
struct InitializeResponse : DAPResponse {
    InitializeResponseBody body;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(InitializeResponse, seq, request_seq, type, command, success, message, body);
};

} // namespace dap


// ------- request/response 定义 --------
// launch
namespace dap {

struct LaunchRequestArguments {
    std::string                                      program;
    std::vector<std::string>                         args;
    std::string                                      cwd;
    std::vector<std::pair<std::string, std::string>> environment;
    bool                                             stopAtEntry;
    std::string                                      console;
    std::optional<std::string>                       symbolSearchPath;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        LaunchRequestArguments,
        program, args, cwd, environment,
        stopAtEntry, console, symbolSearchPath)
};
// 错误信息
struct LaunchErrorBody {
    int                                id;
    std::string                        format;
    std::map<std::string, std::string> variables;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        LaunchErrorBody,
        id, format, variables)
};

struct LaunchResponseBody {
    std::optional<LaunchErrorBody> error; // 可选的错误信息
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LaunchResponseBody, error);
};

struct LaunchRequest : DAPMessage {
    LaunchRequestArguments arguments;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LaunchRequest, seq, type, command, arguments);
};
struct LaunchResponse : DAPResponse {
    LaunchResponseBody body;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(LaunchResponse, seq, request_seq, type, command, success, message, body);
};


} // namespace dap


// ------- request/response 定义 --------
// threads
namespace dap {


// threads 请求 (无参数)
struct ThreadsRequest : DAPMessage {};

// threads 响应
struct ThreadsResponseBody {
    std::vector<Thread> threads;
};
struct ThreadsResponse : DAPResponse {
    ThreadsResponseBody body;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ThreadsResponse, seq, request_seq, type, command, success, message, body);
};

// JSON 序列化/反序列化
inline void to_json(json& j, const ThreadsResponseBody& t) {
    j = json{{"threads", t.threads}};
}

inline void from_json(const json& j, ThreadsResponseBody& t) {
    j.at("threads").get_to(t.threads);
}


} // namespace dap


// ------- request/response 定义 --------
// stackTrace
namespace dap {

// stackTrace 请求参数
struct StackTraceArguments {
    int                threadId;
    std::optional<int> startFrame;
    std::optional<int> levels;
};
struct StackTraceRequest : DAPMessage {
    StackTraceArguments arguments;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StackTraceRequest, seq, type, command, arguments);
};

struct StackTraceResponseBody {
    std::vector<StackFrame> stackFrames;
    std::optional<int>      totalFrames;
};
struct StackTraceResponse : DAPResponse {
    StackTraceResponseBody body;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StackTraceResponse, seq, request_seq, type, command, success, message, body);
};


// stackTrace 响应


inline void to_json(json& j, const StackTraceArguments& s) {
    j = json{{"threadId", s.threadId}};
    if (s.startFrame)
        j["startFrame"] = *s.startFrame;
    if (s.levels)
        j["levels"] = *s.levels;
}
inline void from_json(const json& j, StackTraceArguments& s) {
    j.at("threadId").get_to(s.threadId);
    if (j.contains("startFrame"))
        s.startFrame = j["startFrame"];
    if (j.contains("levels"))
        s.levels = j["levels"];
}

inline void to_json(json& j, const StackTraceResponseBody& s) {
    j = json{{"stackFrames", s.stackFrames}};
    if (s.totalFrames)
        j["totalFrames"] = *s.totalFrames;
}
inline void from_json(const json& j, StackTraceResponseBody& s) {
    j.at("stackFrames").get_to(s.stackFrames);
    if (j.contains("totalFrames"))
        s.totalFrames = j["totalFrames"];
}

} // namespace dap


// ------- request/response 定义 --------
// continue
namespace dap {

// continue 请求参数
struct ContinueArguments {
    int                 threadId;
    std::optional<bool> singleThread;
};

struct ContinueRequest : DAPMessage {
    ContinueArguments arguments;
};

// continue 响应
struct ContinueResponseBody {
    std::optional<bool> allThreadsContinued;
};
struct ContinueResponse : DAPResponse {
    ContinueResponseBody body;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ContinueResponse, seq, request_seq, type, command, success, message, body);
};

// JSON 序列化/反序列化
inline void to_json(json& j, const ContinueArguments& c) {
    j = json{{"threadId", c.threadId}};
    if (c.singleThread)
        j["singleThread"] = *c.singleThread;
}

inline void from_json(const json& j, ContinueArguments& c) {
    j.at("threadId").get_to(c.threadId);
    if (j.contains("singleThread"))
        c.singleThread = j["singleThread"];
}

inline void to_json(json& j, const ContinueResponseBody& c) {
    if (c.allThreadsContinued)
        j["allThreadsContinued"] = *c.allThreadsContinued;
}

inline void from_json(const json& j, ContinueResponseBody& c) {
    if (j.contains("allThreadsContinued")) {
        c.allThreadsContinued = j["allThreadsContinued"];
    }
}

} // namespace dap


// ------- event 定义 --------
namespace dap {

struct InitializedEvent {
    int         seq   = 0; // 序列号
    std::string type  = "event";
    std::string event = "initialized";

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(InitializedEvent, seq, type, event);
};

struct StoppedEvent {
    int         seq   = 0; // 序列号
    std::string type  = "event";
    std::string event = "stopped";
    struct Body {
        std::string reason;            // 停止的原因
        int         threadId;          // 停止的线程ID
        bool        allThreadsStopped; // 是否所有线程都已停止
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Body, reason, threadId, allThreadsStopped);
    } body;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StoppedEvent, seq, type, event, body);
};


struct OutputEvent {
    enum class Category {
        Console,
        Important,
        Stdout,
        Stderr,
        Telemetry
    };
    std::string event = "output";
    struct Body {
        std::string output;                 // 输出内容
        std::string category;               // 输出类别
        int         variablesReference = 0; // 变量引用
        std::string source;
        int         line;
        int         column;
        std::string data;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Body, output, category, variablesReference, source, line, column, data);
    } body;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(OutputEvent, event, body);
};


} // namespace dap


#endif // RING_DAP_INCLUDE_H
