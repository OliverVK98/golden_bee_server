//
// Created by oliver on 10/31/23.
//

#include "Users_Routes.h"
#include "../util/convert_to_JSON.h"
#include "../../HTTP_Status_Code/HTTP_Status_Code.h"

std::string UsersRoutes::users_path = "/users";

void UsersRoutes::setup() {
    auto headers = data_source.headers;

    router.Get(users_path, [this, headers](const httplib::Request& req, httplib::Response& res) {
        auto user_data = data_source.read();
        auto jsonData = convert_to_JSON(headers, user_data);
        res.set_content(jsonData.dump(), "application/json");
    });

    router.Get(users_path + "/([0-9]+)", [this, headers](const httplib::Request& req, httplib::Response& res) {
        int param = std::stoi(req.matches[1]);

        auto user_data = data_source.read_by_unique_id(param);

        if (!user_data.empty()) {
            auto jsonData = convert_to_JSON(headers, user_data);
            res.set_content(jsonData.dump(), "application/json");
        } else {
            HTTPStatusCode error(404, res);
        }
    });

    router.Get(users_path+"/add", [this, headers](const httplib::Request& req, httplib::Response& res) {
        User test_user;
        test_user.password = "123";
        test_user.email = "Mike@test.com";
        data_source.write(test_user);
    });
}
