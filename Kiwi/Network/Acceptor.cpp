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
		_listening_(false)
{
	_acceptor_socket_.set_reuse_address(true);
	_acceptor_socket_.set_reuse_port(true);
	_acceptor_socket_.bind(address);
	_acceptor_channel_.set_read_handler(std::bind(&Acceptor::acceptor_read_handler, this));
}

void Acceptor::set_new_connection_handler(const Type::NewConnectionHandler &handler)
{
	_new_connection_handler_ = handler;
}

void Acceptor::listen()
{
	if (!_listening_)
	{
		_listening_ = true;
		_acceptor_channel_.enable_reading();
		_acceptor_channel_.update();
		_acceptor_socket_.listen();
	}
}

Acceptor::~Acceptor()
{
	if (_owner_event_loop_->has_channel(&_acceptor_channel_))
	{
		_acceptor_channel_.disable_all();
		_acceptor_channel_.remove();
		_acceptor_socket_.close();
	}
}

void Acceptor::acceptor_read_handler()
{
	InetAddress peer_address;
	Socket conn = _acceptor_socket_.accept(peer_address);
	if (conn.get_fd() != -1)
	{
		if (_new_connection_handler_)
			_new_connection_handler_(conn, peer_address);
		else
			conn.close();
	}
}
