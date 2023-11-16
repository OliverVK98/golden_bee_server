#include <iostream>
#include "../lib/cpp-httplib/httplib.h"
#include "./Logger/Logger.h"
#include "Server_Config/Server_Config.h"

httplib::Server svr;

int main(void)
{
    try {
        ServerConfig server(svr);
        server.listen();
    } catch (const std::runtime_error& e) {
        Logger logger;
        logger.log(std::string("Exception caught: ") + e.what());
    }
}
