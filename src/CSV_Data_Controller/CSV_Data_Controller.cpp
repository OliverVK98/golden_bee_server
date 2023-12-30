//
// Created by oliver on 10/25/23.
//

#include <fstream>
#include <sstream>
#include "CSV_Data_Controller.h"
#include <algorithm>
#include <shared_mutex>

bool contains_id(const std::vector<int>& vec, int value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

std::string Items_CSV_Data_Controller::filename = "items.csv";
std::string Users_CSV_Data_Controller::filename = "users.csv";

template <typename EntityType>
std::vector<std::unique_ptr<EntityType>> CSV_Data_Controller<EntityType>::read_by_condition(const std::function<bool(const EntityType &)> &cond) {
    std::vector<std::unique_ptr<EntityType>> entities;

    std::ifstream file(this->getFilename());

    if (!file.is_open()) {
        throw std::runtime_error("Could not open CSV file.");
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        auto entity = parse_line(line);
        if (cond(*entity)) {
            entities.push_back(std::move(entity));
        }
    }
    file.close();
    return entities;
}

// Items_CSV_Data_Controller

std::vector<std::unique_ptr<Item>> Items_CSV_Data_Controller::read() {
    return read_by_condition([](const Item& item) { return true; });
}

std::vector<std::unique_ptr<Item>> Items_CSV_Data_Controller::read_by_unique_id(int id) {
    return read_by_condition([&](const Item& item) { return item.id == id; });
}

std::vector<std::unique_ptr<Item>> Items_CSV_Data_Controller::read_by_collection_id(int id) {
    return read_by_condition([&](const Item& item) { return contains_id(item.type, id); });
}

std::unique_ptr<Item> Items_CSV_Data_Controller::parse_line(const std::string &line) {
    std::stringstream ss(line);
    std::string value;
    // Item vars initializers
    int id;
    std::string name;
    double price;
    double discountedPrice;
    int rating;
    std::vector<std::string> imgUrl;
    std::vector<std::string> bundle;
    std::vector<AdditionalInfo> additional_info;
    std::vector<int> type;


    if (std::getline(ss, value, ',')) {
        id = std::stoi(value);
    }
    if (std::getline(ss, value, ',')) {
        name = value;
    }
    if (std::getline(ss, value, ',')) {
        price = std::stod(value);
    }
    if (std::getline(ss, value, ',')) {
        if(value.empty()) { discountedPrice = 0; }
        else {
            discountedPrice = std::stod(value);
        }
    }
    if (std::getline(ss, value, ',')) {
        if(value.empty()) { rating = 0; }
        else {
            rating = std::stoi(value);
        }
    }

    if (std::getline(ss, value, ',')) {
        std::istringstream urlArr(value);
        std::string singleUrl;

        while (std::getline(urlArr, singleUrl, '|')) {
            imgUrl.push_back(singleUrl);
        }
    }

    if (std::getline(ss, value, ',')) {
        std::istringstream url_arr(value);
        if (value.empty()) { bundle.emplace_back("NULL"); }
        else {
        std::string bundleItems;
        while (std::getline(url_arr, bundleItems, '|')) {
            bundle.push_back(bundleItems);
        }
        }
    }

    if (std::getline(ss, value, ',')) {

        if (!value.empty() && value.front() == '\"') {

            std::string restOfField;
            char ch;
            while (ss.get(ch)) {
                if (ch == '\"') {
                    if (ss.peek() == '\"') {
                        ss.get(ch);
                    } else {
                        break;
                    }
                } else {
                    restOfField += ch;
                }
            }
            value.erase(0, 1);
            value += restOfField;
            ss.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        }

        if (!value.empty()) {
            std::istringstream add_inf_arr(value);
            std::string add_inf_line;
            while (std::getline(add_inf_arr, add_inf_line, '|')) {
                std::istringstream add_inf_line_stream(add_inf_line);
                std::string add_inf_url;
                std::string add_inf_desc;

                if (std::getline(add_inf_line_stream, add_inf_url, '^') &&
                    std::getline(add_inf_line_stream, add_inf_desc)) {
                    additional_info.emplace_back(add_inf_url, add_inf_desc);
                }
            }
        } else {
            additional_info.emplace_back("NULL", "NULL");
        }
    }

    if (std::getline(ss, value, ',')) {
        std::istringstream type_arr(value);
        std::string type_item;

        while (std::getline(type_arr, type_item, '|')) {
            type.push_back(std::stoi(type_item));
        }
    }


    auto item = std::make_unique<Item>(id, name, price, discountedPrice, rating, imgUrl, bundle, additional_info, type);

    return item;
}

// Users_CSV_Data_Controller
int Users_CSV_Data_Controller::currentUserId = -1;

Users_CSV_Data_Controller::Users_CSV_Data_Controller(std::string &fname) : CSV_Data_Controller(fname) {
    std::ifstream file(this->getFilename());
    if (!file.is_open()) {
        throw std::runtime_error("Could not open CSV file.");
    }

    std::string line;
    std::string lastLine;
    std::getline(file, line);
    while (std::getline(file, line)) {
        lastLine = line;
    }

    if (!lastLine.empty()) {
        size_t pos = lastLine.find(',');
        if (pos != std::string::npos) {
            currentUserId = std::stoi(lastLine.substr(0, pos));
        }
    } else {
        currentUserId = 0;  // Default value if the file is empty
    }

    file.close();
}

std::vector<std::unique_ptr<User>> Users_CSV_Data_Controller::read() {
    std::shared_lock<std::shared_timed_mutex> lock(csv_mutex);
    return read_by_condition([](const User& user) { return true; });
}

std::vector<std::unique_ptr<User>> Users_CSV_Data_Controller::read_by_unique_id(int id) {
    std::shared_lock<std::shared_timed_mutex> lock(csv_mutex);
    return read_by_condition([&](const User& user) { return user.id == id; });
}

std::vector<std::unique_ptr<User>> Users_CSV_Data_Controller::read_by_unique_email(std::string email) {
    std::shared_lock<std::shared_timed_mutex> lock(csv_mutex);
    return read_by_condition([&](const User& user) { return user.email == email; });
}

std::unique_ptr<User> Users_CSV_Data_Controller::parse_line(const std::string &line) {
    std::stringstream ss(line);
    std::string value;
    std::string email;
    int id;

    if (std::getline(ss, value, ',')) {
        id = std::stoi(value);
    }
    if (std::getline(ss, value, ',')) {
        email = value;
    }

    auto user = std::make_unique<User>(id, email);

    return user;
}

void Users_CSV_Data_Controller::write(const std::string& email) {
    std::unique_lock<std::shared_timed_mutex> lock(csv_mutex);

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open CSV file for writing.");
    }

    ++currentUserId;

    file << currentUserId << "," << email  << std::endl;

    file.close();
}




