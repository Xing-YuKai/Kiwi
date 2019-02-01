//
// Created by kiwi on 19-1-19.
//

#include "../Network/TcpServer.h"
#include "../Base/InetAddress.h"

int main()
{
	Kiwi::InetAddress listen_address;
	listen_address.set_address_any();
	listen_address.set_port(3333);
	Kiwi::TcpServer server(4,listen_address);
	return 0;
}