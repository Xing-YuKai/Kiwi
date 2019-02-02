//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_TCPCONNECTION_H
#define KIWI_TCPCONNECTION_H

#include <atomic>
#include "../Base/Types.h"
#include "../Base/Socket.h"
#include "../Base/Buffer.h"
#include "../Base/TimeRange.h"

namespace Kiwi
{
	class TcpConnection : public std::enable_shared_from_this<TcpConnection>
	{
	public:
		TcpConnection(EventLoop* io_loop_ptr,
					  Type::TcpConnectionID id,
					  Socket socket,
					  const InetAddress &local_address,
					  const InetAddress &peer_address);

		void set_connection_handler(const Type::ConnectionHandler &handler) { _connection_handler_ = handler; }

		void set_message_handler(const Type::MessageHandler &handler) { _message_handler_ = handler; }

		void set_write_complete_handler(const Type::WriteCompleteHandler &handler) { _write_complete_handler_ = handler; }

		void set_close_handler(const Type::CloseHandler &handler) { _close_handler_ = handler; }

		void send(const std::string &data);

		void shutdown_write();

		void close();

		void set_tcp_no_delay(bool on);

		void start_read();

		void stop_read();

		void connection_established();

		void connection_destroyed();

		int get_state() const { return _state_.load(); }

		Type::TcpConnectionID get_id() const { return _id_; }

		EventLoop* get_loop() const { return _owner_event_loop_; }

		~TcpConnection();

		TcpConnection(const TcpConnection &) = delete;

		TcpConnection &operator=(const TcpConnection &) = delete;

	public:
		static const int STATE_INITIAL = 1;
		static const int STATE_CONNECTED = 2;
		static const int STATE_HALF_CLOSE = 3;
		static const int STATE_DISCONNECTED = 4;

	private:
		void tcp_connection_read_handler(TimeRange receive_time);

		void tcp_connection_write_handler();

		void tcp_connection_close_handler();

		void tcp_connection_error_handler();

	private:
		Type::ConnectionHandler _connection_handler_;
		Type::MessageHandler _message_handler_;
		Type::WriteCompleteHandler _write_complete_handler_;
		Type::CloseHandler _close_handler_;
		Type::TcpConnectionID _id_;
		Type::BufferPtr _input_buffer_ptr_;
		Type::BufferPtr _output_buffer_ptr_;

		std::unique_ptr<Socket> _socket_ptr_;
		std::unique_ptr<Channel> _channel_ptr_;
		std::atomic<int> _state_;
		EventLoop* _owner_event_loop_;

		const InetAddress _local_address_;
		const InetAddress _peer_address_;
	};
}

#endif //KIWI_TCPCONNECTION_H
