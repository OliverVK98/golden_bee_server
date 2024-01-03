//
// Created by oliver on 10/29/23.
//

#include "Router.h"
#include "../../lib/json/single_include/nlohmann/json.hpp"

void Router::set_cors_headers(httplib::Response &res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
}

void Router::Get(const std::string& route, const httplib::Server::Handler& handler) {
    svr.Get(prefix + route, [handler](const httplib::Request& req, httplib::Response& res) {
        set_cors_headers(res);
        handler(req, res);
    });
}

void Router::Post(const std::string& route, const httplib::Server::Handler& handler) {
    svr.Post(prefix + route, [handler](const httplib::Request& req, httplib::Response& res) {
        set_cors_headers(res);
        handler(req, res);
    });
}

void Router::Put(const std::string& route, const httplib::Server::Handler& handler) {
    svr.Put(prefix + route, [handler](const httplib::Request& req, httplib::Response& res) {
        set_cors_headers(res);
        handler(req, res);
    });
}

void Router::Options(const std::string& route, const httplib::Server::Handler& handler) {
    svr.Options(prefix + route, [handler](const httplib::Request& req, httplib::Response& res) {
        set_cors_headers(res);
        handler(req, res);
    });
}
