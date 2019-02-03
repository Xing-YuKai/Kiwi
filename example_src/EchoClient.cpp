//
// Created by kiwi on 19-1-19.
//

#include "../Kiwi/Network/TcpClient.h"
#include "../Kiwi/Network/TcpConnection.h"
#include "../Kiwi/Base/InetAddress.h"
#include "../Kiwi/Reactor/EventLoop.h"

void connection_handler(const Kiwi::Type::TcpConnectionPtr &conn_ptr)
{
}

void message_handler(const Kiwi::Type::TcpConnectionPtr &conn_ptr,
					 const Kiwi::Type::BufferPtr &buffer,
					 const Kiwi::TimeRange &receive)
{
	std::string data;
	data = buffer->retrieve(buffer->get_readable_bytes());
	std::cout<<data<<std::endl;

	std::cin>>data;
	conn_ptr->send(data);
}

int main()
{
	Kiwi::InetAddress server_address;
	Kiwi::EventLoop base_loop;
	server_address.set_address("127.0.0.1");
	server_address.set_port(23333);

	Kiwi::TcpClient client(&base_loop,server_address,1);
	client.set_message_handler(message_handler);
	client.set_connection_handler(connection_handler);
	client.connect();
	base_loop.loop();
}