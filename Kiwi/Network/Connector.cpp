//
// Created by kiwi on 19-1-19.
//

#include "Connector.h"

using namespace Kiwi;
using namespace Kiwi::Type;

Connector::Connector(EventLoop *loop, const InetAddress &server_adderss) :
		_owner_event_loop_(loop),
		_server_address_(server_adderss),
		_connected_(false) {}

bool Connector::connect()
{
	Socket socket = Socket::nonblocking_socket();
	bool flag = socket.connect(_server_address_) && !socket.is_self_connect();
	if (flag)
	{
		InetAddress null_address;
		_new_connection_handler_(socket,null_address);
		return flag;
	} else
	{
		socket.close();
		return flag;
	}
}

void Connector::disconnect()
{

}
