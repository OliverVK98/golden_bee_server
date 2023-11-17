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
        JSON_item[headers[3]] = item->description;
        JSON_item[headers[4]] = item->collections;

        json_array.push_back(JSON_item);
    }


    return json_array;
}

template<>
nlohmann::json convert_to_JSON<Collection>(const std::vector<std::string>& headers, const std::vector<std::unique_ptr<Collection>>& collection_data) {
    nlohmann::json json_array;

    for (const auto& collection_ptr : collection_data) {
        nlohmann::json json_collection;

        json_collection[headers[0]] = collection_ptr->id;
        json_collection[headers[1]] = collection_ptr->name;

        json_array.push_back(json_collection);
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
        json_user[headers[2]] = user_ptr->password;

        json_array.push_back(json_user);
    }

    return json_array;
}

//nlohmann::json convert_to_JSON(const std::vector<std::string>& headers, const std::vector<std::unique_ptr<BaseEntity>>& item_data) {
//    nlohmann::json jsonDataArray;
//
//    for (const auto& item_ptr : item_data) {
//        if(auto item = dynamic_cast<Item*>(item_ptr.get())) {
//            nlohmann::json JSON_object;
//            JSON_object[headers[0]] = item->id;
//            JSON_object[headers[1]] = item->name;
//            JSON_object[headers[2]] = item->price;
//            JSON_object[headers[3]] = item->description;
//            JSON_object[headers[4]] = item->collections;
//            jsonDataArray.push_back(JSON_object);
//        }
//        else if(auto collection = dynamic_cast<Collection*>(item_ptr.get())) {
//            nlohmann::json JSON_object;
//            JSON_object[headers[0]] = collection->id;
//            JSON_object[headers[1]] = collection->name;
//            jsonDataArray.push_back(JSON_object);
//        }
//        else if(auto collection = dynamic_cast<User*>(item_ptr.get())) {
//            nlohmann::json JSON_object;
//            JSON_object[headers[0]] = collection->id;
//            JSON_object[headers[1]] = collection->email;
//            JSON_object[headers[2]] = collection->password;
//            jsonDataArray.push_back(JSON_object);
//        }
//        else {
//            throw std::runtime_error("Incorrect payload");
//        }
//    }
//
//    return jsonDataArray;
//}
