#include <iostream>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../lib/cpp-httplib/httplib.h"
#include "Server_Config/Server_Config.h"
#include "Logger/Logger.h"

httplib::SSLServer srv("cert.pem", "key.pem");

int main()
{
    try {
        ServerConfig server(srv);
        server.listen();
    } catch (const std::runtime_error& e) {
        Logger logger;
        logger.log(std::string("Exception caught: ") + e.what());
    }
}
