//
// Created by kiwi on 19-1-19.
//

#include "TcpClient.h"
#include "TcpConnection.h"
#include "../Reactor/EventLoop.h"

using namespace Kiwi;
using namespace Kiwi::Type;

TcpClient::TcpClient(EventLoop *base_loop, const InetAddress &server_address, uint32_t client_id)
{

}

void TcpClient::connect()
{

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
}

void TcpClient::remove_connection_handler(const Type::TcpConnectionPtr &conn_ptr)
{

}
