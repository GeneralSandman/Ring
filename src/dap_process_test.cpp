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


void exampleHandler(const std::string& body) {

    dap::Message message;

    auto         err = json_decode(body, &message);
    if (err != nullptr) {
        std::cerr << "Error (" << static_cast<int>(err->type) << "): " << err->message << "\n";
        return;
    }


    std::cout << "Received message: seq=" << message.seq << ", type=" << message.type << std::endl;
}

/*

{"seq":1, "type":"request"}

*/

int process_1() {
    // 这里用标准输入作为示例
    DapMessageProcessor processor(STDIN_FILENO, exampleHandler);
    printf("Starting message processor...\n");
    processor.run();

    return 0;
}


int send_1() {
    DapMessageSender sender(STDOUT_FILENO);

    dap::Response    response1;
    sender.send(response1);

    dap::Response response2;
    sender.send(response2);

    return 0;
}

void testMessageHandler(const std::string& body) {
    if (body.empty()) {
        std::cerr << "-Received empty message" << std::endl;
        return;
    }

    dap::Request request;

    auto         err = json_decode(body, &request);
    if (err != nullptr) {
        std::cerr << "Error (" << static_cast<int>(err->type) << "): " << err->message << "\n";
        return;
    }

    std::cout << "+Received message: command=" << request.command << std::endl;
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
{"seq":1, "type":"request", "command":"initialize"}
*/


int main() {
    // send_1();
    // process_dap_handler_test_1();
    process_dap_handler_test_2();

    return 0;
}
