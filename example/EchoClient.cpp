//
// Created by kiwi on 19-1-19.
//

#include "../Kiwi/Network/TcpClient.h"
#include "../Kiwi/Network/TcpConnection.h"
#include "../Kiwi/Base/InetAddress.h"
#include "../Kiwi/Reactor/EventLoop.h"
#include <stdlib.h>

void connection_handler(const Kiwi::Type::TcpConnectionPtr &conn_ptr)
{
}

void message_handler(const Kiwi::Type::TcpConnectionPtr &conn_ptr,
					 const Kiwi::Type::BufferPtr &buffer,
					 const Kiwi::TimeRange &receive)
{
	std::string data_receive;
	std::string data_send;
	data_receive = buffer->retrieve(buffer->get_readable_bytes());
	std::cout << data_receive << std::endl;
	std::cin >> data_send;
	conn_ptr->send(data_send);
}

int main(int argc, char **argv)
{
    u_int16_t port = 8888;
    Kiwi::InetAddress server_address;
    std::string ip("127.0.0.1");

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-p") && i + 1 < argc)
        {
            long port_num = strtol(argv[++i], nullptr, 10);
            if (port_num != 0)
                port = port_num;
        }
        if (!strcmp(argv[i], "-h") && i + 1 < argc)
        {
            ip = std::string(argv[++i]);
        }
    }
    Kiwi::EventLoop base_loop;
    server_address.set_address(ip);
    server_address.set_port(port);

	Kiwi::TcpClient client(&base_loop, server_address, 1);
	client.set_message_handler(message_handler);
	client.set_connection_handler(connection_handler);
	client.connect();
	base_loop.loop();
	return 0;
}