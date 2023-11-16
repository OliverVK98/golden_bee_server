//
// Created by oliver on 10/30/23.
//

#ifndef UNTITLED_COLLECTIONS_ROUTES_H
#define UNTITLED_COLLECTIONS_ROUTES_H

#include "../Router.h"
#include "../../CSV_Data_Controller/CSV_Data_Controller.h"

class CollectionsRoutes {
public:
    explicit CollectionsRoutes(Router& rtr): router(rtr), data_source(filename) {};
    void setup();

private:
    std::string filename = "collections.csv";
    Router& router;
    Collections_CSV_Data_Controller data_source;
    static std::string collections_path;
};

#endif //UNTITLED_COLLECTIONS_ROUTES_H
