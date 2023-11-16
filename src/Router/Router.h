//
// Created by oliver on 10/29/23.
//

#ifndef UNTITLED_ROUTER_H
#define UNTITLED_ROUTER_H

#include "httplib.h"
#include "unordered_map"
#include "string"

class Router {
private:
    httplib::Server& svr;
    std::string prefix = "/api";

public:
    explicit Router(httplib::Server& server) : svr(server) {};
    void Get(const std::string& route, const httplib::Server::Handler& handler);
    void Post(const std::string& route, const httplib::Server::Handler& handler);
    void Put(const std::string& route, const httplib::Server::Handler& handler);
};

#endif //UNTITLED_ROUTER_H
