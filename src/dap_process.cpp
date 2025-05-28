#include "dap.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <poll.h>
#include <stdexcept>
#include <string>
#include <system_error>
#include <unistd.h>


class MessageSender {
public:
    explicit MessageSender(int fd) :
        write_fd(fd) {
    }

    template <typename T>
    bool send(const T& data) {
        auto result = json_encode(data);
        if (JsonError* err = std::get_if<JsonError>(&result)) {
            // 处理错误
            std::cerr << "Error (" << static_cast<int>(err->type) << "): " << err->message << "\n";
            return false;
        }

        std::string* message = std::get_if<std::string>(&result);
        message->push_back('\n');
        return writeAll(message->data(), message->size());
    }

protected:
    // 确保写入所有数据
    bool writeAll(const char* data, size_t length) {
        size_t written = 0;
        while (written < length) {
            ssize_t n = write(write_fd, data + written, length - written);
            if (n <= 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    continue; // 非阻塞模式下重试
                }
                perror("write failed");
                return false;
            }
            written += n;
        }
        return true;
    }

private:
    int write_fd; // 文件描述符
};

class MessageProcessor {
public:
    using HandlerType = std::function<void(const std::string&)>;

    MessageProcessor(int fd, HandlerType handler, size_t max_size = 10 * 1024 * 1024) :
        read_fd(fd), message_handler(handler), message_max_size(max_size) {
    }

    // 主循环，持续读取并处理消息
    void run() {
        while (true) {
            try {
                std::string message;
                if (!receiveMessage(message)) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        continue; // 非阻塞模式下的无数据情况
                    }
                    break; // 真正的错误或EOF
                }

                message_handler(message);

            } catch (const std::exception& e) {
                std::cerr << "Error processing message: " << e.what() << std::endl;
                // 可以选择继续处理下一条消息或退出
            }
        }
    }

protected:
    // 接收一条完整消息(以换行符结尾)
    bool receiveMessage(std::string& message) {
        message.clear();
        char ch;

        while (read(read_fd, &ch, 1) == 1) {
            if (ch == '\n') {
                // 处理可能的Windows换行\r\n
                if (!message.empty() && message.back() == '\r') {
                    message.pop_back();
                }
                return true;
            }

            message += ch;

            // 防止消息过大导致内存耗尽
            if (message.size() > message_max_size) {
                throw std::runtime_error("Message too large, max size: " + std::to_string(message_max_size));
            }
        }

        return false; // 读取失败或EOF
    }


protected:
    int         read_fd;          // 文件描述符
    HandlerType message_handler;  // 消息处理器
    size_t      message_max_size; // 最大消息大小限制
};


class RobustMessageProcessor : public MessageProcessor {
public:
    using MessageProcessor::MessageProcessor;

    void run() {
        struct pollfd pfd = {read_fd, POLLIN, 0};

        while (true) {
            try {
                // 等待数据到达，带超时(1000ms)
                int ret = poll(&pfd, 1, 1000);
                if (ret == -1) {
                    throw std::system_error(errno, std::system_category(), "poll failed");
                }

                if (ret == 0) {
                    onTimeout();
                    continue;
                }

                if (pfd.revents & POLLIN) {
                    std::string message;
                    if (!receiveMessage(message)) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            continue;
                        }
                        onConnectionClosed();
                        break;
                    }

                    message_handler(message);
                }

                if (pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
                    onConnectionError();
                    break;
                }

            } catch (const std::exception& e) {
                onError(e);
                // 可以选择继续或退出
                if (shouldStopOnError())
                    break;
            }
        }
    }

protected:
    virtual void onTimeout() {
        // 默认空实现，子类可以覆盖
    }

    virtual void onConnectionClosed() {
        std::cout << "Connection closed by peer" << std::endl;
    }

    virtual void onConnectionError() {
        std::cerr << "Connection error occurred" << std::endl;
    }

    virtual void onError(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    virtual bool shouldStopOnError() const {
        return true; // 默认出错时停止
    }
};


void exampleHandler(const std::string& body_) {

    dap::Message message;

    auto         err = json_decode(body_, &message);
    if (err != nullptr) {
        // 处理错误
        std::cerr << "Error (" << static_cast<int>(err->type) << "): " << err->message << "\n";
        return;
    }


    std::cout << "Received message: seq=" << message.seq << ", type=" << message.type << std::endl;
}

/*

{"seq":1, "type":"request"}

*/

int process_1() {
    int              fd = STDIN_FILENO; // 这里用标准输入作为示例
    MessageProcessor processor(fd, exampleHandler);
    printf("Starting message processor...\n");
    processor.run();

    return 0;
}

int process_2() {
    int                    fd = STDIN_FILENO; // 这里用标准输入作为示例
    RobustMessageProcessor processor(fd, exampleHandler);
    printf("Starting message processor...\n");
    processor.run();

    return 0;
}

int send_1() {
    MessageSender sender(STDOUT_FILENO);

    dap::Response response1;
    sender.send(response1);

    dap::Response response2;
    sender.send(response2);

    return 0;
}

/*

int main() {
    send_1();
}

*/