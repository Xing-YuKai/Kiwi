//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_TCPCLIENT_H
#define KIWI_TCPCLIENT_H

#include "../Base/Types.h"
#include "../Base/InetAddress.h"
#include "../Base/Socket.h"

namespace Kiwi
{
	class TcpClient
	{
	public:
		TcpClient(EventLoop *base_loop, const InetAddress &server_address, uint32_t client_id);

		void set_connection_handler(const Type::ConnectionHandler &handler) { _connection_handler_ = handler; }

		void set_message_handler(const Type::MessageHandler &handler) { _message_handler_ = handler; }

		void set_write_complete_handler(const Type::WriteCompleteHandler &handler) { _write_complete_handler_ = handler; }

		void connect();

		~TcpClient() = default;

		TcpClient(const TcpClient &) = delete;

		TcpClient &operator=(const TcpClient &) = delete;

	public:
		static const int STATE_INITIAL = 1;
		static const int STATE_CONNECTED = 2;
		static const int STATE_DISCONNECTED = 3;

	private:
		void try_connect();

		void new_connection_handler(const Socket &socket);

		void remove_connection_handler(const Type::TcpConnectionPtr &conn_ptr);

	private:
		uint32_t _client_id_;
		EventLoop *_base_loop_;
		InetAddress _server_address_;
		int _state_;
		Type::TcpConnectionPtr _conn_ptr_;
		Type::ConnectionHandler _connection_handler_;
		Type::MessageHandler _message_handler_;
		Type::WriteCompleteHandler _write_complete_handler_;
	};
}


#endif //KIWI_TCPCLIENT_H
