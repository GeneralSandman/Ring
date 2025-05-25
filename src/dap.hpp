#include "json.hpp"
#include <cstdio>
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

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
std::string commandToString(Command cmd);
std::string eventTypeToString(EventType type);
Command     stringToCommand(const std::string& str);
EventType   stringToEventType(const std::string& str);


} // namespace dap


namespace dap {

struct InitializeRequestArguments {
    std::string clientID;
    std::string clientName;
    std::string adapterID;
    std::string locale;
    bool        linesStartAt1   = true;
    bool        columnsStartAt1 = true;
    std::string pathFormat;
    bool        supportsVariableType         = false;
    bool        supportsVariablePaging       = false;
    bool        supportsRunInTerminalRequest = false;
    bool        supportsMemoryReferences     = false;
    bool        supportsProgressReporting    = false;
    bool        supportsInvalidatedEvent     = false;
    bool        supportsMemoryEvent          = false;
};

struct LaunchRequestArguments {
    bool                               noDebug = false;
    std::string                        program;
    std::vector<std::string>           args;
    std::map<std::string, std::string> env;
    std::string                        cwd;
    std::string                        runtimeExecutable;
    std::vector<std::string>           runtimeArgs;
    bool                               stopOnEntry = false;
    std::string                        console;
};

struct SetBreakpointsArguments {
    struct Source {
        std::string name;
        std::string path;
    };

    Source                          source;
    std::vector<struct Breakpoint>  breakpoints;
    std::optional<std::vector<int>> lines;
    bool                            sourceModified = false;
};

struct Breakpoint {
    int                        line;
    std::optional<int>         column;
    std::optional<std::string> condition;
    std::optional<std::string> hitCondition;
    std::optional<std::string> logMessage;
};

struct ContinueArguments {
    int  threadId;
    bool singleThread = false;
};


} // namespace dap

namespace dap {

// Initialize 响应体
struct InitializeResponseBody {
    struct Capabilities {
        bool supportsConfigurationDoneRequest      = false;
        bool supportsFunctionBreakpoints           = false;
        bool supportsConditionalBreakpoints        = false;
        bool supportsHitConditionalBreakpoints     = false;
        bool supportsEvaluateForHovers             = false;
        bool supportsStepBack                      = false;
        bool supportsSetVariable                   = false;
        bool supportsRestartFrame                  = false;
        bool supportsGotoTargetsRequest            = false;
        bool supportsStepInTargetsRequest          = false;
        bool supportsCompletionsRequest            = false;
        bool supportsModulesRequest                = false;
        bool supportsRestartRequest                = false;
        bool supportsExceptionOptions              = false;
        bool supportsValueFormattingOptions        = false;
        bool supportsExceptionInfoRequest          = false;
        bool supportsTerminateDebuggee             = false;
        bool supportsSuspendDebuggee               = false;
        bool supportsDelayedStackTraceLoading      = false;
        bool supportsLoadedSourcesRequest          = false;
        bool supportsLogPoints                     = false;
        bool supportsTerminateThreadsRequest       = false;
        bool supportsSetExpression                 = false;
        bool supportsTerminateRequest              = false;
        bool supportsDataBreakpoints               = false;
        bool supportsReadMemoryRequest             = false;
        bool supportsWriteMemoryRequest            = false;
        bool supportsDisassembleRequest            = false;
        bool supportsCancelRequest                 = false;
        bool supportsBreakpointLocationsRequest    = false;
        bool supportsClipboardContext              = false;
        bool supportsSteppingGranularity           = false;
        bool supportsInstructionBreakpoints        = false;
        bool supportsExceptionFilterOptions        = false;
        bool supportsSingleThreadExecutionRequests = false;
    };

