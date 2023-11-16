//
// Created by oliver on 10/29/23.
//

#include "HTTP_Status_Code.h"

std::unordered_map<int, std::string> HTTPStatusCode::error_code_map {
    {200, "OK"},
    {201, "Created"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {500, "Internal Server Error"},
};

HTTPStatusCode::HTTPStatusCode(int input_code, httplib::Response& response): res(response), error_code(input_code) {
    res.status = error_code;
    res.set_content(error_code_map[error_code], "application/json");
}

