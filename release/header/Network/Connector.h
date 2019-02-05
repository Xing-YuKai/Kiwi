//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_CONNECTOR_H
#define KIWI_CONNECTOR_H

#include "../Base/Socket.h"
#include "../Base/Types.h"
#include "../Base/InetAddress.h"

namespace Kiwi
{
	class Connector
	{
	public:
		Connector(EventLoop *loop, const InetAddress &server_adderss);

		void set_new_connection_handler(const Type::NewConnectionHandler &handler) { _new_connection_handler_ = handler; }

		bool connect();

		void disconnect();

		~Connector();

		Connector(const Connector &) = delete;

		Connector &operator=(const Connector &) = delete;

	private:
		EventLoop *_owner_event_loop_;
		Type::NewConnectionHandler _new_connection_handler_;
		InetAddress _server_address_;
		bool _connected_;
	};
}


#endif //KIWI_CONNECTOR_H
