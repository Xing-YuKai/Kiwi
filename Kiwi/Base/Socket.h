//
// Created by kiwi on 19-1-6.
//

#ifndef KIWI_SOCKET_H
#define KIWI_SOCKET_H

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>
#include "InetAddress.h"

namespace Kiwi
{
	class Socket
	{
	public:
		static const int BACKLOG_SIZE = 16;

		static Socket nonblocking_socket();

		Socket(int socket_fd);

		bool connect(const InetAddress &addr) const;

		void bind(const InetAddress &addr) const;

		void listen() const;

		void close() const;

		Socket accept(InetAddress &addr) const;

		void shutdown_write() const;

		void shutdown_read() const;

		void set_tcp_no_delay(bool on) const;

		void set_keep_alive(bool on) const;

		void set_reuse_address(bool on) const;

		void set_reuse_port(bool on) const;

		void set_nonblock(bool on) const;

		bool is_self_connect() const;

		InetAddress get_local_address() const;

		InetAddress get_peer_address() const;

		int get_socket_error()const;

		int get_fd() const { return _socket_fd_; }

		~Socket() = default;

	private:
		int _socket_fd_;
	};
}

#endif //KIWI_SOCKET_H
