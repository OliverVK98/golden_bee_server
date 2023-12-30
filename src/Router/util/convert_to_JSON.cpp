//
// Created by oliver on 10/31/23.
//

#include "convert_to_JSON.h"

template<>
nlohmann::json convert_to_JSON<Item>(const std::vector<std::string>& headers, const std::vector<std::unique_ptr<Item>>& item_data) {
    nlohmann::json json_array;

    for (auto &item : item_data) {
        nlohmann::json JSON_item;


        JSON_item[headers[0]] = item->id;
        JSON_item[headers[1]] = item->name;
        JSON_item[headers[2]] = item->price;

        if (item->discountedPrice == 0) { JSON_item[headers[3]] = nullptr; }
        else { JSON_item[headers[3]] = item->discountedPrice; }

        if (item->rating == 0) { JSON_item[headers[4]] = nullptr; }
        else { JSON_item[headers[4]] = item->rating; }

        JSON_item[headers[5]] = item->imgUrl;

        if (item->bundle[0] == "NULL") { JSON_item[headers[6]] = nullptr; }
        else { JSON_item[headers[6]] = item->bundle; }

        if (item->additionalInfo[0].url == "NULL"  ) { JSON_item[headers[7]] = nullptr; }
        else {
            nlohmann::json additionalInfo_json;
            for (const auto& info : item->additionalInfo) {
                nlohmann::json info_json;
                info_json["url"] = info.url;
                info_json["description"] = info.description;
                additionalInfo_json.push_back(info_json);
            }
            JSON_item[headers[7]] = additionalInfo_json;
        }

        JSON_item[headers[8]] = item->type;

        json_array.push_back(JSON_item);
    }


    return json_array;
}

template<>
nlohmann::json convert_to_JSON<User>(const std::vector<std::string>& headers, const std::vector<std::unique_ptr<User>>& user_data) {
    nlohmann::json json_array;

    for (const auto& user_ptr : user_data) {
        nlohmann::json json_user;

        json_user[headers[0]] = user_ptr->id;
        json_user[headers[1]] = user_ptr->email;

        json_array.push_back(json_user);
    }

    return json_array;
}