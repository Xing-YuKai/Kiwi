//
// Created by kiwi on 19-2-1.
//

#include "../Kiwi/Network/Acceptor.h"
#include "../Kiwi/Reactor/EventLoop.h"

void new_connection_handler(const Kiwi::Socket &socket, const Kiwi::InetAddress &peer_address)
{
	std::cout << "New connection : " << peer_address.get_address() << ":" << peer_address.get_port() << std::endl;
}

int main()
{
	Kiwi::EventLoop loop;
	Kiwi::InetAddress address;

	address.set_port(23333);
	address.set_address_any();

	Kiwi::Acceptor acceptor(&loop, address);

	acceptor.set_new_connection_handler(new_connection_handler);
	acceptor.listen();
	loop.loop();

	std::cout << std::endl << "destruct" << std::endl;
	return 0;
}
