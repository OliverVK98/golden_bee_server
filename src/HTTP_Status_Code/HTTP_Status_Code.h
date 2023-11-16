//
// Created by oliver on 10/29/23.
//

#ifndef UNTITLED_HTTP_STATUS_CODE_H
#define UNTITLED_HTTP_STATUS_CODE_H

#include <map>
#include <string>
#include <unordered_map>
#include "httplib.h"

class HTTPStatusCode {
private:
    static std::unordered_map<int, std::string> error_code_map;
    int error_code;
    httplib::Response& res;

public:
    HTTPStatusCode(int input_code, httplib::Response& response);
};

#endif //UNTITLED_HTTP_STATUS_CODE_H
