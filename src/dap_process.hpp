
#ifndef RING_DAP_PROCESS_INCLUDE_H
#define RING_DAP_PROCESS_INCLUDE_H

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


class DapMessageSender {
public:
    explicit DapMessageSender(int fd) :
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

class DapMessageProcessor {
public:
    using HandlerType = std::function<void(const std::string&)>;

    DapMessageProcessor(int fd, HandlerType handler, size_t max_size = 10 * 1024 * 1024) :
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

    std::string get_a_message() {
        try {
            std::string message;
            if (!receiveMessage(message)) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    // TODO: 非阻塞模式下的无数据情况
                    return message;
                }
                // 错误
                // TODO: 后续处理
                return message;
            }

            return message;
        } catch (const std::exception& e) {
            std::cerr << "Error processing message: " << e.what() << std::endl;
            // 可以选择继续处理下一条消息或退出
        }

        return "";
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

#endif // RING_DAP_PROCESS_INCLUDE_H