    Capabilities capabilities;
};

// Launch 响应体
struct LaunchResponseBody {
    std::optional<int>         processId;            // 被调试程序的进程ID
    std::optional<std::string> debugServerProcessId; // 调试服务器的进程ID
};


// SetBreakpoints 响应体
struct SetBreakpointsResponseBody {
    std::vector<Breakpoint> breakpoints; // 设置的断点信息
};

// StackFrame 信息
struct StackFrame {
    int                        id;               // 栈帧ID
    std::string                name;             // 栈帧名称(通常是函数名)
    std::optional<std::string> source;           // 源文件信息
    int                        line;             // 当前行号
    int                        column;           // 当前列号
    std::optional<int>         endLine;          // 结束行号
    std::optional<int>         endColumn;        // 结束列号
    std::optional<std::string> moduleId;         // 模块ID
    std::optional<std::string> presentationHint; // 表示提示('normal', 'label', 'subtle')
};

// StackTrace 响应体
struct StackTraceResponseBody {
    std::vector<StackFrame> stackFrames; // 栈帧列表
    std::optional<int>      totalFrames; // 总栈帧数(如果大于返回的数量)
};

// Variables 响应体
struct Variable {
    std::string                name;               // 变量名
    std::string                value;              // 变量值
    std::optional<std::string> type;               // 变量类型
    std::optional<int>         variablesReference; // 引用ID(用于获取子变量)
    std::optional<int>         namedVariables;     // 命名子变量数量
    std::optional<int>         indexedVariables;   // 索引子变量数量
    std::optional<std::string> memoryReference;    // 内存引用(用于大对象)
};

struct VariablesResponseBody {
    std::vector<Variable> variables; // 变量列表
};

// Threads 响应体
struct Thread {
    int         id;   // 线程ID
    std::string name; // 线程名称
};

struct ThreadsResponseBody {
    std::vector<Thread> threads; // 线程列表
};

// Evaluate 响应体
struct EvaluateResponseBody {
    std::string                result;             // 评估结果
    std::optional<std::string> type;               // 结果类型
    std::optional<int>         variablesReference; // 变量引用
    std::optional<int>         namedVariables;     // 命名变量数量
    std::optional<int>         indexedVariables;   // 索引变量数量
    std::optional<std::string> memoryReference;    // 内存引用
};

} // namespace dap


namespace dap {

struct Message {
    int         seq;
    std::string type;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Message, seq, type);
};

using RequestArguments = std::variant<
    std::monostate,
    InitializeRequestArguments,
    LaunchRequestArguments,
    SetBreakpointsArguments,
    ContinueArguments>;

using ResponseBody = std::variant<
    std::monostate, // 无响应体
    InitializeResponseBody,
    LaunchResponseBody,
    SetBreakpointsResponseBody,
    StackTraceResponseBody,
    VariablesResponseBody,
    ThreadsResponseBody,
    EvaluateResponseBody
    // 其他响应体类型...
    >;


struct Request : Message {
    Command          command;
    RequestArguments arguments;
};

struct Response : Message {
    int                         request_seq;
    Command                     command;
    bool                        success;
    std::optional<ResponseBody> body;
    std::optional<std::string>  message;   // 错误时的消息
    std::optional<ErrorCode>    errorCode; // 错误代码
};

const std::string StoppedEvent_Reason_Step                  = "step";
const std::string StoppedEvent_Reason_Breakpoint            = "breakpoint";
const std::string StoppedEvent_Reason_Exception             = "exception";
const std::string StoppedEvent_Reason_Pause                 = "pause";
const std::string StoppedEvent_Reason_Entry                 = "entry";
const std::string StoppedEvent_Reason_Goto                  = "goto";
const std::string StoppedEvent_Reason_FunctionBreakpoint    = "functionBreakpoint";
const std::string StoppedEvent_Reason_DataBreakpoint        = "dataBreakpoint";
const std::string StoppedEvent_Reason_InstructionBreakpoint = "instructionBreakpoint";


struct StoppedEvent {

    enum class Reason {
        Step,
        Breakpoint,
        Exception,
        Pause,
        Entry,
        Goto,
        FunctionBreakpoint,
        DataBreakpoint,
        InstructionBreakpoint,
    };


    std::string event = "stopped";

    struct Body {
        std::string reason;            // 停止的原因
        int         threadId;          // 停止的线程ID
        bool        allThreadsStopped; // 是否所有线程都已停止

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Body, reason, threadId, allThreadsStopped);

    } body;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StoppedEvent, event, body);
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


void sendEvent(const StoppedEvent& event) {
    std::string body = json_encode(event);
    printf("%s^@^\r\n", body.c_str());
}


} // namespace dap
