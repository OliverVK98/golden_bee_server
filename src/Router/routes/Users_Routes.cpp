//
// Created by oliver on 10/31/23.
//

#include "Users_Routes.h"
#include "../util/convert_to_JSON.h"

std::string UsersRoutes::users_path = "/users";

bool isValidEmail(const std::string& email) {
    std::regex email_regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, email_regex);
}

void UsersRoutes::setup() {
    auto headers = data_source.headers;

    router.Post(users_path+"/add", [this, headers](const httplib::Request& req, httplib::Response& res) {
        try {
            auto json_body = nlohmann::json::parse(req.body);
            std::string email = json_body["email"];

            if(email.empty()) {
                send_response_with_HTTP_code(400, "Email cannot be empty", res);
                return;
            }
            if (!isValidEmail(email)) {
                send_response_with_HTTP_code(400, "Invalid email format", res);
                return;
            }

            auto existingUser = data_source.read_by_unique_email(email);

            if(!existingUser.empty() && existingUser[0]) {
                send_response_with_HTTP_code(400, "This email already exists", res);
            } else data_source.write(email);

        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content("Invalid request body", "text/plain");
        }
    });

    router.Options(users_path + "/add", [](const httplib::Request&, httplib::Response& res) {
        res.status = 204; // OPTIONS BEFORE POST
    });
}
