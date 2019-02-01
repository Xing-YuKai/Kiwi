//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_ACCEPTOR_H
#define KIWI_ACCEPTOR_H

#include "../Base/Types.h"
#include "../Base/Socket.h"
#include "../Reactor/Channel.h"

namespace Kiwi
{
	class EventLoop;

	class Acceptor
	{
	public:
		Acceptor(EventLoop* loop, const InetAddress &address);

		void set_new_connection_handler(const Type::NewConnectionHandler & handler);

		void listen();

		~Acceptor();

		Acceptor(const Acceptor &) = delete;

		Acceptor &operator=(const Acceptor &) = delete;

	private:
		void acceptor_read_handler();
	private:
		Socket _acceptor_socket_;
		Channel _acceptor_channel_;
		EventLoop* _owner_event_loop_;
		Type::NewConnectionHandler _new_connection_handler_;
		bool _listening_;
	};
}

#endif //KIWI_ACCEPTOR_H
