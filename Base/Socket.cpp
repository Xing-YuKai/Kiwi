//
// Created by kiwi on 19-1-6.
//

#include "Socket.h"

Kiwi::Socket::Socket(int socket_fd) :
		_socket_fd_(socket_fd) {}

void Kiwi::Socket::connect(const Kiwi::InetAddress &addr)
{
	sockaddr_in tmp = addr.get_sockaddr_in();
	int retval;
	flag:
	retval = ::connect(_socket_fd_,(const sockaddr *)&tmp,sizeof(tmp));
	if(retval<0)
	{
		switch (errno)
		{
			case EINTR:
				goto flag;
			default:
				std::cerr << "Socket connect error : " << errno << " " << strerror(errno) << std::endl;
				std::terminate();
		}
	}
}

Kiwi::Socket::~Socket()
{
	close(_socket_fd_);
}


