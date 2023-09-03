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
// #include <memory>
// #include <new>
#include "asio-1.28.0/include/asio.hpp"

// using asio::ip::udp;

std::string
make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server
{
public:
    udp_server()
        : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 1024))
    {
        // this->io_context = io_context;
        io_context.run();
        start_receive([this](const asio::error_code &ec, size_t len) {});
    }

private:
    using state_ptr = std::shared_ptr<udp_server>;
    // start waiting for client to send
    void start_receive(std::function<void(const asio::error_code &ec, size_t len)> handler)
    {
        // other option to pass instead of asio::use_future
        //  asio::yield_context yield;

        // if implements this instead must call handle_receive separately, can do for send as well
        // std::future<std::size_t> my_future = socket_.async_receive_from(asio::buffer(recv_buffer_), remote_endpoint_, asio::use_future);
        // handle_receive(iError1, recvSize);

        /*         socket_.async_receive_from(
                    asio::buffer(recBuff), remote_endpoint_,
                    handle_receive(iError1, recSize)); */

        socket_.async_receive_from(asio::buffer(recBuff), remote_endpoint_, handler);
        std::cout << "hi1" << std::endl;

        asio::steady_timer t(io_context, asio::chrono::seconds(20));
        t.wait();

        handle_receive(iError1, recSize);
    }

    // to do after recieved from client, send info back
    void handle_receive(const asio::error_code &error,
                        std::size_t
                            bytes_transferred)
    {
        std::cout << "handle_receive" << std::endl;

        if (!error)
        {
            day = make_daytime_string();
            // std::cout << day << std::endl;
            sendSize = day.size();
            sendStar = day.c_str();
            // boost::shared_ptr<std::string> message(new std::string(day));

            /*             socket_.async_send_to(asio::buffer(sendBuff), remote_endpoint_,
                                              boost::bind(&udp_server::handle_send, this, message,
                                                          iError2,
                                                          sizeDay)); */

            std::future<std::size_t> my_future2 = socket_.async_send_to(
                asio::buffer(day),
                remote_endpoint_,
                asio::use_future);

            // my_future2.wait();

            handle_send(day, iError2, sendSize);

            // start listening for another client send
            state_ptr s2;
            start_receive([this](const asio::error_code &ec, size_t len) {});
        }
    }

    // what to do with info recieved?
    void handle_send(std::string
                         message,
                     const asio::error_code &
                         error,
                     std::size_t
                         bytes_transferred)
    {
    }

    asio::io_context io_context;
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint remote_endpoint_;
    // boost::array<char, 1> recv_buffer_;
    std::size_t recSize = 1, sendSize = 128;
    char recBuff[1], sendBuff[128];
    const char *sendStar;
    std::string day;
    asio::error_code iError1, iError2;
};

int main()
{
    try
    {
        // asio::io_context io_context;
        udp_server server;
        // io_context.run();
        // asio::steady_timer t(io_context, asio::chrono::seconds(5));

        //  t.wait();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}