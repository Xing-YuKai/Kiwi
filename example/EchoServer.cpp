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

int main()
{
	Kiwi::InetAddress listen_address;
	Kiwi::EventLoop base_loop;
	listen_address.set_address_any();
	listen_address.set_port(23333);

	Kiwi::TcpServer server(&base_loop, 4, listen_address);
	server.set_message_handler(message_handler);
	server.set_connection_handler(connection_handler);
	server.listen();
    base_loop.loop();
}
