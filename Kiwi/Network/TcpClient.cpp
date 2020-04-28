//
// Created by kiwi on 19-1-19.
//

#include "TcpClient.h"
#include "TcpConnection.h"
#include "../Reactor/EventLoop.h"

using namespace Kiwi;
using namespace Kiwi::Type;

TcpClient::TcpClient(EventLoop *base_loop, const InetAddress &server_address, uint32_t client_id) :
        _client_id_(client_id),
        _base_loop_(base_loop),
        _server_address_(server_address),
        _state_(STATE_INITIAL) {}

void TcpClient::connect()
{
    if (_state_ != STATE_CONNECTED)
        _base_loop_->run_in_loop(std::bind(&TcpClient::try_connect, this));
}

void TcpClient::try_connect()
{
    Socket socket = Socket::nonblocking_socket();
    if (socket.connect(_server_address_) && !socket.is_self_connect())
    {
        _state_ = STATE_CONNECTED;
        new_connection_handler(socket);
    } else
    {
        socket.close();
        TimeRange time(1000);
        _base_loop_->run_after(std::bind(&TcpClient::try_connect, this), time);
    }
}

void TcpClient::new_connection_handler(const Socket &socket)
{
    _base_loop_->assert_in_event_loop_thread();
    auto peer_address = socket.get_peer_address();
    auto local_address = socket.get_local_address();
    TcpConnectionPtr conn_ptr = std::make_shared<TcpConnection>(_base_loop_,
                                                                _client_id_,
                                                                socket.get_fd(),
                                                                local_address,
                                                                peer_address);
    conn_ptr->set_connection_handler(_connection_handler_);
    conn_ptr->set_message_handler(_message_handler_);
    conn_ptr->set_write_complete_handler(_write_complete_handler_);
    conn_ptr->set_close_handler(std::bind(&TcpClient::remove_connection_handler, this, _1));

    _conn_ptr_ = conn_ptr;
    _conn_ptr_->connection_established();
}

void TcpClient::remove_connection_handler(const Type::TcpConnectionPtr &conn_ptr)
{
    _base_loop_->assert_in_event_loop_thread();

    _state_ = STATE_DISCONNECTED;
    _conn_ptr_.reset();
    conn_ptr->connection_destroyed();
}