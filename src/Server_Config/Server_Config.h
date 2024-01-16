//
// Created by oliver on 10/25/23.
//

#ifndef UNTITLED_SERVER_CONFIG_H
#define UNTITLED_SERVER_CONFIG_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../../lib/cpp-httplib/httplib.h"
#include "../Router/Router.h"
#include "../Router/routes/Items_Routes.h"
#include "../Router/routes/Users_Routes.h"
#include "../Router/routes/OrdersRoutes.h"

class ServerConfig {
public:
    explicit ServerConfig(httplib::SSLServer& server);
    void listen();
private:
    httplib::Server& svr;
    Router router;
    ItemsRoutes items_routes;
    UsersRoutes users_routes;
    OrdersRoutes orders_routes;
};

#endif //UNTITLED_SERVER_CONFIG_H