//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_TCPSERVER_H
#define KIWI_TCPSERVER_H

#include "../Base/Types.h"
#include "../Base/InetAddress.h"
#include "../Reactor/EventLoopPool.h"
#include "Acceptor.h"

namespace Kiwi
{
	class TcpServer
	{
	public:
		TcpServer(const unsigned int &io_thread_num,const InetAddress& acceptor_address, unsigned int thread_num);

		void set_connection_handler(const Type::ConnectionHandler &handler) { _connection_handler_ = handler; }

		void set_message_handler(const Type::MessageHandler &handler) { _message_handler_ = handler; }

		void set_write_complete_handler(const Type::WriteCompleteHandler &handler) { _write_complete_handler_ = handler; }


		void run();



		~TcpServer();

		TcpServer(const TcpServer &) = delete;

		TcpServer &operator=(const TcpServer &) = delete;

	private:
		Type::ConnectionHandler _connection_handler_;
		Type::MessageHandler _message_handler_;
		Type::WriteCompleteHandler _write_complete_handler_;
		std::shared_ptr<EventLoopPool> _event_loop_pool_;
		std::unique_ptr<Acceptor> _acceptor_;
	};
}

#endif //KIWI_TCPSERVER_H
