//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2023 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
// #include <boost/array.hpp>
// #include <boost/asio.hpp>
#define ASIO_STANDALONE
#include "asio-1.28.0/include/asio.hpp"
// #include "asio-1.28.0/include/asio/ts/socket.hpp"
// #include <asio.hpp>
// #include <asio/ts/buffer.hpp>

// using asio::ip::udp;

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client <host>" << std::endl;
            return 1;
        }

        asio::io_context io_context;

        asio::ip::udp::resolver resolver(io_context);
        asio::ip::udp::endpoint receiver_endpoint =
            *resolver.resolve(asio::ip::udp::v4(), argv[1], "1025").begin();

        asio::ip::udp::socket socket(io_context);
        socket.open(asio::ip::udp::v4());

        size_t bytes = socket.available();
        char data[1];
        // std::vector<char> vBuff(bytes);
        //  boost::array<char, 1> send_buf = {{0}};
        socket.send_to(asio::buffer(data), receiver_endpoint);

        // while (true)
        //{

        size_t bytes2 = socket.available();
        char data2[128];
        // std::vector<char, 128> vBuff2();
        //  boost::array<char, 128> recv_buf;
        asio::ip::udp::endpoint sender_endpoint =
            *resolver.resolve(asio::ip::udp::v4(), argv[1], "1024").begin();
        size_t len = socket.receive_from(
            asio::buffer(data2), sender_endpoint);

        std::cout.write(data2, len);
        //}
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}