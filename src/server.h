#ifndef KEMTER_SERVER_H
#define KEMTER_SERVER_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <string>

using namespace boost::asio::ip;

class connection
    : public boost::enable_shared_from_this<connection>
{
public:
    typedef boost::shared_ptr<connection> pointer;
    static pointer create(boost::asio::io_context& io_context) {
        return pointer(new connection(io_context));
    }

    tcp::socket& socket() {
        return socket_;
    }

    void start() {
        boost::asio::async_read(
            socket_,
            boost::asio::buffer(buffer_),
            boost::bind(&connection::handle_read, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

        boost::asio::async_write(
            socket_,
            boost::asio::buffer(message_),
            boost::bind(&connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
private:
    connection(boost::asio::io_context& io_context)
        : socket_(io_context) { }
    void handle_write(const boost::system::error_code&, std::size_t bytes_transferred) {
        
    }
    void handle_read(const boost::system::error_code&, std::size_t bytes_transferred) {
        std::cout << buffer_.data();
    }
    tcp::socket socket_;
    boost::array<char, 1024> buffer_;
    const std::string message_ = "Hello Kemter!";
};

class server
{
public:
    explicit server(boost::asio::io_context& context, std::size_t port = 9000) 
        : io_context_(context), 
          acceptor_(context, tcp::endpoint(tcp::v4(), port))
        { 
            accept();
        }
private:
    void accept() {
        connection::pointer new_connection = 
            connection::create(io_context_);

        acceptor_.async_accept(new_connection->socket(), 
            boost::bind(&server::accept_handler, this, new_connection,
                boost::asio::placeholders::error));
    }

    void accept_handler(connection::pointer new_connection,
        const boost::system::error_code& error) {
        if (!error)
        {
            new_connection->start();
        }

        accept();
    }
    
    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
};

#endif