//
// Created by oliver on 10/29/23.
//

#include "HTTP_Status_Code.h"
#include "../../lib/json/single_include/nlohmann/json.hpp"

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
    nlohmann::json json_response;
    json_response["error"] = {{"code", error_code}, {"message", error_code_map[error_code]}};

    response.status = error_code;
    response.set_content(json_response.dump(), "application/json");
}

void send_response_with_HTTP_code(int error_code, const std::string& error_message, httplib::Response& response) {
    nlohmann::json json_response;
    json_response["error"] = {{"code", error_code}, {"message", error_message}};

    response.status = error_code;
    response.set_content(json_response.dump(), "application/json");
}

