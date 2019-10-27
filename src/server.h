#ifndef KEMTER_SERVER_H
#define KEMTER_SERVER_H
#include <string>
#include <boost/noncopyable.hpp>

class server: private boost::noncopyable
{
public:
    explicit server(const std::string& address, const std::string& port, std::size_t thread_pool_size);
    ~server();
    void run();
private:
    std::size_t thread_pool_size_;
};

#endif // !KEMTER_SERVER_H