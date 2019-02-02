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
	class EventLoop;

	class TcpClient
	{
	public:
		TcpClient(EventLoop* base_loop, const InetAddress & server_address);

		void set_connection_handler(const Type::ConnectionHandler &handler) { _connection_handler_ = handler; }

		void set_message_handler(const Type::MessageHandler &handler) { _message_handler_ = handler; }

		void set_write_complete_handler(const Type::WriteCompleteHandler &handler) { _write_complete_handler_ = handler; }

		void connect();

		void disconnect();

		~TcpClient();

		TcpClient(const TcpClient &) = delete;

		TcpClient &operator=(const TcpClient &) = delete;

	private:
		Type::ConnectionHandler _connection_handler_;
		Type::MessageHandler _message_handler_;
		Type::WriteCompleteHandler _write_complete_handler_;
	};
}


#endif //KIWI_TCPCLIENT_H
