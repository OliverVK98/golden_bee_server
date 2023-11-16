//
// Created by oliver on 10/25/23.
//

#include "Server_Config.h"

ServerConfig::ServerConfig(httplib::Server& server)
        : svr(server),
          router(server),
          itemsRoutes(router),
          collectionsRoutes(router),
          usersRoutes(router) {

    itemsRoutes.setup();
    collectionsRoutes.setup();
    usersRoutes.setup();

}

void ServerConfig::listen() {
    svr.listen("localhost", 3000);
}
