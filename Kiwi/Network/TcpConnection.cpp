//
// Created by kiwi on 19-1-19.
//

#include "TcpConnection.h"
#include "../Reactor/EventLoop.h"
#include "../Reactor/Channel.h"

using namespace Kiwi;
using namespace Kiwi::Type;

TcpConnection::TcpConnection(EventLoop *io_loop_ptr,
							 Type::TcpConnectionID id,
							 Socket socket,
							 const InetAddress &local_address,
							 const InetAddress &peer_address) :
		_owner_event_loop_(io_loop_ptr),
		_id_(id),
		_socket_ptr_(new Socket(socket)),
		_channel_ptr_(new Channel(io_loop_ptr, socket.get_fd())),
		_local_address_(local_address),
		_peer_address_(peer_address),
		_output_buffer_ptr_(new Buffer()),
		_input_buffer_ptr_(new Buffer()),
		_state_(STATE_INITIAL)
{
	_channel_ptr_->set_read_handler(std::bind(&TcpConnection::tcp_connection_read_handler, this, _1));
	_channel_ptr_->set_write_handler(std::bind(&TcpConnection::tcp_connection_write_handler, this));
	_channel_ptr_->set_close_handler(std::bind(&TcpConnection::tcp_connection_close_handler, this));
	_channel_ptr_->set_error_handler(std::bind(&TcpConnection::tcp_connection_error_handler, this));
	_socket_ptr_->set_keep_alive(true);
}

void TcpConnection::send(const std::string &data)
{
	if (_state_.load() == STATE_CONNECTED)
	{
		auto this_ptr = shared_from_this();
		_owner_event_loop_->queue_in_loop([this_ptr, data]
										{
											this_ptr->_output_buffer_ptr_->append(data);
											if (!this_ptr->_channel_ptr_->is_writing())
											{
												this_ptr->_channel_ptr_->enable_writing();
												this_ptr->_channel_ptr_->update();
											}
										});
	}
}

void TcpConnection::shutdown_write()
{
	if (_state_.load() == STATE_CONNECTED)
	{
		_state_.store(STATE_HALF_CLOSE);
		auto this_ptr = shared_from_this();
		_owner_event_loop_->run_in_loop([this_ptr]
										{
											if (this_ptr->_channel_ptr_->is_writing())
												this_ptr->_socket_ptr_->shutdown_write();
										});
	}
}

void TcpConnection::close()
{
	if (_state_.load() == STATE_CONNECTED || _state_.load() == STATE_HALF_CLOSE)
	{
		_state_.store(STATE_DISCONNECTED);
		_owner_event_loop_->queue_in_loop(std::bind(&TcpConnection::tcp_connection_close_handler, this));
	}
}

void TcpConnection::set_tcp_no_delay(bool on)
{
	_socket_ptr_->set_tcp_no_delay(on);
}

void TcpConnection::start_read()
{
	auto this_ptr = shared_from_this();
	_owner_event_loop_->run_in_loop([this_ptr]
									{
										if (!this_ptr->_channel_ptr_->is_reading())
										{
											this_ptr->_channel_ptr_->enable_reading();
											this_ptr->_channel_ptr_->update();
										}
									});
}

void TcpConnection::stop_read()
{
	auto this_ptr = shared_from_this();
	_owner_event_loop_->run_in_loop([this_ptr]
									{
										if (this_ptr->_channel_ptr_->is_reading())
										{
											this_ptr->_channel_ptr_->disable_reading();
											this_ptr->_channel_ptr_->update();
										}
									});
}

void TcpConnection::connection_established()
{
	_owner_event_loop_->assert_in_event_loop_thread();
	if (_state_.load() == STATE_INITIAL)
	{
		_state_.store(STATE_CONNECTED);

		_channel_ptr_->enable_reading();
		_channel_ptr_->update();

		_connection_handler_(shared_from_this());
	}
}

void TcpConnection::connection_destroyed()
{
	_owner_event_loop_->assert_in_event_loop_thread();
	if (_state_.load() == STATE_CONNECTED)
	{
		_state_.store(STATE_DISCONNECTED);

		_channel_ptr_->disable_all();
		_channel_ptr_->update();
	}
	_channel_ptr_->remove();
	_socket_ptr_->close();
}

TcpConnection::~TcpConnection()
{
	assert(_state_.load() == STATE_DISCONNECTED);
}

void TcpConnection::tcp_connection_read_handler(TimeRange receive_time)
{
	_owner_event_loop_->assert_in_event_loop_thread();
	if (_channel_ptr_->is_reading())
	{
		ssize_t retval = _input_buffer_ptr_->append_from(_socket_ptr_->get_fd());
		if (retval > 0)
			_message_handler_(shared_from_this(), _input_buffer_ptr_, receive_time);
		if (retval == 0)
			tcp_connection_close_handler();
		if (retval < 0 && errno != EWOULDBLOCK)
			tcp_connection_error_handler();
	}
}

void TcpConnection::tcp_connection_write_handler()
{
	_owner_event_loop_->assert_in_event_loop_thread();
	if (_channel_ptr_->is_writing())
	{
		ssize_t retval = _output_buffer_ptr_->retrieve_to(_socket_ptr_->get_fd());
		if (retval >= 0)
		{
			if (_output_buffer_ptr_->get_readable_bytes() == 0)
			{
				_channel_ptr_->disable_writing();
				_channel_ptr_->update();
				if (_write_complete_handler_)
					_owner_event_loop_->run_in_loop(std::bind(_write_complete_handler_, shared_from_this()));
			}
		}
		if (retval < 0 && errno != EWOULDBLOCK)
			tcp_connection_error_handler();
	}
}

void TcpConnection::tcp_connection_close_handler()
{
	_owner_event_loop_->assert_in_event_loop_thread();
	_state_.store(STATE_DISCONNECTED);
	_channel_ptr_->disable_all();
	_channel_ptr_->update();
	TcpConnectionPtr shared_this = shared_from_this();
	_close_handler_(shared_this);
}

void TcpConnection::tcp_connection_error_handler()
{
	int error = _socket_ptr_->get_socket_error();
	std::cerr << "TcpConnection error_handler" << std::endl
			  << "local_address : " << _local_address_.get_address() << " : " << _local_address_.get_port() << std::endl
			  << "peer_address : " << _peer_address_.get_address() << " : " << _peer_address_.get_port() << std::endl
			  << "errno : " << error << " " << strerror(error) << std::endl;
	tcp_connection_close_handler();
}