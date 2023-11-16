`cmake_minimum_required(VERSION 3.26)
project(golden_bee_server)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/nlohmann)
include_directories(${CMAKE_SOURCE_DIR}/lib/cpp-httplib)

add_executable(golden_bee_server
        src/main.cpp
        src/Server_Config/Server_Config.cpp
        src/CSV_Data_Controller/CSV_Data_Controller.cpp
        src/HTTP_Status_Code/HTTP_Status_Code.cpp
        src/Router/Router.cpp
        src/Router/routes/Items_Routes.cpp
        src/Router/routes/Collections_Routes.cpp
        src/Router/routes/Users_Routes.cpp
        src/Router/util/convert_to_JSON.cpp
)

target_link_libraries(golden_bee_server)
