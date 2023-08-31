//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <asio.hpp>

using asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server
{
public:
    udp_server(asio::io_context &io_context)
        : socket_(io_context, udp::endpoint(udp::v4(), 13))
    {
        start_receive();
    }

private:
    void start_receive()
    {
        std::cout << "start_receive" << std::endl;
        // asio::yield_context yield;
        socket_.async_receive_from(
            asio::buffer(recv_buffer_), remote_endpoint_,
            boost::bind(&udp_server::handle_receive, this,
                        ignored_error,
                        recvSize));
        std::cout << "start_receive done" << std::endl;
    }

    void handle_receive(const asio::error_code &error,
                        std::size_t /*bytes_transferred*/)
    {
        std::cout << "handle_receive" << std::endl;

        if (!error)
        {
            boost::shared_ptr<std::string> message(
                new std::string(make_daytime_string()));

            std::future<std::size_t> my_future2 = socket_.async_send_to(asio::buffer(*message), remote_endpoint_, asio::use_future);

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
                     const asio::error_code & /*error*/,
                     std::size_t /*bytes_transferred*/)
    {
        std::cout << "handle_send" << std::endl;
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
    int recvSize = recv_buffer_.size();
    boost::system::error_code ignored_error;
};

void print(const asio::error_code & /*e*/)
{
    std::cout << "Hello, world!" << std::endl;
}

int main()
{
    try
    {
        asio::io_context io_context;
        udp_server server(io_context);
        io_context.run();
        asio::steady_timer t(io_context, asio::chrono::seconds(5));
        t.wait();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}