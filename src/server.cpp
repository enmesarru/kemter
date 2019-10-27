#include "server.h"

server::server(const std::string& address, const std::string& port, std::size_t thread_pool_size)
    : thread_pool_size_(thread_pool_size)
{

};

server::~server()
{
};

void server::run()
{
};