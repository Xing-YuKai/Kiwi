//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_TCPSERVER_H
#define KIWI_TCPSERVER_H

#include <atomic>
#include "../Base/Types.h"
#include "../Base/InetAddress.h"
#include "../Base/Socket.h"


namespace Kiwi
{

	class EventLoopPool;

	class Acceptor;

	class EventLoop;

	class TcpServer
	{
	public:
		TcpServer(EventLoop *base_loop, unsigned int io_thread_num, const InetAddress &acceptor_address);

		void set_connection_handler(const Type::ConnectionHandler &handler) { _connection_handler_ = handler; }

		void set_message_handler(const Type::MessageHandler &handler) { _message_handler_ = handler; }

		void set_write_complete_handler(const Type::WriteCompleteHandler &handler) { _write_complete_handler_ = handler; }

		void listen();

		~TcpServer();

		TcpServer(const TcpServer &) = delete;

		TcpServer &operator=(const TcpServer &) = delete;

	private:
		void new_connection_handler(const Socket &socket, const InetAddress &peer_address);

		void remove_connection_handler(const Type::TcpConnectionPtr &conn_ptr);

	private:
		Type::TcpConnectionID _id_counter_;
		Type::TcpConnectionMap _tcp_connections_;
		Type::ConnectionHandler _connection_handler_;
		Type::MessageHandler _message_handler_;
		Type::WriteCompleteHandler _write_complete_handler_;
		EventLoop *_acceptor_loop_ptr_;
		std::shared_ptr<EventLoopPool> _event_loop_pool_;
		std::unique_ptr<Acceptor> _acceptor_ptr_;
		std::atomic<bool> _listening_;
	};
}

#endif //KIWI_TCPSERVER_H
