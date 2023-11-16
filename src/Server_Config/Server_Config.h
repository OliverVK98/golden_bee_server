//
// Created by oliver on 10/25/23.
//

#ifndef UNTITLED_SERVER_CONFIG_H
#define UNTITLED_SERVER_CONFIG_H

#include "../../lib/cpp-httplib/httplib.h"
#include "../Router/Router.h"
#include "../Router/routes/Items_Routes.h"
#include "../Router/routes/Collections_Routes.h"
#include "../Router/routes/Users_Routes.h"

class ServerConfig {
public:
    explicit ServerConfig(httplib::Server& server);
    void listen();
private:
    httplib::Server& svr;
    Router router;
    ItemsRoutes itemsRoutes;
    CollectionsRoutes collectionsRoutes;
    UsersRoutes usersRoutes;
};

#endif //UNTITLED_SERVER_CONFIG_H