//
// Created by oliver on 10/25/23.
//

#include "Server_Config.h"

ServerConfig::ServerConfig(httplib::SSLServer& server)
        : srv(server),
          router(server),
          items_routes(router),
          users_routes(router),
          orders_routes(router) {

    items_routes.setup();
    users_routes.setup();
    orders_routes.setup();
}

void ServerConfig::listen() {
    srv.listen("0.0.0.0", 443);
}
