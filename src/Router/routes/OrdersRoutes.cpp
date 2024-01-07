//
// Created by oliver on 1/4/24.
//

#include "OrdersRoutes.h"
#include "../../HTTP_Status_Code/HTTP_Status_Code.h"

std::string OrdersRoutes::orders_path = "/orders";

Address OrdersRoutes::createAddressFromJson(const nlohmann::json& json_body, AddressType addressType) {
    std::string prefix = (addressType == AddressType::Billing) ? "billing" : "shipping";

    std::string addressKey = prefix + "Address";
    std::string cityKey = prefix + "City";
    std::string stateKey = prefix + "State";
    std::string zipCodeKey = prefix + "ZipCode";
    std::string phoneKey = prefix + "Phone";

    if (json_body.contains(phoneKey) && !json_body.at(phoneKey).is_null()) {
        return Address {
                json_body.at(addressKey).get<std::string>(), json_body.at(cityKey).get<std::string>(),
                json_body.at(stateKey).get<std::string>(), json_body.at(zipCodeKey).get<std::string>(),
                json_body.at(phoneKey).get<std::string>()
        };
    } else {
        return Address {
                json_body.at(addressKey).get<std::string>(), json_body.at(cityKey).get<std::string>(),
                json_body.at(stateKey).get<std::string>(), json_body.at(zipCodeKey).get<std::string>()
        };
    }
}

void OrdersRoutes::setup() {
    auto headers = data_source.headers;

    router.Post(orders_path, [this, headers](const httplib::Request& req, httplib::Response& res) {
        try {
            auto json_body = nlohmann::json::parse(req.body);
            std::string email = json_body["email"];
            std::string first_name = json_body["firstName"];
            std::string last_name = json_body["lastName"];
            std::string order_info = json_body["orderData"];
            bool send_offers = json_body["sendOffers"];
            auto contact_shipping_info = std::make_unique<Address>(createAddressFromJson(json_body.at("shippingAddress"), AddressType::Shipping));
            bool is_shipping_billing_same = json_body["shippingBillingIsSame"];

            if(is_shipping_billing_same) {
                Order order {0, email, first_name, last_name, order_info, std::move(contact_shipping_info)};
                data_source.write(order, send_offers, is_shipping_billing_same);
            } else {
                auto billing_info = std::make_unique<Address>(createAddressFromJson(json_body.at("billingAddress"), AddressType::Billing));
                Order order {0, email, first_name, last_name, order_info, std::move(contact_shipping_info), std::move(billing_info)};
                data_source.write(order, send_offers, is_shipping_billing_same);
            }

            res.status = 200;

        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content("Invalid request body", "text/plain");
        }
    });

    router.Options(orders_path , [](const httplib::Request&, httplib::Response& res) {
        res.status = 204; // OPTIONS BEFORE POST
    });
}