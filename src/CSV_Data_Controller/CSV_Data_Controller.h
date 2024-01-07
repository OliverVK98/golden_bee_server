//
// Created by oliver on 10/25/23.
//

#ifndef UNTITLED_CSV_DATA_CONTROLLER_H
#define UNTITLED_CSV_DATA_CONTROLLER_H

#include <memory>
#include <functional>
#include "vector"
#include <shared_mutex>
#include <mutex>
#include <string>
#include <utility>
#include <fstream>

struct BaseEntity {
    explicit BaseEntity(int id) : id(id) {};
    int id;
    virtual ~BaseEntity() = default;
};

struct AdditionalInfo {
    AdditionalInfo(std::string url, std::string description)
            : url(std::move(url)), description(std::move(description)) {}

    std::string url;
    std::string description;
};

struct Item : public BaseEntity {
    Item(int id, std::string  name, double price, double discountedPrice, int rating,
         const std::vector<std::string>& imgUrl, const std::vector<std::string>& bundle,
         const std::vector<AdditionalInfo>& additionalInfo, const std::vector<int>& type)
            : BaseEntity(id),
              name(std::move(name)), price(price), discountedPrice(discountedPrice),
              rating(rating), imgUrl(imgUrl), bundle(bundle), additionalInfo(additionalInfo),
              type(type) {}

    std::string name;
    double price;
    double discountedPrice;
    int rating;
    std::vector<std::string> imgUrl;
    std::vector<std::string> bundle;
    std::vector<AdditionalInfo> additionalInfo;
    std::vector<int> type;
};

struct User : public BaseEntity {
    User(int id, std::string email) : BaseEntity(id), email(std::move(email)) {};
    std::string email;
};

struct Address {
    Address(std::string  addr, std::string  ct, std::string  st, std::string zip, std::string phone_num)
            : address(std::move(addr)), city(std::move(ct)), state(std::move(st)), zip_code(zip),
            phone(std::make_unique<std::string>(phone_num)) {}

    Address(std::string  addr, std::string  ct, std::string  st, std::string zip)
            : address(std::move(addr)), city(std::move(ct)), state(std::move(st)),
            zip_code(zip), phone(nullptr) {}

    std::string address;
    std::string city;
    std::string state;
    std::string zip_code;
    std::unique_ptr<std::string> phone;
};

struct Order : public BaseEntity {
public:
    Order(int id, std::string &email, std::string &fn, std::string &ln, std::string &order_info,
            std::unique_ptr<Address> con_ship_info, std::unique_ptr<Address> bill_info) :
            BaseEntity(id), email(email), first_name(fn), last_name(ln), order_info(order_info),
            contact_shipping_info(std::move(con_ship_info)), billing_info(std::move(bill_info)) {}

    Order(int id, std::string &email, std::string &fn, std::string &ln, std::string &order_info,
            std::unique_ptr<Address> con_ship_info) : BaseEntity(id), email(email), first_name(fn), last_name(ln),
            order_info(order_info), contact_shipping_info(std::move(con_ship_info)), billing_info(nullptr) {}

    std::string first_name;
    std::string last_name;
    std::string email;
    std::string order_info;
    std::unique_ptr<Address> contact_shipping_info;
    std::unique_ptr<Address> billing_info;
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

        std::ifstream csv_file(fname);

        if (!csv_file.is_open()) {
            throw std::runtime_error("Could not open CSV file.");
        }

        std::string line;
        if (std::getline(csv_file, line) && !line.empty()) {
            std::stringstream headerStream(line);
            std::string headerItem;
            while (std::getline(headerStream, headerItem, ',')) {
                headers.push_back(headerItem);
            }
        }
        csv_file.close();
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
    std::vector<std::unique_ptr<Item>> get_random_items(int quant);
};

class Users_CSV_Data_Controller : public CSV_Data_Controller<User> {
private:
    std::shared_timed_mutex csv_mutex;
    std::unique_ptr<User> parse_line(const std::string& line) override;
    static int currentUserId;
    static std::string filename;
    const std::string& getFilename() const override { return filename; }

public:
    explicit Users_CSV_Data_Controller(std::string& fname);
    std::vector<std::unique_ptr<User>> read() override;
    std::vector<std::unique_ptr<User>> read_by_unique_id(int id) override;
    std::vector<std::unique_ptr<User>> read_by_unique_email(std::string email);
    void write(const std::string& email);
};

class Orders_CSV_Data_Controller : public CSV_Data_Controller<Order> {
private:
    std::shared_timed_mutex csv_mutex;
    static int currentOrderId;
    static std::string filename;
    const std::string& getFilename() const override { return filename; }
    std::unique_ptr<Order> parse_line(const std::string& line) override;
    std::vector<std::unique_ptr<Order>> read() override;
    std::vector<std::unique_ptr<Order>> read_by_unique_id(int id) override;

public:
    explicit Orders_CSV_Data_Controller(std::string& fname);
    void write(const Order &order, bool &send_offers, bool &shipping_billing_is_same);
};

#endif //UNTITLED_CSV_DATA_CONTROLLER_H
