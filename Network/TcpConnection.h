//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_TCPCONNECTION_H
#define KIWI_TCPCONNECTION_H

#include "../Base/Types.h"
#include "../Base/Socket.h"
#include "../Base/Buffer.h"

namespace Kiwi
{
	class TcpConnection
	{
	public:
		TcpConnection(Type::EventLoopPtr io_loop_ptr,
					  Type::TcpConnectionID id,
					  Socket socket,
					  const InetAddress &local_address,
					  const InetAddress &peer_address);

		void set_connection_handler(const Type::ConnectionHandler &handler) { _connection_handler_ = handler; }

		void set_message_handler(const Type::MessageHandler &handler) { _message_handler_ = handler; }

		void set_write_complete_handler(const Type::WriteCompleteHandler &handler) { _write_complete_handler_ = handler; }

		void set_close_handler(const Type::CloseHandler &handler) { _close_handler_ = handler; }

		void connection_established();

		void connection_destroyed();

		Type::TcpConnectionID get_id() const { return _id_; }

		~TcpConnection();

		TcpConnection(const TcpConnection &) = delete;

		TcpConnection &operator=(const TcpConnection &) = delete;

	private:
		Type::ConnectionHandler _connection_handler_;
		Type::MessageHandler _message_handler_;
		Type::WriteCompleteHandler _write_complete_handler_;
		Type::CloseHandler _close_handler_;
		Type::EventLoopPtr _owner_event_loop_;
		Type::TcpConnectionID _id_;
		std::unique_ptr<Socket> _socket_;
		std::unique_ptr<Channel> _channel_;
		const InetAddress _local_address_;
		const InetAddress _peer_address_;
		Buffer _input_buffer_;
		Buffer _output_buffer_;


	};
}

#endif //KIWI_TCPCONNECTION_H
