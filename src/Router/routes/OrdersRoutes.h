//
// Created by oliver on 1/4/24.
//

#ifndef GOLDEN_BEE_SERVER_ORDERSROUTES_H
#define GOLDEN_BEE_SERVER_ORDERSROUTES_H

#include "../Router.h"
#include "../../../lib/json/single_include/nlohmann/json.hpp"
#include "../../CSV_Data_Controller/CSV_Data_Controller.h"

enum class AddressType {
    Shipping,
    Billing
};

class OrdersRoutes {
public:
    explicit OrdersRoutes(Router& rtr): router(rtr), data_source(filename) {};
    void setup();

private:
    std::string filename = "orders.csv";
    Orders_CSV_Data_Controller data_source;
    Router& router;
    static std::string orders_path;
    static Address createAddressFromJson(const nlohmann::json& json_body, AddressType addressType);
};

#endif //GOLDEN_BEE_SERVER_ORDERSROUTES_H
