#include "dap.hpp"
#include "dap_process.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <poll.h>
#include <stdexcept>
#include <string>
#include <system_error>
#include <unistd.h>


// event
int send_1() {
    DapMessageSender  sender(STDOUT_FILENO);

    dap::StoppedEvent event1;
    sender.send(event1);

    dap::StoppedEvent event2;
    sender.send(event2);

    return 0;
}

// response
int send_2() {
    DapMessageSender sender(STDOUT_FILENO);

    // initialize_response
    dap::InitializeResponse initialize_response = dap::InitializeResponse{
        {
            .seq         = 1,
            .request_seq = 1,
            .type        = "response",
            .command     = "initialize",
            .success     = true,
            .message     = "",
        },
        .body = dap::InitializeResponseBody{
            .supportsConfigurationDoneRequest = true,
            .supportsFunctionBreakpoints      = true,
            .supportsConditionalBreakpoints   = true,
            .exceptionBreakpointFilters       = std::vector<dap::ExceptionBreakpointsFilter>{},
            .supportsSetVariable              = true,
            .supportsStepBack                 = true,
        },
    };
    sender.send(initialize_response);


    // launch_response
    dap::LaunchResponse launch_response = dap::LaunchResponse{
        {
            .seq         = 2,
            .request_seq = 2,
            .type        = "response",
            .command     = "launch",
            .success     = true,
            .message     = "",
        },
        .body = dap::LaunchResponseBody{
            .error = dap::LaunchErrorBody{
                .id        = 1,
                .format    = "Launch failed",
                .variables = {{"reason", "Invalid program path"}},
            },
        },
    };
    sender.send(launch_response);


    // threads_response
    dap::ThreadsResponse threads_response = dap::ThreadsResponse{
        {
            .seq         = 1,
            .request_seq = 1,
            .type        = "response",
            .command     = "threads",
            .success     = true,
            .message     = "",
        },
        .body = dap::ThreadsResponseBody{
            .threads = std::vector<dap::Thread>{
                {
                    .id          = 1,
                    .name        = "thread-1",
                    .state       = "stopped",
                    .pauseReason = "entry",
                },
            },
        },
    };
    sender.send(threads_response);


    dap::StackTraceResponse stack_trace_response = dap::StackTraceResponse{
        {
            .seq         = 2,
            .request_seq = 2,
            .type        = "response",
            .command     = "stackTrace",
            .success     = true,
            .message     = "",
        },
        .body = dap::StackTraceResponseBody{
            .stackFrames = std::vector<dap::StackFrame>{
                {
                    .id        = 0,
                    .name      = "main",
                    .line      = 10,
                    .column    = 5,
                    .endLine   = 10,
                    .endColumn = 5,
                },
            },
            .totalFrames = 1,
        }};
    sender.send(stack_trace_response);


    dap::ContinueResponse continue_response = dap::ContinueResponse{
        {
            .seq         = 3,
            .request_seq = 3,
            .type        = "response",
            .command     = "continue",
            .success     = true,
            .message     = "",
        },
        .body = dap::ContinueResponseBody{
            .allThreadsContinued = true,
        },
    };
    sender.send(continue_response);


    return 0;
}

void testMessageHandler(const std::string& body) {
    if (body.empty()) {
        std::cerr << "-Received empty message" << std::endl;
        return;
    }

    dap::DAPMessage dap_message;

    auto            err = json_decode(body, &dap_message);
    if (err != nullptr) {
        std::cerr << "Error (" << static_cast<int>(err->type) << "): " << err->message << "\n";
        return;
    }

    std::cout << "+Received message: command=" << dap_message.command << std::endl;
    if (dap_message.command == "threads") {
        dap::ThreadsRequest threads_request;
        err = json_decode(body, &threads_request);
        std::cout << "+ThreadsRequest: \n"
                  << "seq=" << threads_request.seq
                  << ", type=" << threads_request.type
                  << ", command=" << threads_request.command
                  << std::endl;
    } else if (dap_message.command == "stackTrace") {
        dap::StackTraceRequest stack_trace_request;
        err = json_decode(body, &stack_trace_request);
        std::cout << "+StackTraceRequest: \n"
                  << "seq=" << stack_trace_request.seq
                  << ", type=" << stack_trace_request.type
                  << ", command=" << stack_trace_request.command
                  << std::endl;

        std::cout << "\t arguments:"
                  << "threadId:" << stack_trace_request.arguments.threadId
                  << std::endl;

    } else if (dap_message.command == "continue") {

        dap::ContinueRequest continue_request;
        err = json_decode(body, &continue_request);
        std::cout << "+ContinueRequest: \n"
                  << "seq=" << continue_request.seq
                  << ", type=" << continue_request.type
                  << ", command=" << continue_request.command
                  << std::endl;

        std::cout << "\t arguments:"
                  << "threadId:" << continue_request.arguments.threadId
                  << ", singleThread:" << (continue_request.arguments.singleThread ? *continue_request.arguments.singleThread : false)
                  << std::endl;

    } else {
        std::cerr << "Unknown command: " << dap_message.command << "\n";
        return;
    }

    if (err != nullptr) {
        std::cerr << "Error (" << static_cast<int>(err->type) << "): " << err->message << "\n";
        return;
    }
}

// 循环处理消息
int process_dap_handler_test_1() {

    DapMessageProcessor processor(STDIN_FILENO, testMessageHandler);
    printf("Starting message processor...\n");
    processor.run();

    return 0;
}

// 一次只处理一个消息
int process_dap_handler_test_2() {

    DapMessageProcessor processor(STDIN_FILENO, testMessageHandler);
    printf("Starting message processor...\n");

    while (true) {
        std::string message = processor.get_a_message();
        printf("-Received message: %s\n", message.c_str());
        if (message == "q") {
            printf("Exiting message processor...\n");
            break;
        }
        testMessageHandler(message);
    }


    return 0;
}

/*

缺失seq 字段
{"seq1":1, "type":"request", "command":"initialize"}

正常
{"seq":1, "type":"request", "command":"threads", "arguments":{}}

{"seq":1, "type":"request", "command":"stackTrace", "arguments":{}}
{"seq":1, "type":"request", "command":"stackTrace", "arguments":{"threadId":1,"startFrame":0,"levels":20}}

{"seq":1, "type":"request", "command":"continue", "arguments":{"threadId":1,"singleThread":false}}
*/


int main() {
    // send_1();
    send_2();


    // process_dap_handler_test_1();
    // process_dap_handler_test_2();

    return 0;
}
