//
// Created by kiwi on 19-1-19.
//

#include "Acceptor.h"

using namespace Kiwi;
using namespace Kiwi::Type;

Acceptor::Acceptor(EventLoop *loop, const InetAddress &address) :
		_owner_event_loop_(loop),
		_acceptor_socket_(Socket::nonblocking_socket()),
		_acceptor_channel_(loop, _acceptor_socket_.get_fd()),
		_listening_(false) {}

void Acceptor::set_new_connection_handler(const Type::NewConnectionHandler &handler)
{
	_new_connection_handler_ = handler;
}

void Acceptor::listen()
{

}

Acceptor::~Acceptor()
{

}

void Acceptor::acceptor_read_handler()
{
	InetAddress peer_address;
	Socket conn = _acceptor_socket_.accept(peer_address);
	if(_new_connection_handler_)
		_new_connection_handler_();
	
}
