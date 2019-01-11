//
// Created by kiwi on 19-1-6.
//

#ifndef KIWI_SOCKET_H
#define KIWI_SOCKET_H

#include <sys/socket.h>
#include <unistd.h>
#include "InetAddress.h"

namespace Kiwi
{
	class Socket
	{
	public:
		explicit Socket(int socket_fd);

		void connect(const InetAddress &addr);

		void bind(const InetAddress &addr);

		void listen();

		Socket accept(InetAddress &addr);

		void set_tcp_no_delay(bool on);

		void set_keep_alive(bool on);

		void set_reuse_address(bool on);

		void set_reuse_port(bool on);

		~Socket();

		Socket(const Socket &) = delete;

		Socket &operator=(const Socket &) = delete;

	private:
		int _socket_fd_;
	};
}

#endif //KIWI_SOCKET_H
