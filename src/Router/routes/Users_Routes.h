//
// Created by oliver on 10/31/23.
//

#ifndef UNTITLED_USERS_ROUTES_H
#define UNTITLED_USERS_ROUTES_H

#include "../Router.h"
#include "../../CSV_Data_Controller/CSV_Data_Controller.h"
#include "../../HTTP_Status_Code/HTTP_Status_Code.h"

class UsersRoutes {
public:
    explicit UsersRoutes(Router& rtr): router(rtr), data_source(filename) {};
    void setup();

private:
    std::string filename = "users.csv";
    Router& router;
    Users_CSV_Data_Controller data_source;
    static std::string users_path;
};

#endif //UNTITLED_USERS_ROUTES_H
