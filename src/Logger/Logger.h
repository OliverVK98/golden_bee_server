//
// Created by oliver on 10/27/23.
//

#ifndef UNTITLED_LOGGER_H
#define UNTITLED_LOGGER_H

#include "string"
#include <fstream>

class Logger {
public:
    explicit Logger()
            : log_file("logs.txt", std::ios::app) {
        if (!log_file.is_open()) {
            throw std::runtime_error("Failed to open log file");
        }
    }

    void log(const std::string& message) {
        log_file << message << std::endl;
    }

    ~Logger() {
        if (log_file.is_open()) {
            log_file.close();
        }
    }

private:
    std::ofstream log_file;
};

#endif //UNTITLED_LOGGER_H
