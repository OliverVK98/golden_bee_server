//
// Created by oliver on 10/29/23.
//

#include "Router.h"
#include "../../lib/json/single_include/nlohmann/json.hpp"

void Router::Get(const std::string& route, const httplib::Server::Handler& handler) {
    svr.Get((prefix + route), handler);
}

void Router::Post(const std::string& route, const httplib::Server::Handler& handler) {
    svr.Post((prefix + route), handler);
}

void Router::Put(const std::string& route, const httplib::Server::Handler& handler) {
    svr.Put((prefix + route), handler);
}
