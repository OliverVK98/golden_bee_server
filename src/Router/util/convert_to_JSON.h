//
// Created by oliver on 10/31/23.
//

#ifndef UNTITLED_CONVERT_TO_JSON_H
#define UNTITLED_CONVERT_TO_JSON_H

#include "../../../lib/json/single_include/nlohmann/json.hpp"
#include "../../CSV_Data_Controller/CSV_Data_Controller.h"

template<typename T>
nlohmann::json convert_to_JSON(const std::vector<std::string>& headers, const std::vector<std::unique_ptr<T>>& item_data);

#endif //UNTITLED_CONVERT_TO_JSON_H
