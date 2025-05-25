#include "dap.hpp"
#include <nlohmann/json.hpp>
#include <unordered_map>

using json = nlohmann::json;

namespace dap {


Response newResponse(int seq, int request_seq, Command command, bool success,
                     const std::string& body, const std::string& message,
                     ErrorCode errorCode) {
    Response resp;
    resp.seq         = seq;
    resp.type        = "response";
    resp.request_seq = request_seq;
    resp.command     = command;
    resp.success     = success;

    return resp;
}


} // namespace dap


namespace dap {

static const std::unordered_map<Command, std::string> CommandToString = {
    {Command::Initialize, "initialize"},
    {Command::Launch, "launch"},
    {Command::Attach, "attach"},
    {Command::Disconnect, "disconnect"},
    {Command::Terminate, "terminate"},
    {Command::Restart, "restart"},
    {Command::SetBreakpoints, "setBreakpoints"},
    {Command::SetFunctionBreakpoints, "setFunctionBreakpoints"},
    {Command::SetExceptionBreakpoints, "setExceptionBreakpoints"},
    {Command::ConfigurationDone, "configurationDone"},
    {Command::Continue, "continue"},
    {Command::Next, "next"},
    {Command::StepIn, "stepIn"},
    {Command::StepOut, "stepOut"},
    {Command::StepBack, "stepBack"},
    {Command::ReverseContinue, "reverseContinue"},
    {Command::RestartFrame, "restartFrame"},
    {Command::Goto, "goto"},
    {Command::Pause, "pause"},
    {Command::StackTrace, "stackTrace"},
    {Command::Scopes, "scopes"},
    {Command::Variables, "variables"},
    {Command::SetVariable, "setVariable"},
    {Command::Source, "source"},
    {Command::Threads, "threads"},
    {Command::TerminateThreads, "terminateThreads"},
    {Command::Modules, "modules"},
    {Command::LoadedSources, "loadedSources"},
    {Command::Evaluate, "evaluate"},
    {Command::SetExpression, "setExpression"},
    {Command::StepInTargets, "stepInTargets"},
    {Command::GotoTargets, "gotoTargets"},
    {Command::Completions, "completions"},
    {Command::ExceptionInfo, "exceptionInfo"},
    {Command::ReadMemory, "readMemory"},
    {Command::WriteMemory, "writeMemory"},
    {Command::Disassemble, "disassemble"},
    {Command::Cancel, "cancel"},
    {Command::BreakpointLocations, "breakpointLocations"}};

static const std::unordered_map<std::string, Command> StringToCommand = {
    {"initialize", Command::Initialize},
    {"launch", Command::Launch},
    {"attach", Command::Attach},
    {"disconnect", Command::Disconnect},
    {"terminate", Command::Terminate},
    {"restart", Command::Restart},
    {"setBreakpoints", Command::SetBreakpoints},
    {"setFunctionBreakpoints", Command::SetFunctionBreakpoints},
    {"setExceptionBreakpoints", Command::SetExceptionBreakpoints},
    {"configurationDone", Command::ConfigurationDone},
    {"continue", Command::Continue},
    {"next", Command::Next},
    {"stepIn", Command::StepIn},
    {"stepOut", Command::StepOut},
    {"stepBack", Command::StepBack},
    {"reverseContinue", Command::ReverseContinue},
    {"restartFrame", Command::RestartFrame},
    {"goto", Command::Goto},
    {"pause", Command::Pause},
    {"stackTrace", Command::StackTrace},
    {"scopes", Command::Scopes},
    {"variables", Command::Variables},
    {"setVariable", Command::SetVariable},
    {"source", Command::Source},
    {"threads", Command::Threads},
    {"terminateThreads", Command::TerminateThreads},
    {"modules", Command::Modules},
    {"loadedSources", Command::LoadedSources},
    {"evaluate", Command::Evaluate},
    {"setExpression", Command::SetExpression},
    {"stepInTargets", Command::StepInTargets},
    {"gotoTargets", Command::GotoTargets},
    {"completions", Command::Completions},
    {"exceptionInfo", Command::ExceptionInfo},
    {"readMemory", Command::ReadMemory},
    {"writeMemory", Command::WriteMemory},
    {"disassemble", Command::Disassemble},
    {"cancel", Command::Cancel},
    {"breakpointLocations", Command::BreakpointLocations}};

std::string commandToString(Command cmd) {
    auto it = CommandToString.find(cmd);
    if (it != CommandToString.end()) {
        return it->second;
    }
    return "unknown";
}

Command stringToCommand(const std::string& str) {
    auto it = StringToCommand.find(str);
    if (it != StringToCommand.end()) {
        return it->second;
    }
    return Command::InvalidCommand;
}

// TODO:
// 类似地实现 EventType 的转换函数...

} // namespace dap