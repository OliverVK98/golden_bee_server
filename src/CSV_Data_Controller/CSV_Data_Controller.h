//
// Created by oliver on 10/25/23.
//

#ifndef UNTITLED_CSV_DATA_CONTROLLER_H
#define UNTITLED_CSV_DATA_CONTROLLER_H

#include <iostream>
#include <memory>
#include <functional>
#include "vector"
#include "../Logger/Logger.h"
#include <shared_mutex>
#include <mutex>
#include <fstream>
#include <string>

struct BaseEntity {
    BaseEntity() : id(0) {};
    int id;
    virtual ~BaseEntity() = default;
};

struct Item : public BaseEntity {
    Item() : BaseEntity(), price(0.0) {}
    std::string name;
    double price;
    std::string description;
    std::vector<int> collections;
};

struct Collection : public BaseEntity {
    Collection() : BaseEntity() {};
    std::string name;
};

struct User : public BaseEntity {
    User() : BaseEntity() {};
    User(std::string& email, std::string& password) : BaseEntity(), email(email), password(password) {};
    std::string email;
    std::string password;
};

template <typename EntityType>
class CSV_Data_Controller {
public:
    std::vector<std::string> headers;

protected:
    std::vector<std::unique_ptr<EntityType>> csv_cache;
    virtual std::unique_ptr<EntityType> parse_line(const std::string& line) =0;
    std::vector<std::unique_ptr<EntityType>> read_by_condition(const std::function<bool(const EntityType &)> &cond);
    virtual const std::string& getFilename() const = 0;
    virtual std::vector<std::unique_ptr<EntityType>> read() =0;
    virtual std::vector<std::unique_ptr<EntityType>> read_by_unique_id(int id) =0;
    virtual ~CSV_Data_Controller() = default;

    explicit CSV_Data_Controller(std::string& fname) {

        std::ifstream file(fname);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open CSV file.");
        }

        std::string line;
        if (std::getline(file, line) && !line.empty()) {
            std::stringstream headerStream(line);
            std::string headerItem;
            while (std::getline(headerStream, headerItem, ',')) {
                headers.push_back(headerItem);
            }
        }
        file.close();
    }
};

class Items_CSV_Data_Controller : public CSV_Data_Controller<Item> {
private:
    std::unique_ptr<Item> parse_line(const std::string& line) override;
    static std::string filename;
    const std::string& getFilename() const override { return filename; }

public:
    explicit Items_CSV_Data_Controller(std::string& fname) : CSV_Data_Controller<Item>(fname) {};
    std::vector<std::unique_ptr<Item>> read() override;
    std::vector<std::unique_ptr<Item>> read_by_unique_id(int id) override;
    std::vector<std::unique_ptr<Item>> read_by_collection_id(int id);
};

class Collections_CSV_Data_Controller : public CSV_Data_Controller<Collection> {
private:
    std::unique_ptr<Collection> parse_line(const std::string& line) override;
    static std::string filename;
    const std::string& getFilename() const override { return filename; }

public:
    explicit Collections_CSV_Data_Controller(std::string& fname) : CSV_Data_Controller<Collection>(fname) {};
    std::vector<std::unique_ptr<Collection>> read() override;
    std::vector<std::unique_ptr<Collection>> read_by_unique_id(int id) override;
};

class Users_CSV_Data_Controller : public CSV_Data_Controller<User> {
private:
    std::shared_timed_mutex csv_mutex;
    std::unique_ptr<User> parse_line(const std::string& line) override;
    static int currentUserId;
    static std::string filename;
    const std::string& getFilename() const override { return filename; }

public:
    explicit Users_CSV_Data_Controller(std::string& fname) : CSV_Data_Controller<User>(fname) {};
    std::vector<std::unique_ptr<User>> read() override;
    std::vector<std::unique_ptr<User>> read_by_unique_id(int id) override;
    std::vector<std::unique_ptr<User>> read_by_unique_email(std::string email);
    void write(User& user);
};

#endif //UNTITLED_CSV_DATA_CONTROLLER_H
