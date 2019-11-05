#include <iostream>
#include <boost/asio.hpp>
#include "server.h"
int main(int argc, const char** argv) {
    boost::asio::io_context context;

    server server(context);

    context.run();
    return 0;
}