//
// Created by oliver on 10/25/23.
//

#include "Server_Config.h"
#include "../Logger/Logger.h"

ServerConfig::ServerConfig(httplib::SSLServer& server)
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
    std::cout << "Starting server on port 80..." << std::endl;

    // Attempt to start the server
    if (!svr.listen("138.197.69.84", 8080)) {
        std::cerr << "Error: Unable to start the server. Is the port already in use?" << std::endl;
    } else {
        std::cout << "Server started successfully." << std::endl;
    }
}
