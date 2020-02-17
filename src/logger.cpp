#include "logger.hpp"
#include "string.hpp"
#include <iostream>
#include <fstream>

using ze::Logger;
using ze::string;
using ze::object;

std::vector<string> Logger::messages;

void Logger::LogMsg(const string& msg) {
    messages.push_back(msg);
    std::cout << msg.c_str() << std::endl;
}

// void Logger::LogMsg(const char* msg) {
//     messages.push_back(msg);
//     std::cout << msg << std::endl;
// }

void Logger::LogMsg(const string& msg, const object& obj) {
    messages.push_back(msg);
    std::cout << msg.c_str() << std::endl;
}

// void Logger::LogMsg(const char* msg, const object& obj) {
//     messages.push_back(msg);
//     std::cout << msg << std::endl;
// }

void Logger::LogErr(const string& err_msg) {
    messages.push_back(err_msg);
    std::cerr << err_msg.c_str() << std::endl;
}

// void Logger::LogErr(const char* err_msg) {
//     messages.push_back(err_msg);
//     std::cerr << err_msg << std::endl;
// }

void Logger::LogErr(const string& err_msg, const object& obj) {
    messages.push_back(err_msg);
    std::cerr << err_msg.c_str() << std::endl;
}

// void Logger::LogErr(const char* err_msg, const object& obj) {
//     messages.push_back(err_msg);
//     std::cerr << err_msg << std::endl;
// }

void Logger::OutLog(const char* path) {
    std::fstream output_file;
    output_file.open(path, std::ios::out);
    if (output_file.is_open()) {
        for (auto line : messages) {
            output_file << line.c_str() << std::endl;
        }
        output_file.close();
        std::cout << "Log saved to " << path << std::endl;
    } else LogErr("Failed to open file!");
}
