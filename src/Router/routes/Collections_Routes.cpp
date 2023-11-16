//
// Created by oliver on 10/30/23.
//

#include "Collections_Routes.h"
#include "string"
#include "../util/convert_to_JSON.h"
#include "../../HTTP_Status_Code/HTTP_Status_Code.h"

std::string CollectionsRoutes::collections_path = "/collections";

void CollectionsRoutes::setup() {
    auto headers = data_source.headers;

    router.Get(collections_path, [this, headers](const httplib::Request& req, httplib::Response& res) {

        auto collections_data = data_source.read();

        auto jsonData = convert_to_JSON(headers, collections_data);

        res.set_content(jsonData.dump(), "application/json");
    });

    router.Get(collections_path + "/([0-9]+)", [this, headers](const httplib::Request& req, httplib::Response& res) {
        int param = std::stoi(req.matches[1]);

        auto collection_data = data_source.read_by_unique_id(param);

        if (!collection_data.empty()) {
            auto jsonData = convert_to_JSON(data_source.headers, collection_data);
            res.set_content(jsonData.dump(), "application/json");
        } else {
            HTTPStatusCode error(404, res);
        }
    });
}
