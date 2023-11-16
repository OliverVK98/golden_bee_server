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
std::string Collections_CSV_Data_Controller::filename = "collections.csv";

template <typename EntityType>
std::vector<std::unique_ptr<EntityType>> CSV_Data_Controller<EntityType>::read_by_condition(const std::function<bool(const EntityType &)> &cond) {
    std::vector<std::unique_ptr<EntityType>> entities;

    Logger console;
    console.log("123");
    console.log(this->getFilename());

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
    return read_by_condition([&](const Item& item) { return contains_id(item.collections, id); });
}

std::unique_ptr<Item> Items_CSV_Data_Controller::parse_line(const std::string &line) {
    std::stringstream ss(line);
    std::string value;
    auto item = std::make_unique<Item>();

    if (std::getline(ss, value, ',')) {
        item->id = std::stoi(value);
    }
    if (std::getline(ss, value, ',')) {
        item->name = value;
    }
    if (std::getline(ss, value, ',')) {
        item->price = std::stod(value);
    }
    if (std::getline(ss, value, ',')) {
        item->description = value;
    }
    std::string collections_str;
    std::getline(ss, collections_str, '\0');
    std::stringstream collections_ss(collections_str);
    std::string collection;

    while (std::getline(collections_ss, collection, ',')) {
        collection.erase(std::remove(collection.begin(), collection.end(), '\"'), collection.end());
        item->collections.push_back(std::stoi(collection));
    }
    return item;
}

// Collections_CSV_Data_Controller

std::unique_ptr<Collection> Collections_CSV_Data_Controller::parse_line(const std::string &line) {
    std::stringstream ss(line);
    std::string value;
    auto collection = std::make_unique<Collection>();

    if (std::getline(ss, value, ',')) {
        collection->id = std::stoi(value);
    }
    if (std::getline(ss, value, ',')) {
        collection->name = value;
    }

    return collection;
}

std::vector<std::unique_ptr<Collection>> Collections_CSV_Data_Controller::read() {
    return read_by_condition([](const Collection& collection) { return true; });
}

std::vector<std::unique_ptr<Collection>> Collections_CSV_Data_Controller::read_by_unique_id(int id) {
    return read_by_condition([&](const Collection& collection) { return collection.id == id; });
}

// Users_CSV_Data_Controller
int Users_CSV_Data_Controller::currentUserId = 1;

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
    auto user = std::make_unique<User>();

    if (std::getline(ss, value, ',')) {
        user->id = std::stoi(value);
    }
    if (std::getline(ss, value, ',')) {
        user->email = value;
    }
    if (std::getline(ss, value, ',')) {
        user->password = value;
    }

    return user;
}

void Users_CSV_Data_Controller::write(User &user) {
    std::unique_lock<std::shared_timed_mutex> lock(csv_mutex);

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open CSV file for writing.");
    }

    ++currentUserId;

    file << currentUserId << "," << user.email << "," << user.password << std::endl;

    file.close();
}


