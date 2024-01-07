//
// Created by oliver on 10/29/23.
//

#ifndef UNTITLED_ITEMS_ROUTES_H
#define UNTITLED_ITEMS_ROUTES_H

#include "httplib.h"
#include "../Router.h"
#include "../../CSV_Data_Controller/CSV_Data_Controller.h"

class ItemsRoutes {
public:
    void setup();
    explicit ItemsRoutes(Router& rtr): router(rtr), data_source(filename) {};

private:
    std::string filename = "items.csv";
    Items_CSV_Data_Controller data_source;
    Router& router;
    static std::string items_path;
    static std::unordered_map<std::string, int> collection_name_to_id_map;
};

#endif //UNTITLED_ITEMS_ROUTES_H
