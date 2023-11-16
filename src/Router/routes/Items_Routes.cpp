//
// Created by oliver on 10/29/23.
//

#include "Items_Routes.h"
#include "../../HTTP_Status_Code/HTTP_Status_Code.h"
#include "../util/convert_to_JSON.h"

std::unordered_map<std::string, int> ItemsRoutes::collection_name_to_id_map = {
        {"necklaces", 1},
        {"rings", 2},
        {"bracelets", 3},
        {"earrings", 4},
        {"gift Cards", 5},
        {"bundles", 6},
};

std::string ItemsRoutes::items_path = "/items";

void ItemsRoutes::setup() {
    auto headers = data_source.headers;

    router.Get(items_path, [this, headers](const httplib::Request& req, httplib::Response& res) {
        std::vector<std::unique_ptr<Item>> item_data;

        if (req.has_param("collection")) {
            std::string collectionName = req.get_param_value("collection");
            for (auto& c: collectionName) c = tolower(c);
            item_data = data_source.read_by_collection_id(collection_name_to_id_map[collectionName]);
        } else {
            item_data = data_source.read();
        }

        auto jsonData = convert_to_JSON(headers, item_data);

        res.set_content(jsonData.dump(), "application/json");
    });

    router.Get(items_path + "/([0-9]+)", [this, headers](const httplib::Request& req, httplib::Response& res) {
        int param = std::stoi(req.matches[1]);

        auto item_data = data_source.read_by_unique_id(param);

        if (!item_data.empty()) {
            auto jsonData = convert_to_JSON(headers, item_data);
            res.set_content(jsonData.dump(), "application/json");
        } else {
            HTTPStatusCode error(404, res);
        }
    });

}