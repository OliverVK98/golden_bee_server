//
// Created by oliver on 10/29/23.
//

#ifndef UNTITLED_HTTP_STATUS_CODE_H
#define UNTITLED_HTTP_STATUS_CODE_H

#include <map>
#include <string>
#include <unordered_map>
#include "httplib.h"

void send_response_with_HTTP_code(int error_code, httplib::Response &response);
void send_response_with_HTTP_code(int error_code, const std::string& error_message, httplib::Response& response);

#endif //UNTITLED_HTTP_STATUS_CODE_H