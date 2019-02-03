//
// Created by kiwi on 19-1-19.
//

#ifndef KIWI_CONNECTOR_H
#define KIWI_CONNECTOR_H

#include "../Base/Types.h"

namespace Kiwi
{
	class Connector
	{
	public:
		Connector(EventLoop* loop,const InetAddress & server_adderss);

		void connect();

		~Connector();

		Connector(const Connector &) = delete;

		Connector &operator=(const Connector &) = delete;

	private:
		EventLoop* _owner_event_loop_;
	};
}


#endif //KIWI_CONNECTOR_H
