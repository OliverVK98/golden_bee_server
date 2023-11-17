//
// Created by oliver on 10/29/23.
//

#include "HTTP_Status_Code.h"

std::unordered_map<int, std::string> error_code_map {
    {200, "OK"},
    {201, "Created"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {500, "Internal Server Error"},
};

void send_response_with_HTTP_code(int error_code, httplib::Response& response) {
    response.status = error_code;
    response.set_content(error_code_map[error_code],  "application/json");
}

void send_response_with_HTTP_code(int error_code, const std::string& error_message, httplib::Response& response) {
    response.status = error_code;
    response.set_content(error_message,  "application/json");
}

