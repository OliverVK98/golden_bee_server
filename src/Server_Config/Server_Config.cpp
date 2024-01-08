//
// Created by oliver on 10/25/23.
//

#include "Server_Config.h"
#include "../Logger/Logger.h"

ServerConfig::ServerConfig(httplib::Server& server)
        : svr(server),
          router(server),
          items_routes(router),
          users_routes(router),
          orders_routes(router) {

    Logger console;
    items_routes.setup();
    users_routes.setup();
    orders_routes.setup();
}

void ServerConfig::listen() {
    svr.listen("0.0.0.0", 8080);
}
