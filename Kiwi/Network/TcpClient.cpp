//
// Created by kiwi on 19-1-19.
//

#include "TcpClient.h"
#include "Connector.h"
#include "TcpConnection.h"
#include "../Reactor/EventLoop.h"

using namespace Kiwi;
using namespace Kiwi::Type;

TcpClient::TcpClient(EventLoop *base_loop, const InetAddress &server_address, uint32_t client_id) :
		_base_loop_(base_loop),
		_client_id_(client_id) {}

void TcpClient::connect()
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

void TcpClient::disconnect()
{

}

void TcpClient::new_connection_handler(const Socket &socket)
{
	_base_loop_->assert_in_event_loop_thread();

	TcpConnectionPtr conn_ptr = std::make_shared<TcpConnection>(_base_loop_,
																_client_id_,
																socket.get_fd(),
																socket.get_peer_address(),
																socket.get_local_address());
	conn_ptr->set_connection_handler(_connection_handler_);
	conn_ptr->set_message_handler(_message_handler_);
	conn_ptr->set_write_complete_handler(_write_complete_handler_);
	conn_ptr->set_close_handler(std::bind(&TcpClient::remove_connection_handler, this, _1));

	_connection_ptr_ = conn_ptr;
	_connection_ptr_->connection_established();
}

void TcpClient::remove_connection_handler(const Type::TcpConnectionPtr &conn_ptr)
{
	_base_loop_->assert_in_event_loop_thread();

	_connection_ptr_.reset();
	conn_ptr->connection_destroyed();
}
