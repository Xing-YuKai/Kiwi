//
// Created by kiwi on 19-1-19.
//

#include "../Kiwi/Network/TcpServer.h"
#include "../Kiwi/Network/TcpConnection.h"
#include "../Kiwi/Base/InetAddress.h"
#include "../Kiwi/Reactor/EventLoop.h"

void connection_handler(const Kiwi::Type::TcpConnectionPtr &conn_ptr)
{
    conn_ptr->send("EchoServer");
}

void message_handler(const Kiwi::Type::TcpConnectionPtr &conn_ptr,
                     const Kiwi::Type::BufferPtr &buffer,
                     const Kiwi::TimeRange &receive)
{
    std::string data;
    data = buffer->retrieve(buffer->get_readable_bytes());
    conn_ptr->send(data);
}

int main(int argc, char **argv)
{
    u_int16_t port = 8888;
    Kiwi::InetAddress listen_address;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-p") && i + 1 < argc)
        {
            long port_num = strtol(argv[++i], nullptr, 10);
            if (port_num != 0)
                port = port_num;
        }
    }
    Kiwi::EventLoop base_loop;
    listen_address.set_address_any();
    listen_address.set_port(port);

    Kiwi::TcpServer server(&base_loop, 4, listen_address);
    server.set_message_handler(message_handler);
    server.set_connection_handler(connection_handler);
    server.listen();
    base_loop.loop();
}
